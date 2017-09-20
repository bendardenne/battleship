//
// Created by bdardenn on 20/09/17.
//

#include "AIFireController.hpp"

AIFireController::AIFireController(GameWindow &window, GridWindow& gridWindow) : AController(window, gridWindow),
                                                                                 _ai(gridWindow.grid()),
                                                                                 _gridWindow(gridWindow) {

}

void AIFireController::enable() {
    _gridWindow.move(0, 0);
    _gridWindow.redraw();
}

bool AIFireController::finished() const {
    return false;
}


void AIFireController::control() {
    std::string msg;
    std::pair<int, int> target = _ai.shoot();
    msg += std::to_string(target.second) + " " + std::to_string(target.first);

    target = _ai.shoot();
    msg += std::to_string(target.second) + " " + std::to_string(target.first);

    target = _ai.shoot();
    msg += std::to_string(target.second) + " " + std::to_string(target.first);


    _gameWindow.status(msg);
    _gridWindow.redraw();
}

void AIFireController::handleKey(int key) {

}
