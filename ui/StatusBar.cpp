//
// Created by bdardenn on 10/09/17.
//

#include "StatusBar.hpp"

StatusBar::StatusBar(NCursesWindow &parentWin)
        : NCursesColorWindow(parentWin, 1, parentWin.cols(), parentWin.lines() - 1, 0) {

    bkgd(COLOR_PAIR(6));
}
