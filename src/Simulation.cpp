//
// Created by denis on 14.12.20.
//

#include <outputWriter/VTKWriter.h>
#include <utils/ForceUtils.h>
#include "Simulation.h"
#include "cell/LinkedCellContainer.h"

Simulation::Simulation(molsimInput &data) : data(data) {
    auto pg = ParticleGenerator(data.particle_data());
    //Update delta_t for each particle before copying
    pg.getParticles().iterate([&](Particle &p) {
        p.updateDT(data.delta_t());
    });

    if(data.linked_cell()){
        container = new LinkedCellContainer(data.domain(), pg.getParticles());
    } else {
        container = new ParticleContainer(pg.getParticles().getParticles());
    }
}

void Simulation::start(bool isPT) {
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

        current_time += data.delta_t();
    }
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
