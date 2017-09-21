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
    void init(bool bColors) override;
    int titlesize() const override;
    void title() override ;

public:
    BattleshipApplication();

    void handleArgs(int argc, char *argv[]) override ;
    int run() override;
    void showTitleScreen();
};
