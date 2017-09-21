//
// Created by bdardenn on 08/09/17.
//

#include "AController.hpp"

AController::AController(GameWindow &window, NCursesWindow &eventSource) : _gameWindow(window),
                                                                           _eventSource(eventSource),
                                                                           _next(nullptr) {

}

void AController::append(AController *next) {
    _next = next;
}

AController::~AController() {
    delete _next;
}

void AController::control() {
    enable();

    while(enabled()) {
        int ch = _eventSource.getch();
        handleKey(ch);
    }
}

void AController::enable() {
    _enabled = true;
}

void AController::disable() {
    _enabled = false;
}

bool AController::enabled() const{
    return _enabled;
}
