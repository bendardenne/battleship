//
// Created by bdardenn on 23/08/17.
//

#pragma once

#include <string>

struct GameConfiguration {
    size_t gridWidth = 10;
    size_t gridHeight = 10;
    unsigned shotsPerTurn = 3;
    std::string player1 = "Player1";
    std::string player2 = "Player2";
};
