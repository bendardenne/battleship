//
// Created by bdardenn on 23/08/17.
//

#pragma once

#include "Grid.hpp"
#include "Player.hpp"
#include "GameConfiguration.hpp"

class Game {
public:
    Game(GameConfiguration& configuration);
    std::pair<Player, Player> &players();
    GameConfiguration const & configuration() const;
protected:

private:
    GameConfiguration _configuration;
    std::pair<Player, Player> _players;
};