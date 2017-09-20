//
// Created by bdardenn on 11/09/17.
//

#pragma once

#include <memory>

enum CellStatus {
    clean, hit
};

typedef struct {
    std::shared_ptr<Ship> ship;
    CellStatus status;
} Cell;
