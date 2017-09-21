//
// Created by bdardenn on 11/09/17.
//

#pragma once

#include <memory>

#include "Ship.hpp"

enum CellStatus {
    clean, hit
};

struct Cell_t {
    std::shared_ptr<Ship> ship;
    CellStatus status;
};

using Cell = Cell_t;
