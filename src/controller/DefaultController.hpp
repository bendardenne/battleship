//
// Created by bdardenn on 08/09/17.
//

#pragma once

#include "AController.hpp"

class DefaultController : public AController {
public:
    DefaultController(GameWindow& gameWindow, NCursesWindow& eventSource);
    void handleKey(int key) override;
    bool finished() const override;
    void enable() override;
protected:
private:
};
