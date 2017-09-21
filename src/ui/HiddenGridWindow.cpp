//
// Created by bdardenn on 11/09/17.
//

#include "HiddenGridWindow.hpp"

HiddenGridWindow::HiddenGridWindow(NCursesWindow &par, Player &player, int y, int x) : GridWindow(par, player, y, x) {
    keypad(true);
}

void
HiddenGridWindow::redraw() {
    int x, y;
    _getyx(y, x);
    GridWindow::redraw();

    for (size_t i = 0; i < grid().width(); i++) {
        for (size_t j = 0; j < grid().height(); j++) {
            Cell cell = grid()(j, i);
            if (cell.ship && cell.ship->sunk()) {
                addch(winy(j), winx(i), 'X');
            }
            if (cell.status == CellStatus::hit) {
                int color = cell.ship ? 8 : 4;
                chgat(winy(j), winx(i), 1, A_BOLD, color);
            }
        }
    }

    // Replace cursor where it was.
    _move(y, x);
    syncup();
}