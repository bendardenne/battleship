//
// Created by bdardenn on 08/09/17.
//

#include <fstream>

#include "GameWindow.hpp"
#include "HiddenGridWindow.hpp"
#include "VisibleGridWindow.hpp"
#include "../controller/PlaceShipsController.hpp"
#include "../controller/DefaultController.hpp"
#include "../controller/FireController.hpp"
#include "../controller/AIFireController.hpp"


GameWindow::GameWindow(NCursesWindow &par, Game &game) : NCursesColorWindow(par, par.lines(), par.cols(), 0, 0),
                                                         _game(game),
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
    auto *placeShips = new PlaceShipsController(*this, *_gridWindows.first);
    placeShips->append(new DefaultController(*this, *_gridWindows.first));
    setController(placeShips);
    delete placeShips;

    auto *fire = new FireController(*this, *_gridWindows.second);
    fire->append(new DefaultController(*this, *_gridWindows.second));

    auto ai = new AIFireController(*this, *_gridWindows.first);
    ai->append(new DefaultController(*this, *_gridWindows.first));

    setController(fire);

    while (!_game.over()) {
        if(_controller == fire) {
            setController(ai);
        } else if (_controller == ai){
            setController(fire);
        } else {
            return;     // Shouldn't happen
        }
    }

    delete fire;
    delete ai;
}


void GameWindow::setController(AController *controller) {
    _controller = controller;
    _controller->control();
}

void GameWindow::quit() {
    // TODO
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
