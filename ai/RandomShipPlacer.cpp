//
// Created by bdardenn on 14/09/17.
//

#include "RandomShipPlacer.hpp"
#include <algorithm>
#include <chrono>

RandomShipPlacer::RandomShipPlacer() {}

void
RandomShipPlacer::placeShips(Grid &grid) const {
    std::vector<std::shared_ptr<Ship>> ships = grid.fleet();

    // Try largest first
    std::sort(ships.begin(), ships.end(), [](std::shared_ptr<Ship> &a, std::shared_ptr<Ship> &b) {
        return a->length() > b->length();
    });

    for (auto ship: ships) {
        placeShip(ship, grid);
    }
}

void
RandomShipPlacer::placeShip(std::shared_ptr<Ship> ship, Grid &grid) const {
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 randomEngine = std::default_random_engine(seed);

    std::vector<std::pair<size_t, size_t >> positions = getAvailablePositions(grid);
    std::shuffle(positions.begin(), positions.end(), randomEngine);

    std::vector<Orientation> orientations = {Orientation::vertical, Orientation::horizontal};

    for (auto position : positions) {
        std::shuffle(orientations.begin(), orientations.end(), randomEngine);
        for (auto orientation : orientations) {
            ShipLocation location = { .x = position.second, .y = position.first, .orientation = orientation};

            if (grid.anchorShip(ship, location))
                return;
        }
    }
}

std::vector<std::pair<size_t, size_t>>
RandomShipPlacer::getAvailablePositions(const Grid &grid) const {

    std::vector<std::pair<size_t, size_t >> possibilities;

    for (size_t i = 0; i < grid.width(); i++)
        for (size_t j = 0; j < grid.height(); j++)
            if (!grid(j, i).ship)
                possibilities.push_back(std::pair<size_t, size_t>(j, i));

    return possibilities;
}
