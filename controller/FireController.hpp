//
// Created by bdardenn on 14/09/17.
//

#pragma once


#include "AController.hpp"

class FireController : public AController {
public:
    FireController(GameWindow &window, GridWindow *gridWindow);
    void handleKey(int key) override;
    void enable() override;
    bool finished() const override;
public:
protected:
private:
    static const std::string &DEFAULT_MESSAGE;

    GridWindow* _gridWindow;
    unsigned _shotsPerTurn = 3;     //TODO get from config
    unsigned _shotsLeft;

    void showOutcome(Cell hitCell);
};
