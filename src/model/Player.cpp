//
// Created by bdardenn on 23/08/17.
//

#include "Player.hpp"
#include "GameConfiguration.hpp"

Player::Player(GameConfiguration &configuration, std::string &name) : _name(name),
                                                                      _grid(Grid(configuration.gridWidth,
                                                                                 configuration.gridHeight)) {

}

Grid const & Player::grid() const {
    return _grid;
}

Grid & Player::grid() {
    return _grid;
}

std::string const Player::name() const {
    return _name;
}
