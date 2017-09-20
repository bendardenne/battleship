//
// Created by bdardenn on 14/09/17.
//

#pragma once

#include "../model/Grid.hpp"
#include "../model/Ship.hpp"

class RandomShipPlacer {
public:
    RandomShipPlacer();
    void placeShips(Grid& grid) const;
protected:
private:
    std::vector<std::pair<size_t, size_t>> getAvailablePositions(const Grid &grid) const;
    void placeShip(std::shared_ptr<Ship> ship, Grid& grid) const;
};
