//
// Created by bdardenn on 08/09/17.
//

#pragma once

#include <cstddef>
#include <vector>

#include "ShipLocation.hpp"


class Ship {
public:
    Ship(size_t length);
    Ship(const Ship &other);
    size_t const length() const;
    bool const sunk() const;
    const std::string name() const;
    void hit(size_t i);

    bool operator<(Ship const & other) const;
    bool operator==(Ship const & other) const;
    bool operator!=(Ship const & other) const;
    friend std::ostream& operator<<(std::ostream& out, const Ship & other);

protected:

private:
    static int __sId;
    size_t _id;
    size_t _length;
    std::vector<bool> _hits;
};
