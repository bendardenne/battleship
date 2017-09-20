//
// Created by bdardenn on 08/09/17.
//

#pragma once

#include "AController.hpp"

class DefaultController : public AController {
public:
    DefaultController(GameWindow& gameWindow);
    void handleKey(int key);
    bool finished() const override;
    void enable() override;
protected:
private:
};
