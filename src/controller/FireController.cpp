//
// Created by bdardenn on 14/09/17.
//

#include "FireController.hpp"
#include "../model/Cell.hpp"


const std::string &FireController::DEFAULT_MESSAGE = "← → ↓ ↑: Move\tEnter: Fire\tq: Quit";


FireController::FireController(GameWindow &window, GridWindow *gridWindow) : AController(window, *gridWindow), _gridWindow(gridWindow) {

}

void FireController::handleKey(int key) {
    _gameWindow.status(DEFAULT_MESSAGE);

    int x, y;
    _gridWindow->_getyx(y, x);

    switch (key) {
        case KEY_UP:
            _gridWindow->move(y - 1, x);
            break;
        case KEY_DOWN:
            _gridWindow->move(y + 1, x);
            break;
        case KEY_LEFT:
            _gridWindow->move(y, x - 1);
            break;
        case KEY_RIGHT:
            _gridWindow->move(y, x + 1);
            break;
        case '\n':
            _gridWindow->grid().shoot(y,x);
            showOutcome(_gridWindow->grid()(y,x));
            _shotsLeft--;
            break;
        default:
            if (_next)
                _next->handleKey(key);
    }

    _gridWindow->redraw();
    _gridWindow->refresh();
}

void FireController::enable() {
    _shotsLeft = _shotsPerTurn;
    _gridWindow->move(0, 0);
    _gridWindow->redraw();
    _gameWindow.status(DEFAULT_MESSAGE);
}

bool FireController::finished() const {
    return !_shotsLeft;
}

void FireController::showOutcome(Cell hitCell) {
    if(hitCell.ship && hitCell.ship->sunk() ){
        _gameWindow.status("You sunk the enemy's " + hitCell.ship->name() + "!", MessageType::warning);
    } else if(hitCell.ship) {
        _gameWindow.status("You hit an enemy ship!", MessageType::warning);
    }
}
