//
// Created by bdardenn on 08/09/17.
//

#include <fstream>
#include "GameWindow.hpp"

#include "../controller/PlaceShipsController.hpp"
#include "../controller/DefaultController.hpp"
#include "../controller/FireController.hpp"
#include "../ai/RandomShipPlacer.hpp"
#include "HiddenGridWindow.hpp"


GameWindow::GameWindow(NCursesWindow &par, Game &game) : NCursesColorWindow(par, par.lines(), par.cols(), 0, 0),
                                                         _game(game),
                                                         _gridWindows(),
                                                         _statusBar(*this) {

    _gridWindows.first = new VisibleGridWindow(*this, game.players().first, 0, 0);
    _gridWindows.second = new HiddenGridWindow(*this, game.players().second, 0,
                                               _gridWindows.first->width() + SEPARATION);

    _gridWindows.first->mvwin(height() / 2 - _gridWindows.first->height() / 2,
                              width() / 2 - _gridWindows.first->width() - SEPARATION / 2);

    _gridWindows.second->mvwin(height() / 2 - _gridWindows.second->height() / 2,
                               width() / 2 + SEPARATION / 2);

    _gridWindows.first->refresh();
    _gridWindows.second->redraw();
    _gridWindows.second->refresh();
    _statusBar.refresh();
    keypad(true);
}


GameWindow::~GameWindow() {
    delete _gridWindows.first;
    delete _gridWindows.second;
}


void GameWindow::run() {
    AController *placeShips = new PlaceShipsController(*this, _gridWindows.first);
    placeShips->append(new DefaultController(*this));
    setController(placeShips);

    // Queue of controllers to enable successively
    std::queue<AController *> controllers;
    AController *fire = new FireController(*this, _gridWindows.second);
    fire->append(new DefaultController(*this));

    controllers.push(fire);

    while (_playing) {
        if (_controller->finished()) {
            if (!controllers.empty()) {
                setController(controllers.front());
                controllers.pop();
            } else {
                quit();
            }
        }

        int ch = _gridWindows.first->getch();
        _controller->handleKey(ch);
    }
}


void GameWindow::setController(AController *controller) {
    // TODO is this ok?
    if (_controller) {
        delete _controller;
    }
    _controller = controller;
    _controller->enable();
}

void GameWindow::quit() {
    _playing = false;
}

void GameWindow::status(std::string const &msg, MessageType type) {
    _statusBar.clear();

    switch (type) {
        case info:
            _statusBar.bkgd(COLOR_PAIR(6));
            break;
        case warning:
            _statusBar.bkgd(COLOR_PAIR(5));
            break;
        case error:
            _statusBar.bkgd(COLOR_PAIR(8));
            break;
    }

    _statusBar.addstr(msg.c_str());
    _statusBar.refresh();
}
