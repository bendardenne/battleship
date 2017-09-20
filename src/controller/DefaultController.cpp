//
// Created by bdardenn on 08/09/17.
//

#include "DefaultController.hpp"


DefaultController::DefaultController(GameWindow &gameWindow, NCursesWindow& eventSource) : AController(gameWindow, eventSource) {

}

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

void DefaultController::enable() {

}

bool DefaultController::finished() const {
    return false;
}
