//
// Created by bdardenn on 08/09/17.
//

#pragma once

#include "../ui/GameWindow.hpp"

class AController {
public:
    virtual void enable() = 0;
    virtual bool finished() const = 0;
    virtual void handleKey(int key) = 0;

    virtual void control();

    void append(AController* next);

    virtual ~AController();
protected:
    AController(GameWindow& window, NCursesWindow& eventSource);

    GameWindow& _gameWindow;
    NCursesWindow& _eventSource;
    AController* _next;
private:

};