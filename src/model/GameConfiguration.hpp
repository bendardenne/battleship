//
// Created by bdardenn on 23/08/17.
//

#pragma once

#include <string>

struct GameConfiguration {
    size_t gridWidth;
    size_t gridHeight;
    unsigned shotsPerTurn;
    std::string player1;
    std::string player2;
};
