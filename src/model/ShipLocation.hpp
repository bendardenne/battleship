//
// Created by bdardenn on 09/09/17.
//

#pragma once

#include <cstddef>

#include "Orientation.hpp"


typedef struct {
    size_t x;
    size_t y;
    Orientation orientation;
} ShipLocation;
