//
// Created by bdardenn on 12/09/17.
//

#pragma once

#include <vector>
#include <string>
#include <cursesapp.h>

#include "../model/GameConfiguration.hpp"
#include "../model/Game.hpp"
#include "GameWindow.hpp"

class BattleshipApplication : public NCursesApplication {

private:
    std::vector<std::string> args;

protected:
    void init(bool bColors);
    virtual int titlesize() const;
    virtual void title();

public:
    BattleshipApplication();

    virtual void handleArgs(int argc, char *argv[]);
    virtual int run();
    void showTitleScreen();
};
