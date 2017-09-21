//
// Created by bdardenn on 11/09/17.
//

#pragma once

#include "GridWindow.hpp"

class VisibleGridWindow : public GridWindow {
public:
    VisibleGridWindow(NCursesWindow &par, Player &player, int y, int x);
    void redraw() override;

public:
protected:
private:
    void printPlacingShip(std::shared_ptr<Ship> placingShip);
};
