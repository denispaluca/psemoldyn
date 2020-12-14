//
// Created by denis on 14.12.20.
//

#include <outputWriter/VTKWriter.h>
#include <utils/ForceUtils.h>
#include "Simulation.h"

Simulation::Simulation(molsimInput &data) : data(data) {
    particleContainer = ParticleGenerator(data.particle_data()).getParticles();
    for(auto& p : particleContainer.getParticles()){
        p.updateDT(data.delta_t());
    }
}

void Simulation::start() {
    int iteration = 0;
    plotParticles(0);

    double current_time = 0;
    int freq = data.frequency_output().present() ?
            data.frequency_output().get() :
            10;
    // for this loop, we assume: current x, current f and current v are known
    while (current_time < data.t_end()) {
        // calculate new x
        particleContainer.iterate([](Particle &p){
            p.calculateX();
            p.saveOldF();
        });
        // calculate new f
        particleContainer.iteratePairs(calculateLennardJones);
        // calculate new v
        particleContainer.iterate([](Particle &p){
            p.calculateV();
        });

        iteration++;
        if (iteration % freq == 0) {
            plotParticles(iteration);
        }

        //std::cout << "Iteration " << iteration << " finished." << std::endl;

        current_time += data.delta_t();
    }
}

void Simulation::plotParticles(int iteration) {

    /* output in xyz format */

//    std::string out_name_xyz("MD_xyz");
//    outputWriter::XYZWriter writer;
//    writer.plotParticles(particles, out_name_xyz, iteration);

    /* VTK output */

    auto particles = particleContainer.getParticles();

    std::string out_name_vtk(
            data.name_output().present() ?
                data.name_output().get().c_str() :
                "MD_vtk");
    outputWriter::VTKWriter vtkWriter;

    vtkWriter.initializeOutput(particles.size());

    for(auto &p : particles) {
        vtkWriter.plotParticle(p);
    }

    vtkWriter.writeFile(out_name_vtk, iteration);
}
