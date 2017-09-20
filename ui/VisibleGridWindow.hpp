//
// Created by bdardenn on 11/09/17.
//

#pragma once

#include "GridWindow.hpp"

class VisibleGridWindow : public GridWindow {
public:
    VisibleGridWindow(NCursesWindow &par, Player &player, int y, int x);
    void redraw() override;
    int move(int, int) override;
//    void _getyx(int &, int &) override;

public:
protected:
private:
    void printPlacingShip(const std::shared_ptr<Ship> placingShip);
};
