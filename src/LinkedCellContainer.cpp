//
// Created by mira on 08.12.20.
//

#include "LinkedCellContainer.h"


LinkedCellContainer LinkedCellContainer() {
    cutoff_radius = 1;
    cells = ;

    std::vector<LinkedCell> boundary;

    std::vector<LinkedCell> halo;
}

LinkedCellContainer LinkedCellContainer(double cutoff_radius, ParticleContainer &particles) {

}

void iterateNeighborCells(void (*f)(Particle&,Particle&)) {
    for(auto i = cells.begin(); i != cells.end(); ++i)
        for(auto j = i + 1; j != particles.end(); ++j)
            (*f)(*i,*j);
}