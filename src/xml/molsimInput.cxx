#include <string>
#include <iostream>

#include "molsimInput-pskel.hxx"

using std::cerr;
using std::endl;

using namespace std;

class double_vector_pimpl: public double_vector_pskel {
public:
    virtual void x (const string& g) {
        x_ = stod(g);
    }
    virtual void y (const string& g) {
        y_ = stod(g);
    }
    virtual void z (const string& g) {
        z_ = stod(g);
    }

public:
    double x_;
    double y_;
    double z_;
};

class integer_vector_pimpl: public integer_vector_pskel {
public:
    virtual void x (const string& g) {
        x_ = stoi(g);
    }
    virtual void y (const string& g) {
        y_ = stoi(g);
    }
    virtual void z (const string& g) {
        z_ = stoi(g);
    }

public:
    int x_;
    int y_;
    int z_;
};

class cuboid_pimpl: public cuboid_pskel {
public:
    virtual void coordinates (const double_vector_pimpl& g) {
        coordinates_ = g;
    }
    virtual void particles_per_dimension (const integer_vector_pimpl& g) {
        particles_per_dimension_ = g;
    }
    virtual void distance_particles (const string& g) {
        distance_particles_ = stod(g);
    }
    virtual void mass (const string& g) {
        mass_ = stod(g);
    }
    virtual void velocity (const double_vector_pimpl& g) {
        velocity_ = g;
    }

public:
    double_vector_pimpl coordinates_;
    integer_vector_pimpl particles_per_dimension_;
    double distance_particles_;
    double mass_;
    double_vector_pimpl velocity_;
};

class cuboid_cluster_pimpl: public cuboid_cluster_pskel {
public:
    virtual void cuboid (const cuboid_pimpl& g) {
        cuboid_ = g;
    }

public:
    cuboid_pimpl cuboid_;
};

class particle_pimpl: public particle_pskel {
public:
    virtual void coordinates (const double_vector_pimpl& g) {
        coordinates_ = g;
    }
    virtual void velocity (const double_vector_pimpl& g) {
        velocity_ = g;
    }
    virtual void mass (const string& g) {
        mass_ = stod(g);
    }

public:
    double_vector_pimpl coordinates_;
    double_vector_pimpl velocity_;
    double mass_;
};

class particle_cluster_pimpl: public particle_cluster_pskel {
public:
    virtual void cuboid (const particle_pimpl& g) {
        particle_ = g;
    }
public:
    particle_pimpl particle_;
};



class input_particles_pimpl: public input_particles_pskel {
public:
    virtual void particle_file (const string& g) {
        particle_file_ = g;
    }

    virtual void cuboids_file (const string& g) {
        cuboids_file_ = g;
    }

    virtual void cuboids (const cuboid_cluster_pimpl& g) {
        cuboids_ = g;
    }

    virtual void particles (const particle_cluster_pimpl& g) {
        particles_ = g;
    }

public:
    string particle_file_ = "";
    string cuboids_file_ = "";
    cuboid_cluster_pimpl cuboids_;
    particle_cluster_pimpl particles_;
};

class molsimInput_pimpl: public molsimInput_pskel {
public:
    virtual void name_output (const string& g) {
        name_output_ = g;
    }

    virtual void frequency_output (const string& g) {
        frequency_output_ = stoi(g);
    }

    virtual void delta_t (const string& g) {
        delta_t_ = stod(g);
    }

    virtual void t_end (const string& g) {
        t_end_ = stoi(g);
    }

    virtual void particles (const input_particles_pimpl& g) {
        particles_ = g;
    }

public:
    string name_output_ = "MD_vtk";
    int frequency_output_ = 10;
    double delta_t_;
    int t_end_;
    input_particles_pimpl particles_;
};

molsimInput_pimpl fileReader(char *filename) {
    try {
        xml_schema::string_pimpl string_p;
        double_vector_pimpl double_vector_p;
        double_vector_p.parsers (string_p,  // x
                                 string_p,  // y
                                 string_p);  // z

        //xml_schema::integer_pimpl integer_p;
        integer_vector_pimpl integer_vector_p;
        integer_vector_p.parsers (string_p,  // x
                                  string_p,  // y
                                  string_p);  // z

        cuboid_pimpl cuboid_p;
        cuboid_p.parsers (double_vector_p,  // x
                          integer_vector_p,  // y
                          string_p, /* distance_particles */
                          string_p, /* mass */
                          double_vector_p); /* velocity */

        cuboid_cluster_pimpl cuboid_cluster_p;
        cuboid_cluster_p.parsers(cuboid_p);

        particle_pimpl particle_p;
        particle_p.parsers(double_vector_p, /* coordinates */
                           double_vector_p, /* velocity */
                           string_p); /* mass */

        particle_cluster_pskel particle_cluster_p;
        particle_cluster_p.parsers(particle_p);

        //xml_schema::string_pimpl string_p;
        input_particles_pimpl input_particles_p;
        input_particles_p.parsers(string_p, /* particle_file */
                                  string_p, /* cuboids_file */
                                  cuboid_cluster_p, /* cuboids */
                                  particle_cluster_p); /* particles */

        molsimInput_pimpl molsimInput_p;
        molsimInput_p.parsers(string_p,
                              string_p,
                              string_p,
                              string_p,
                              input_particles_p);

        xml_schema::document doc_p (
                molsimInput_p,
                "molsimInput");
        molsimInput_p.pre ();
        doc_p.parse (filename);
        molsimInput_p.post_molsimInput ();

        xml_schema::document doc_2 (
                input_particles_p,
                "molsimInput");
        input_particles_p.pre ();
        doc_2.parse (filename);
        molsimInput_p.particles_ = input_particles_p;
/*
        xml_schema::document doc_3 (
                particle_cluster_p,
                "molsimInput");
        particle_cluster_p.pre ();
        doc_2.parse (filename);
        molsimInput_p.particles_.particles = particle_cluster_p;
*/


        return molsimInput_p;
    }
    catch(const xml_schema::exception &e){
    std::cout << "Erroneous programme call!" << std::endl;
        exit(-1);
    }
}
/*
int main (int argc, char* argv[]) {
    argc++;
    molsimInput_pimpl molsimInput_p = fileReader(argv[1]);
    std::cout << "name_output_: " << molsimInput_p.name_output_ << std::endl;
    std::cout << "frequency_output_: " << molsimInput_p.frequency_output_ << std::endl;
    std::cout << "delta_t_: " << molsimInput_p.delta_t_ << std::endl;
    std::cout << "t_end_: " << molsimInput_p.t_end_ << std::endl;

    std::cout << "molsimInput_p.particles_.particle_file_: " << molsimInput_p.particles_.particle_file_ << std::endl;
    std::cout << "molsimInput_p.particles_.cuboids_file_: " << molsimInput_p.particles_.cuboids_file_ << std::endl;

    return 0;
}
 */