//
// Created by bdardenn on 23/08/17.
//

#include "Game.hpp"
#include "../ai/RandomShipPlacer.hpp"

#include <algorithm>

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

bool Game::over() {
    auto sunk = [](const std::shared_ptr<Ship> ship){
        return ship->sunk();
    };

    const std::vector<std::shared_ptr<Ship>> &fleet1 = _players.first.grid().fleet();
    const std::vector<std::shared_ptr<Ship>> &fleet2 = _players.second.grid().fleet();

    return std::all_of(fleet1.begin(), fleet1.end(), sunk) || std::all_of(fleet2.begin(), fleet2.end(), sunk);
}

