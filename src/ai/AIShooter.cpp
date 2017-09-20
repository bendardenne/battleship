//
// Created by bdardenn on 20/09/17.
//

#include <algorithm>
#include <chrono>
#include "AIShooter.hpp"
#include "../model/Cell.hpp"
#include "../model/ShipLocation.hpp"

AIShooter::AIShooter(Grid &targetGrid) : _targetGrid(targetGrid) {
    //FIXME new engine evey time?
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    _randomEngine = std::default_random_engine(seed);
}

std::pair<int, int> AIShooter::shoot() {
    Coordinates target = shootAtRandom();

    while (!_hitZones.empty()) {
        Coordinates source = *_hitZones.begin();
        if (!shootNearHit(source, target)) {
            _hitZones.erase(source); // Tis hitzone is blocked on all sides
        } else {
            break;
        }
    }


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
                available.push_back(Coordinates(j, i));

    std::shuffle(available.begin(), available.end(), _randomEngine);
    return *available.begin();
}

bool AIShooter::shootNearHit(Coordinates source, Coordinates &target) {
    if (exploreUp(source, target)) return true;
    if (exploreDown(source, target)) return true;
    if (exploreLeft(source, target)) return true;
    if (exploreRight(source, target)) return true;

    if (randomNeighbour(source, target)) return true;

    return false;
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

    return found;
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

    return found;
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

    return found;
}

bool AIShooter::exploreRight(const AIShooter::Coordinates &source, AIShooter::Coordinates &targetSFTC) {
    int y = source.first;
    int x = source.second;
    bool found = false;


    while (++x < _targetGrid.height() && _targetGrid(y, x).status == CellStatus::hit) {
        if (_targetGrid(y, x).ship) {
            found = true;
        } else
            return false; //dead end!
    }

    targetSFTC.first = y;
    targetSFTC.second = x;

    return found;
}

bool AIShooter::randomNeighbour(const Coordinates &source, Coordinates &target) {
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


    if(validBounds.empty()) return false;

    std::shuffle(validBounds.begin(), validBounds.end(), _randomEngine);
    target.first = (*validBounds.begin()).first;
    target.second = (*validBounds.begin()).second;

    return true;
}
