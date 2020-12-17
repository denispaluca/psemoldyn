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
    this->meanV = 0;
}

ParticleSphere::ParticleSphere(
        std::array<double, 3> position,
        std::array<double, 3> initialV,
        int radius,
        double distance,
        double mass,
        double meanV) {
    this->position = position;
    this->initialV = initialV;
    this->radius = radius;
    this->distance = distance;
    this->mass = mass;
    this->meanV = meanV;
}

void ParticleSphere::generate(ParticleContainer &particles, bool is3D) {
    int rq = radius * radius;
    Particle newParticle = Particle(
            position,
            initialV,
            mass);
    MaxwellBoltzmannDistribution(newParticle, meanV, 3);
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
                            {x*distance+position[0], y*distance+position[1],  z*distance+position[2]},
                            initialV,
                            mass);
                    MaxwellBoltzmannDistribution(ap, meanV, 3);
                    particles.push(ap);

                    Particle cp = Particle(
                            {x*distance+position[0], -y*distance+position[1],  z*distance+position[2]},
                            initialV,
                            mass);
                    MaxwellBoltzmannDistribution(cp, meanV, 3);
                    particles.push(cp);

                    Particle ep = Particle(
                            {-x*distance+position[0], y*distance+position[1],  z*distance+position[2]},
                            initialV,
                            mass);
                    MaxwellBoltzmannDistribution(ep, meanV, 3);
                    particles.push(ep);

                    Particle gp = Particle(
                            {-x*distance+position[0], -y*distance+position[1],  z*distance+position[2]},
                            initialV,
                            mass);
                    MaxwellBoltzmannDistribution(gp, meanV, 3);
                    particles.push(gp);

                    if (is3D) {
                        Particle hp = Particle(
                                {-x*distance+position[0], -y*distance+position[1],  -z*distance+position[2]},
                                initialV,
                                mass);
                        MaxwellBoltzmannDistribution(hp, meanV, 3);
                        particles.push(hp);

                        Particle bp = Particle(
                                {x*distance+position[0], y*distance+position[1],  -z*distance+position[2]},
                                initialV,
                                mass);
                        MaxwellBoltzmannDistribution(bp, meanV, 3);
                        particles.push(bp);

                        Particle dp = Particle(
                                {x*distance+position[0], -y*distance+position[1],  -z*distance+position[2]},
                                initialV,
                                mass);
                        MaxwellBoltzmannDistribution(dp, meanV, 3);
                        particles.push(dp);

                        Particle fp = Particle(
                                {-x*distance+position[0], y*distance+position[1],  -z*distance+position[2]},
                                initialV,
                                mass);
                        MaxwellBoltzmannDistribution(fp, meanV, 3);
                        particles.push(fp);
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
