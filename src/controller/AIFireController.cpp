//
// Created by bdardenn on 20/09/17.
//

#include "AIFireController.hpp"

AIFireController::AIFireController(GameWindow &window, GridWindow& gridWindow) : AController(window, gridWindow),
                                                                                 _ai(gridWindow.grid()),
                                                                                 _gridWindow(gridWindow) {

}

void AIFireController::enable() {
    _gridWindow._move(0, 0);
    _gridWindow.redraw();
}

bool AIFireController::finished() const {
    return false;
}


void AIFireController::control() {
    std::string msg;

    for(auto i = 0; i < _shotsPerTurn; i++){
        _ai.shoot();
    }

    _gridWindow.redraw();
}

void AIFireController::handleKey(int  /*key*/) {

}
