//
// Created by denis on 14.12.20.
//

#include <outputWriter/VTKWriter.h>
#include <utils/ForceUtils.h>
#include "Simulation.h"
#include "cell/LinkedCellContainer.h"

Simulation::Simulation(molsimInput &data) : data(data) {
    thermostat = data.thermostat().present() ?
            new Thermostat(data.thermostat().get(), data.particle_data().is3D())
            : nullptr;

    auto pg = ParticleGenerator(data.particle_data(), thermostat);

    //Update delta_t for each particle before copying
    pg.getParticles().iterate([&](Particle &p) {
        p.updateDT(data.delta_t());
    });

    if(data.linked_cell()){
        container = new LinkedCellContainer(data.domain(), pg.getParticles());
    } else {
        container = new ParticleContainer(pg.getParticles().getParticles());
    }

    profiling = data.profiling() && data.linked_cell();

    if(profiling) {
        profiler = Profiler::getInstance();
        profiler->init(data, container);
        profiling_freq = data.profiler().present() ? data.profiler()->profiling_frequency() : 1000;
    }

    container->mixParameters();
}

int Simulation::start(bool isPT) {
    int iteration = 0;

    double current_time = 0;
    int freq = data.frequency_output().present() ?
            data.frequency_output().get() :
            10;

    if(!isPT) plotParticles(0);
    // for this loop, we assume: current x, current f and current v are known
    while (current_time < data.t_end()) {
        container->calculateIteration();

        iteration++;
        if (!isPT && iteration % freq == 0) {
            plotParticles(iteration);
        }

        if (profiling && iteration % profiling_freq == 0) {
            profiler->createProfile();
        }

        if(thermostat != nullptr && iteration != 0 && iteration % thermostat->getSteps() == 0){
            thermostat->scale(*container);
        }

        current_time += data.delta_t();
    }

    return iteration;
}

void Simulation::plotParticles(int iteration) {
    /* output in xyz format */

//    std::string out_name_xyz("MD_xyz");
//    outputWriter::XYZWriter writer;
//    writer.plotParticles(particles, out_name_xyz, iteration);

    /* VTK output */

    std::string out_name_vtk(
            data.name_output().present() ?
                data.name_output().get().c_str() :
                "MD_vtk");
    outputWriter::VTKWriter vtkWriter;

    vtkWriter.initializeOutput(container->size());

    container->iterate([&](Particle& p) {
        vtkWriter.plotParticle(p);
    });

    vtkWriter.writeFile(out_name_vtk, iteration);
}

molsimInput &Simulation::checkpoint() {
    data.particle_data().particles().particle().clear();
    data.particle_data().cuboids().cuboid().clear();
    data.particle_data().spheres().sphere().clear();

    container->iterate([&](Particle &p){
        data.particle_data().particles().particle().push_back(mapParticleToXML(p));
    });

    return data;
}

int Simulation::getNumParticles() {
    return container->size();
}