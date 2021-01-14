//
// Created by denis on 16.12.20.
//

#include <utils/ForceUtils.h>

#include <utility>
#include "BoundaryHandler.h"

constexpr double sqrt6of2 = 1.1225;

BoundaryHandler::BoundaryHandler(boundaries_type boundaries, std::array<double, 3> domainSize,
                                 std::array<int, 3> dimensions):
                                 boundaries(boundaries),domainSize(domainSize), dimensions(dimensions){}

void BoundaryHandler::prepareCounter(Particle &p) {
    auto x = p.x;
    counter.f[0] = 0;
    counter.f[1] = 0;
    counter.f[2] = 0;
    counter.setM(p.getM());
    counter.x[0] = x[0];
    counter.x[1] = x[1];
    counter.x[2] = x[2];
}

void BoundaryHandler::iterateCellsAtBoundary(
        Boundaries b,
        const std::function<void(LinkedCell &, std::array<int,3>)>& f)
        {
    switch (b) {
        case left:
            for(int i = 0;i < dimensions[1]; i++)
                for(int j = 0; j < dimensions[2]; j++)
                    f(cells->at(getIndex({0,i,j})), {0,i,j});
            return;
        case right:
            for(int i = 0;i < dimensions[1]; i++)
                for(int j = 0; j < dimensions[2]; j++)
                    f(cells->at(getIndex({dimensions[0]-1, i,j})), {dimensions[0]-1, i,j});
            return;
        case bottom:
            for(int i = 0;i < dimensions[0]; i++)
                for(int j = 0; j < dimensions[2]; j++)
                    f(cells->at(getIndex({i,0,j})), {i,0,j});
            return;
        case top:
            for(int i = 0;i < dimensions[0]; i++)
                for(int j = 0; j < dimensions[2]; j++)
                    f(cells->at(getIndex({i,dimensions[1] - 1,j})), {i,dimensions[1] - 1,j});
            return;
        case front:
            for(int i = 0;i < dimensions[0]; i++)
                for(int j = 0; j < dimensions[1]; j++)
                    f(cells->at(getIndex({i,j,0})), {i,j,0});
            return;
        case back:
            for(int i = 0;i < dimensions[0]; i++)
                for(int j = 0; j < dimensions[1]; j++)
                    f(cells->at(getIndex({i,j, dimensions[2] - 1})), {i,j, dimensions[2] - 1});
            return;
    }
}

void BoundaryHandler::handle(std::vector<LinkedCell>* cells) {
    this->cells = cells;
    handleBoundary(Boundaries::top, boundaries.top());
    handleBoundary(Boundaries::bottom, boundaries.bottom());
    handleBoundary(Boundaries::front, boundaries.front());
    handleBoundary(Boundaries::back, boundaries.back());
    handleBoundary(Boundaries::left, boundaries.left());
    handleBoundary(Boundaries::right, boundaries.right());
}

void BoundaryHandler::handleBoundary(Boundaries boundary, boundary_type& value) {
    if(value == Boundary::reflective)
        reflect(boundary);
    else if(value == Boundary::periodic)
        period(boundary);
}

void BoundaryHandler::iterateParticlesAtBoundary(Boundaries b, const std::function<void(Particle &)> &f) {
    auto func = [&](LinkedCell &c, auto pos) {
        for (auto p : c.getParticles())
            f(*p);
    };
    iterateCellsAtBoundary(b, func);
}

void BoundaryHandler::reflect(Boundaries b) {
    auto func = [&](Particle& p){
        bool isThere;
        auto x = p.x;
        auto sigma = p.sigma;
        auto B_EFFECT = sqrt6of2 * sigma;
        prepareCounter(p);
        switch (b) {
            case left:
                isThere = x[0] < B_EFFECT;
                counter.x[0] = -x[0];
                break;
            case right:
                isThere = domainSize[0] - x[0] < B_EFFECT;
                counter.x[0] = 2 * domainSize[0] - x[0];
                break;
            case bottom:
                isThere = x[1] < B_EFFECT;
                counter.x[1] = -x[1];
                break;
            case top:
                isThere = domainSize[1] - x[1] < B_EFFECT;
                counter.x[1] = 2 * domainSize[1] - x[1];
                break;
            case front:
                isThere = x[2] < B_EFFECT;
                counter.x[2] = -x[2];
                break;
            case back:
                isThere = domainSize[2] - x[2] < B_EFFECT;
                counter.x[2] = 2 * domainSize[2] - x[2];
                break;
        }

        if (isThere)
            calculateLennardJones(p, counter, p.epsilon, sigma);
    };

    iterateParticlesAtBoundary(b,func);
}

