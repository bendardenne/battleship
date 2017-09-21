//
// Created by bdardenn on 08/09/17.
//

#include <ostream>
#include <iostream>
#include <algorithm>

#include "Ship.hpp"

int Ship::__sId = 0;

Ship::Ship(size_t length) : _length(length), _hits(length), _id(__sId++) {

}

size_t const Ship::length() const {
    return _length;
}

bool Ship::operator<(const Ship &other) const {
    return _id < other._id;
}

bool const Ship::sunk() const {
    return std::all_of(_hits.begin(), _hits.end(), [](bool hit) { return hit; });
}

std::string const Ship::name() const {
    switch (_length) {
        case 2 :
            return "Destroyer";
        case 3:
            return "Submarine";
        case 4:
            return "Battleship";
        case 5:
            return "Aircraft Carrier";
        default:
            return "Ship";
    }
};

bool Ship::operator==(Ship const &other) const {
    return _id == other._id;
}

std::ostream &operator<<(std::ostream &out, const Ship &ship) {
    out << ship._id;
    return out;
}

bool Ship::operator!=(Ship const &other) const {
    return !(*this == other);
}

void Ship::hit(size_t i) {
    if (i >= length())
        throw std::out_of_range("Ship::hit: index is out of range");

    _hits[i] = true;
}

