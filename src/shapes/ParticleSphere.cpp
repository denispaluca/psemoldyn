#include <sstream>
#include "utils/ArrayUtils.h"
#include "utils/MaxwellBoltzmannDistribution.h"
#include "ParticleSphere.h"

ParticleSphere::ParticleSphere() {
    this->position = {0., 0., 0.};
    this->initialV = {0., 0., 0.};
    this->radius = 0.;
    this->distance = 0.;
    this->mass = 0;
}

ParticleSphere::ParticleSphere(
        std::array<double, 3> position,
        std::array<double, 3> initialV,
        int radius,
        double distance,
        double mass) {
    this->position = position;
    this->initialV = initialV;
    this->radius = radius;
    this->distance = distance;
    this->mass = mass;
}

void ParticleSphere::generate(ParticleContainer &particles, bool is3D) {
    int rq = radius * radius;
    Particle newParticle = Particle(
            position,
            initialV,
            mass);
    particles.push(newParticle);

    int zr = radius;

    if (!is3D) {
        zr = 0;
    }

    for (int x = 0; x<=radius; x++){
        for (int y = 0; y<=radius; y++) {
            for (int z=0; z<=zr; z++) {
                if (x+y+z > 0 && x*x + y*y + z*z <= rq) {
                    Particle ap = Particle(
                            {x*distance+position[0], y*distance+position[1],  is3D?z*distance+position[2]:0},
                            initialV,
                            mass);
                    particles.push(ap);
                    if (y!= 0) {
                        Particle cp = Particle(
                                {x*distance+position[0], -y*distance+position[1],  is3D?z*distance+position[2]:0},
                                initialV,
                                mass);
                        particles.push(cp);
                    }
                    if (x!=0) {
                        Particle ep = Particle(
                                {-x*distance+position[0], y*distance+position[1],  is3D?z*distance+position[2]:0},
                                initialV,
                                mass);
                        particles.push(ep);
                    }
                    if (x!=0 && y!= 0) {
                        Particle gp = Particle(
                                {-x*distance+position[0], -y*distance+position[1],  is3D?z*distance+position[2]:0},
                                initialV,
                                mass);
                        particles.push(gp);
                    }

                    if (is3D && z!=0) {
                        if (x!=0 && y!=0) {
                            Particle hp = Particle(
                                    {-x*distance+position[0], -y*distance+position[1],  -z*distance+position[2]},
                                    initialV,
                                    mass);
                            particles.push(hp);
                        }
                        Particle bp = Particle(
                                {x*distance+position[0], y*distance+position[1],  -z*distance+position[2]},
                                initialV,
                                mass);
                        particles.push(bp);
                        if (y!=0) {
                            Particle dp = Particle(
                                    {x*distance+position[0], -y*distance+position[1],  -z*distance+position[2]},
                                    initialV,
                                    mass);
                            particles.push(dp);
                        }
                        if(x!=0) {
                            Particle fp = Particle(
                                    {-x*distance+position[0], y*distance+position[1],  -z*distance+position[2]},
                                    initialV,
                                    mass);
                            particles.push(fp);
                        }
                    }
                }
            }
        }
    }
}

bool ParticleSphere::operator==(ParticleSphere &other) {
    return (position == other.position) &&
            (initialV == other.initialV) &&
            (radius == other.radius) &&
            (distance == other.distance) &&
            (mass == other.mass);
}

std::string ParticleSphere::toString() {
    std::stringstream stream;
    stream << "Spere: " << position << " initialV: " << initialV << " radius: " << radius
           << " distance: " << distance << " mass: " << mass;
    return stream.str();
}

int ParticleSphere::getRadius() {
    return radius;
}

std::size_t ParticleSphere::getNrParticles() {
    return 5*radius*radius*radius;
}