void BoundaryHandler::period(Boundaries b) {
    auto func = [&](Particle& p){
        auto& x = p.x;
        switch (b) {
            case top:
                if(x[1] >= domainSize[1])
                    x[1] -= domainSize[1];
                return;
            case bottom:
                if(x[1] < 0)
                    x[1] += domainSize[1];
                return;
            case front:
                if(x[2] < 0)
                    x[2] += domainSize[2];
                return;
            case back:
                if(x[2] >= domainSize[2])
                    x[2] -= domainSize[2];
                return;
            case left:
                if(x[0] < 0)
                    x[0] += domainSize[0];
                return;
            case right:
                if(x[0] >= domainSize[0])
                    x[0] -= domainSize[0];
                return;
        }
    };

    iterateParticlesAtBoundary(b,func);
}

int BoundaryHandler::getIndex(std::array<int, 3> pos) {
    if(pos[0] < 0 || pos[1] < 0 || pos[2] < 0 ||
       pos[0] >= dimensions[0] || pos[1] >= dimensions[1] || pos[2] >= dimensions[2])
        return -1;

    return pos[0] + (pos[1] + pos[2]*dimensions[1])*dimensions[0];
}

void BoundaryHandler::iteratePeriodicParticles(
        std::vector<LinkedCell> *cells,
        const std::function<void(Particle&, Particle&)>& f) {

    this->cells = cells;

    bool front = boundaries.front() == Boundary::periodic;
    bool back = boundaries.back() == Boundary::periodic;
    bool left = boundaries.left() == Boundary::periodic;
    bool right = boundaries.right() == Boundary::periodic;
    bool top = boundaries.top() == Boundary::periodic;
    bool bottom = boundaries.bottom() == Boundary::periodic;


    //SURFACE NEIGHBOURS
    if(left || right){
        auto func = [&](LinkedCell &c, std::array<int,3> pos){
            auto x = dimensions[0] - 1;
            for(int y = -1; y <= 1; y++)
                for(int z = -1; z <= 1; z++){
                    auto index = getIndex({x, pos[1] + y, pos[2] + z});
                    if(index != -1 && index != c.getIndex()){
                        auto& neighbour = cells->at(index);
                        for(auto &p1 :c.getParticles())
                            for(auto &p2 : neighbour.getParticles()){
                                p2->x[0] -= domainSize[0];
                                f(*p1, *p2);
                                p2->x[0] += domainSize[0];
                            }
                    }
                }
        };
        iterateCellsAtBoundary(Boundaries::left, func);
    }

    if(top || bottom){
        auto func = [&](LinkedCell &c, std::array<int,3> pos){
            auto y = dimensions[1] - 1;
            for(int x = -1; x <= 1; x++)
                for(int z = -1; z <= 1; z++){
                    auto index = getIndex({pos[0] + x, y, pos[2] + z});
                    if(index != -1 && index != c.getIndex()){
                        auto& neighbour = cells->at(index);
                        for(auto &p1 :c.getParticles())
                            for(auto &p2 : neighbour.getParticles()){
                                p2->x[1] -= domainSize[1];
                                f(*p1, *p2);
                                p2->x[1] += domainSize[1];
                            }
                    }
                }
        };
        iterateCellsAtBoundary(Boundaries::bottom, func);
    }

    if(front || back){
        auto func = [&](LinkedCell &c, std::array<int,3> pos){
            auto z = dimensions[2] - 1;
            for(int x = -1; x <= 1; x++)
                for(int y = -1; y <= 1; y++){
                    auto index = getIndex({pos[0] + x, pos[1] + y, z});
                    if(index != -1 && index != c.getIndex()){
                        auto& neighbour = cells->at(index);
                        for(auto &p1 :c.getParticles())
                            for(auto &p2 : neighbour.getParticles()){
                                p2->x[2] -= domainSize[2];
                                f(*p1, *p2);
                                p2->x[2] += domainSize[2];
                            }
                    }
                }
        };
        iterateCellsAtBoundary(Boundaries::front, func);
    }


    //SINGLE ROW NEIGHBOURS
    if((left && bottom) || (right && top)){
        std::array<int, 3> pos = {dimensions[0] - 1, dimensions[1] - 1, 0};
        for(int z = 0; z < dimensions[2]; z++){
            auto &c = cells->at(getIndex({0, 0, z}));
            for(int i = -1; i <=1; i++){
                pos[2] = z + i;
                auto index = getIndex(pos);
                if(index != -1){
                    auto& neighbour = cells->at(index);
                    for(auto &p1 :c.getParticles())
                        for(auto &p2 : neighbour.getParticles()){
                            auto &x = p2->x;
                            x[0] -= domainSize[0];
                            x[1] -= domainSize[1];
                            f(*p1, *p2);
                            x[0] += domainSize[0];
                            x[1] += domainSize[1];
                        }
                }
            }
        }
    }

    if((left && top) || (right && bottom)){
        std::array<int, 3> pos = {dimensions[0] - 1, 0, 0};
        for(int z = 0; z < dimensions[2]; z++){
            auto &c = cells->at(getIndex({0, dimensions[1] - 1, z}));
            for(int i = -1; i <=1; i++){
                pos[2] = z + i;
                auto index = getIndex(pos);
                if(index != -1){
                    auto& neighbour = cells->at(index);
                    for(auto &p1 :c.getParticles())
                        for(auto &p2 : neighbour.getParticles()){
                            auto &x = p2->x;
                            x[0] -= domainSize[0];
                            x[1] += domainSize[1];
                            f(*p1, *p2);
                            x[0] += domainSize[0];
                            x[1] -= domainSize[1];
                        }
                }
            }
        }
    }

    if((front && bottom) || (back && top)){
        std::array<int, 3> pos = {0, dimensions[1] - 1, dimensions[2] - 1};
        for(int x = 0; x < dimensions[0]; x++){
            auto &c = cells->at(getIndex({x, 0, 0}));
            for(int i = -1; i <=1; i++){
                pos[0] = x + i;
                auto index = getIndex(pos);
                if(index != -1){
                    auto& neighbour = cells->at(index);
                    for(auto &p1 :c.getParticles())
                        for(auto &p2 : neighbour.getParticles()){
                            auto &p2x = p2->x;
                            p2x[2] -= domainSize[2];
                            p2x[1] -= domainSize[1];
                            f(*p1, *p2);
                            p2x[2] += domainSize[2];
                            p2x[1] += domainSize[1];
                        }
                }
            }
        }
    }

    if((front && top) || (back && bottom)){
        std::array<int, 3> pos = {0, 0, dimensions[2] - 1};
        for(int x = 0; x < dimensions[0]; x++){
            auto &c = cells->at(getIndex({x, dimensions[1] - 1, 0}));
            for(int i = -1; i <=1; i++){
                pos[0] = x + i;
                auto index = getIndex(pos);
                if(index != -1){
                    auto& neighbour = cells->at(index);
                    for(auto &p1 :c.getParticles())
                        for(auto &p2 : neighbour.getParticles()){
                            auto &p2x = p2->x;
                            p2x[2] -= domainSize[2];
                            p2x[1] += domainSize[1];
                            f(*p1, *p2);
                            p2x[2] += domainSize[2];
                            p2x[1] -= domainSize[1];
                        }
                }
            }
        }
    }

    if((left && front) || (right && back)){
        std::array<int, 3> pos = {dimensions[0] -1, 0, dimensions[2] -1};
        for(int y = 0; y < dimensions[1]; y++){
            auto &c = cells->at(getIndex({0, y, 0}));
            for(int i = -1; i <=1; i++){
                pos[1] = y + i;
                auto index = getIndex(pos);
                if(index != -1){
                    auto& neighbour = cells->at(index);
                    for(auto &p1 :c.getParticles())
                        for(auto &p2 : neighbour.getParticles()){
                            auto &x = p2->x;
                            x[0] -= domainSize[0];
                            x[2] -= domainSize[2];
                            f(*p1, *p2);
                            x[0] += domainSize[0];
                            x[2] += domainSize[2];
                        }
                }
            }
        }
    }

    if((left && back) || (right && front)){
        std::array<int, 3> pos = {dimensions[0] -1, 0, 0};
        for(int y = 0; y < dimensions[1]; y++){
            auto &c = cells->at(getIndex({0, y, dimensions[2] - 1}));
            for(int i = -1; i <=1; i++){
                pos[1] = y + i;
                auto index = getIndex(pos);
                if(index != -1){
                    auto& neighbour = cells->at(index);
                    for(auto &p1 :c.getParticles())
                        for(auto &p2 : neighbour.getParticles()){
                            auto &x = p2->x;
                            x[0] -= domainSize[0];
                            x[2] += domainSize[2];
                            f(*p1, *p2);
                            x[0] += domainSize[0];
                            x[2] -= domainSize[2];
                        }
                }
            }
        }
    }



    //SINGLE NEIGHBOURS or CORNERS
    if((left && front && bottom) || (right && back && top)){
        auto &c1 = cells->at(getIndex({0,0,0}));
        auto &c2 = cells->at(getIndex({dimensions[0]-1,dimensions[1]-1,dimensions[2]-1}));

        for(auto &p1 :c1.getParticles())
            for(auto &p2 : c2.getParticles()){
                auto &x = p2->x;
                x[0] -= domainSize[0];
                x[1] -= domainSize[1];
                x[2] -= domainSize[2];
                f(*p1, *p2);
                x[0] += domainSize[0];
                x[1] += domainSize[1];
                x[2] += domainSize[2];
            }
    }

    if((left && front && top) || (right && back && bottom)){
        auto &c1 = cells->at(getIndex({0,dimensions[1]-1,0}));
        auto &c2 = cells->at(getIndex({dimensions[0]-1, 0,dimensions[2]-1}));

        for(auto &p1 :c1.getParticles())
            for(auto &p2 : c2.getParticles()){
                auto &x = p2->x;
                x[0] -= domainSize[0];
                x[1] += domainSize[1];
                x[2] -= domainSize[2];
                f(*p1, *p2);
                x[0] += domainSize[0];
                x[1] -= domainSize[1];
                x[2] += domainSize[2];
            }
    }

    if((left && back && bottom) || (right && front && top)){
        auto &c1 = cells->at(getIndex({0,0,dimensions[2]-1}));
        auto &c2 = cells->at(getIndex({dimensions[0]-1, dimensions[1]-1,0}));

        for(auto &p1 :c1.getParticles())
            for(auto &p2 : c2.getParticles()){
                auto &x = p2->x;
                x[0] -= domainSize[0];
                x[1] -= domainSize[1];
                x[2] += domainSize[2];
                f(*p1, *p2);
                x[0] += domainSize[0];
                x[1] += domainSize[1];
                x[2] -= domainSize[2];
            }
    }

    if((left && back && top) || (right && front && bottom)){
        auto &c1 = cells->at(getIndex({0, dimensions[1]-1, dimensions[2]-1}));
        auto &c2 = cells->at(getIndex({dimensions[0]-1, 0, 0}));

        for(auto &p1 :c1.getParticles())
            for(auto &p2 : c2.getParticles()){
                auto &x = p2->x;
                x[0] -= domainSize[0];
                x[1] += domainSize[1];
                x[2] += domainSize[2];
                f(*p1, *p2);
                x[0] += domainSize[0];
                x[1] -= domainSize[1];
                x[2] -= domainSize[2];
            }
    }
}