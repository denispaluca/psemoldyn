//
// Created by mira on 08.12.20.
//

#ifndef PSEMOLDYN_GROUPB_LINKEDCELLCONTAINER_H
#define PSEMOLDYN_GROUPB_LINKEDCELLCONTAINER_H

#include "LinkedCell.h"

class LinkedCellContainer {
private:
    double cutoff_radius;

    std::vector<LinkedCell> cells;

    std::vector<LinkedCell> boundary;

    std::vector<LinkedCell> halo;
public:
    LinkedCellContainer();

    LinkedCellContainer(double cutoff_radius, ParticleContainer &particles);

    void iterateParticlePairs(void (*f)(Particle&,Particle&));

};


#endif //PSEMOLDYN_GROUPB_LINKEDCELLCONTAINER_H
