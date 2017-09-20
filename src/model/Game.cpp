//
// Created by bdardenn on 23/08/17.
//

#include "Game.hpp"
#include "../ai/RandomShipPlacer.hpp"

Game::Game(GameConfiguration &configuration) : _configuration(configuration),
                                               _players(Player(configuration, configuration.player1),
                                                        Player(configuration, configuration.player2)) {

    RandomShipPlacer placer;
    placer.placeShips(players().second.grid());
}

std::pair<Player, Player>& Game::players() {
    return _players;
}

GameConfiguration const &Game::configuration() const {
    return _configuration;
}

