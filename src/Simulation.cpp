//
// Created by denis on 14.12.20.
//

#include <outputWriter/VTKWriter.h>
#include <utils/ForceUtils.h>
#include "Simulation.h"
#include "LinkedCellContainer.h"
#include "utils/XSDMapper.h"

Simulation::Simulation(molsimInput &data) : data(data) {
    auto pg = ParticleGenerator(data.particle_data());
    size = pg.getParticles().size();
    if(data.linked_cell()){
        container = new LinkedCellContainer(
                mapDoubleVec(data.domain_size()),
                {0,0,0},
                data.cutoff_radius(),
                pg.getParticles());

    } else {
        container = new ParticleContainer(pg.getParticles().getParticles());
    }

    container->iterate([&data](Particle &p) {
        p.updateDT(data.delta_t());
    });
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
        // calculate new x

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

    vtkWriter.initializeOutput(size);

    this->container->iterate([&](Particle& p) {
        vtkWriter.plotParticle(p);
    });

    vtkWriter.writeFile(out_name_vtk, iteration);
}
