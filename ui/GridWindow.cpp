//
// Created by bdardenn on 08/09/17.
//

#include "GridWindow.hpp"
#include "../model/Player.hpp"

GridWindow::GridWindow(NCursesWindow &par, Player &player, int y, int x) :
        NCursesColorWindow(par, player.grid().height() + 2, player.grid().width() + 2, y, x),
        _player(player),
        _grid(player.grid()) {
    keypad(true);
    redraw();
    this->move(0, 0);
}


int GridWindow::move(int aY, int aX) {
    // Guard against moves on the border.
    if( aY < 0 || aX < 0 || aY >= height() - 2 || aX >= width() - 2 )
        return ERR;

    int x = winx(aX);
    int y = winy(aY);

    int ret = NCursesColorWindow::move(y, x);
    cursyncup();
    return ret;
}


void GridWindow::redraw() {
    clear();
    border();
}


Grid& GridWindow::grid() {
    return _grid;
}

// Maps an x coordinate from the ncurses window to a coordinate on the Grid.
size_t const GridWindow::gridx(size_t const x) const {
    return x - 1;
}

// Maps an y coordinate from the ncurses window to a coordinate on the Grid.
size_t const GridWindow::gridy(size_t const y) const {
    return y - 1;
}

size_t const GridWindow::winx(size_t const x) const {
    return x + 1;
}


size_t const GridWindow::winy(size_t const y) const {
    return y + 1;
}

void GridWindow::_getyx(int &y, int &x) {
    NCursesColorWindow::getyx(y, x);
    y = gridy(y);
    x = gridx(x);
}
