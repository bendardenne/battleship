
//
// Created by bdardenn on 23/08/17.
//

#pragma once

#include <string>
#include "GameConfiguration.hpp"
#include "Grid.hpp"

class Player {
public:
    Player(GameConfiguration &name, std::string& string);

    const Grid & grid() const;
    Grid &grid();

    std::string const name() const;

protected:
private:
    std::string _name;
    Grid _grid;
};
