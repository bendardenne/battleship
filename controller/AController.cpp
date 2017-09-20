//
// Created by bdardenn on 08/09/17.
//

#include "AController.hpp"

AController::AController(GameWindow &window) : _gameWindow(window), _next(nullptr) {

}

void AController::append(AController *next) {
    _next = next;
}

AController::~AController() {
    if (_next) delete _next;
}
