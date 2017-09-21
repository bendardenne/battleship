//
// Created by bdardenn on 11/09/17.
//

#include "VisibleGridWindow.hpp"

VisibleGridWindow::VisibleGridWindow(NCursesWindow &par, Player &player, int y, int x) : GridWindow(par, player,
                                                                                                    y, x) {}

void VisibleGridWindow::redraw() {
    int x, y;
    _getyx(y, x);
    GridWindow::redraw();

    for (size_t i = 0; i < grid().width(); i++) {
        for (size_t j = 0; j < grid().height(); j++) {
            Cell cell = grid()(j, i);
            if (cell.ship) {
                addch(winy(j), winx(i), cell.ship->sunk() ? 'X' : 'O');
            }
            if (cell.status == CellStatus::hit) {
                int color = cell.ship ? 8 : 4;  //was 8:7
                chgat(winy(j), winx(i), 1, A_BOLD, color);
            }
        }
    }

    std::shared_ptr<Ship> placingShip = grid().placing();

    if (placingShip) printPlacingShip(placingShip);

    // Replace cursor where it was.
    _move(y, x);
    syncup();
    refresh();
}


void VisibleGridWindow::printPlacingShip(const std::shared_ptr<Ship> placingShip) {
    chtype restore = attrget();
    attron(A_BOLD);

    ShipLocation location = grid().shipLocations().at(*placingShip);

    int x = winx(location.x);
    int y = winy(location.y);

    for (size_t i = 0; i < placingShip->length(); i++) {
        addch(y, x, 'O');

        // Highlight cell in red if collision
        std::shared_ptr<Ship> shipOnCell = _grid(gridy(y), gridx(x)).ship;
        if (shipOnCell)
            chgat(y, x, 1, A_BOLD, 8);

        location.orientation == horizontal ? x++ : y++;
    }

    attrset(restore);
}
