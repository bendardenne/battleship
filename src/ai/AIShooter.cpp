//
// Created by bdardenn on 20/09/17.
//

#include <algorithm>
#include <chrono>
#include "AIShooter.hpp"

AIShooter::AIShooter(Grid &targetGrid) : _targetGrid(targetGrid) {
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    _randomEngine = std::default_random_engine(seed);
}

std::pair<int, int> AIShooter::shoot() {
    Coordinates target = _hitZones.empty() ? shootAtRandom() : shootNearHit();
    _targetGrid.shoot(target.first, target.second);

    const std::shared_ptr<Ship> &ship = _targetGrid(target.first, target.second).ship;
    if (ship) {
        if (!ship->sunk()) {
            _hitZones.insert(target);
        } else {
            removeShipFromHitZones(*ship, _targetGrid.shipLocations().at(*ship));
        }
    }

    return target;
}

std::pair<int, int> AIShooter::shootAtRandom() {

    // TODO what if nothing available?
    std::vector<Coordinates> available;
    for (size_t i = 0; i < _targetGrid.width(); i++)
        for (size_t j = 0; j < _targetGrid.height(); j++)
            if (_targetGrid(j, i).status == CellStatus::clean)
                available.emplace_back(j, i);

    std::shuffle(available.begin(), available.end(), _randomEngine);
    return *available.begin();
}

AIShooter::Coordinates AIShooter::shootNearHit() {
    Coordinates source = *_hitZones.begin();
    Coordinates target;

    if (exploreUp(source, target)) return target;
    if (exploreDown(source, target)) return target;
    if (exploreLeft(source, target)) return target;
    if (exploreRight(source, target)) return target;

    return randomNeighbour(source);
}


void AIShooter::removeShipFromHitZones(Ship &ship, const ShipLocation &at) {
    int x = at.x;
    int y = at.y;
    for (size_t i = 0; i < ship.length(); i++) {
        _hitZones.erase(Coordinates(y, x));
        at.orientation == Orientation::horizontal ? x++ : y++;
    }
}

bool AIShooter::exploreUp(const Coordinates &source, Coordinates &targetSFTC) {
    int y = source.first;
    int x = source.second;
    bool found = false;

    while (--y >= 0 && _targetGrid(y, x).status == CellStatus::hit) {
        if (_targetGrid(y, x).ship)
            found = true;
        else
            return false; //dead end!
    }

    targetSFTC.first = y;
    targetSFTC.second = x;

    return found && y >= 0;
}

bool AIShooter::exploreDown(const AIShooter::Coordinates &source, AIShooter::Coordinates &targetSFTC) {
    int y = source.first;
    int x = source.second;
    bool found = false;


    while (++y < _targetGrid.height() && _targetGrid(y, x).status == CellStatus::hit) {
        if (_targetGrid(y, x).ship) {
            found = true;
        } else
            return false; //dead end!
    }

    targetSFTC.first = y;
    targetSFTC.second = x;

    return found && y < _targetGrid.height();
}

bool AIShooter::exploreLeft(const AIShooter::Coordinates &source, AIShooter::Coordinates &targetSFTC) {
    int y = source.first;
    int x = source.second;
    bool found = false;


    while (--x >= 0 && _targetGrid(y, x).status == CellStatus::hit) {
        if (_targetGrid(y, x).ship) {
            found = true;
        } else
            return false; //dead end!
    }

    targetSFTC.first = y;
    targetSFTC.second = x;

    return found && x >= 0;
}

bool AIShooter::exploreRight(const AIShooter::Coordinates &source, AIShooter::Coordinates &targetSFTC) {
    int y = source.first;
    int x = source.second;
    bool found = false;


    while (++x < _targetGrid.width() && _targetGrid(y, x).status == CellStatus::hit) {
        if (_targetGrid(y, x).ship) {
            found = true;
        } else
            return false; //dead end!
    }

    targetSFTC.first = y;
    targetSFTC.second = x;

    return found && x < _targetGrid.width();
}

AIShooter::Coordinates AIShooter::randomNeighbour(const Coordinates &source) {
    std::vector<Coordinates> possible = {
            Coordinates(source.first + 1, source.second),
            Coordinates(source.first - 1, source.second),
            Coordinates(source.first, source.second + 1),
            Coordinates(source.first, source.second - 1)
    };

    std::vector<Coordinates> validBounds;
    std::copy_if(possible.begin(), possible.end(), std::back_inserter(validBounds),
                 [this](Coordinates c) {
                     return c.first >= 0 && c.first < _targetGrid.height() &&
                            c.second >= 0 && c.second < _targetGrid.width() &&
                            _targetGrid(c.first, c.second).status == CellStatus::clean;
                 });


    std::shuffle(validBounds.begin(), validBounds.end(), _randomEngine);
    return *validBounds.begin();
}
