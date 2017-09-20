// Copyright (C) 2016 xaizek <xaizek@openmailbox.org>
//
// This application is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This application is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this application.  If not, see <http://www.gnu.org/licenses/>.

// Compilation: g++ list-picker.cpp -lncurses++w -lformw -lmenuw -lpanelw -lncursesw -o list-picker

#include <cursesapp.h>
#include <cursesm.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <clocale>

#include <algorithm>
#include <iostream>
#include <iterator>

#include "ui/Menu.hpp"


int main(int argc, char *argv[]) {
    std::setlocale(LC_ALL, "");

    int res;

    try {
        BattleshipApplication app;
        app.handleArgs(argc, argv);
        res = app();
    } catch (const NCursesException *e) {
        std::cerr << e->message << std::endl;
        res = e->errorno;
    } catch (const NCursesException &e) {
        std::cerr << e.message << std::endl;
        res = e.errorno;
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        res = EXIT_FAILURE;
    }

    return res;
}