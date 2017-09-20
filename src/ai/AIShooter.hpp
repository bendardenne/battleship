//
// Created by bdardenn on 20/09/17.
//

#pragma once

#include <random>

#include <set>
#include "../model/Grid.hpp"

class AIShooter {

public:
    AIShooter(Grid& targetGrid);

    std::pair<int, int> shoot();

protected:

private:
    // TODO Check hidden from calling code.
    // We could actually have this defined somewhere, but for toying purposes I will leave this definition internal.
    typedef std::pair<int,int> Coordinates;

    std::minstd_rand0 _randomEngine;
    Grid& _targetGrid;
    std::set<Coordinates> _hitZones;

    Coordinates shootAtRandom();

    Coordinates shootNearHit();
    void removeShipFromHitZones(Ship &ship, const ShipLocation &at);

    bool exploreUp(const Coordinates &source, Coordinates &targetSFTC);
    bool exploreDown(const Coordinates &source, Coordinates &targetSFTC);
    bool exploreLeft(const Coordinates &source, Coordinates &targetSFTC);
    bool exploreRight(const Coordinates &source, Coordinates &targetSFTC);

    Coordinates randomNeighbour(const Coordinates &source);
};

