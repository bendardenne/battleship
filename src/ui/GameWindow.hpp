//
// Created by bdardenn on 08/09/17.
//

#pragma once

#include <cursesw.h>

#include "../model/Game.hpp"
#include "GridWindow.hpp"
#include "StatusBar.hpp"
#include "MessageType.hpp"

class AController;

class GameWindow : public NCursesColorWindow {
    static const int SEPARATION = 5;

public:
    static const int OWN_GRID_COLOR = 7;             // a COLOR_PAIR index;
    static const int OPPONENT_GRID_COLOR = OWN_GRID_COLOR + 1;

    GameWindow(NCursesWindow& par, Game& game);
    ~GameWindow() override;

    void run();
    void quit();
    void setController(AController *controller);
    void status(std::string const &msg, MessageType type = MessageType::info);
protected:
private:
    Game _game;
    std::pair<GridWindow*, GridWindow*> _gridWindows;
    StatusBar _statusBar;

    AController* _controller;
};
