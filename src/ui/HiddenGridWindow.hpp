//
// Created by bdardenn on 11/09/17.
//

#pragma once

#include "GridWindow.hpp"

class HiddenGridWindow : public GridWindow {
public:
    HiddenGridWindow(NCursesWindow &par, Player &player, int y, int x);
public:
    void redraw() override;
    int move(int, int) override;
//    void getyx(int &, int &) override;

protected:
private:

};
