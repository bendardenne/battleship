//
// Created by bdardenn on 08/09/17.
//

#include "DefaultController.hpp"


void DefaultController::handleKey(int key) {
    switch (key) {
        case 'q':
            _gameWindow.quit();
            break;
        default:
            if (_next)
                _next->handleKey(key);
    }
}

DefaultController::DefaultController(GameWindow &gameWindow) : AController(gameWindow) {

}

void DefaultController::enable() {

}

bool DefaultController::finished() const {
    return false;
}
