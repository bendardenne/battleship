//
// Created by bdardenn on 12/09/17.
//

#include <fstream>
#include <algorithm>

#include "BattleshipApplication.hpp"
#include "Menu.hpp"
#include "config/ConfigWindow.hpp"

BattleshipApplication::BattleshipApplication() : NCursesApplication(true) {
}

void BattleshipApplication::init(bool bColors) {
    NCursesApplication::init(bColors);
    init_pair(GameWindow::OWN_GRID_COLOR, COLOR_WHITE, COLOR_BLUE);
    init_pair(GameWindow::OPPONENT_GRID_COLOR, COLOR_WHITE, COLOR_RED);
    Root_Window->bkgd(COLOR_PAIR(1));
    Root_Window->keypad(true);
}

void BattleshipApplication::title() {
    std::string title("Luciad Services Battleship");

    titleWindow->bkgd(screen_titles());
    titleWindow->erase();
    titleWindow->addstr(0, titleWindow->cols() / 2 - title.length() / 2, title.c_str());
    titleWindow->noutrefresh();
}

int BattleshipApplication::titlesize() const {
    return 1;
}

void BattleshipApplication::handleArgs(int argc, char **argv) {
    args.assign(argv + 1, argv + argc);
}

int BattleshipApplication::run() {
    showTitleScreen();

    Menu menu(this);
    menu.mvwin(Root_Window->height() / 2 - menu.height() / 2, Root_Window->width() / 2 - menu.width() / 2);
    NCursesMenuItem *selected = menu();

    // TODO do this better? quit() method on the Application class?
    if (std::string(selected->name()) == "Quit") {
        return EXIT_SUCCESS;
    }

    GameConfiguration config = {.gridWidth = 10,
            .gridHeight = 10,
            .shotsPerTurn = 3,
            .player1 = "Player1",
            .player2 = "Player2"};

    if (std::string(selected->name()) == "Options") {
        ConfigWindow configWindow(config);
        configWindow.mvwin(Root_Window->height() / 2 - configWindow.height() / 2,
                           Root_Window->width() / 2 - configWindow.width() / 2);
        configWindow();
    }


    Game game(config);
    GameWindow gameWindow(*Root_Window, game);
    gameWindow.run();

    return EXIT_SUCCESS;
}

void BattleshipApplication::showTitleScreen() {
    int y = Root_Window->lines() / 4 - 3;
    std::string message = "LUCIAD SERVICES";
    Root_Window->addstr(y, Root_Window->cols() / 2 - message.size() / 2,
                        message.c_str());

    std::ifstream shipFile("battleship.txt");
    std::string line;

    // Count lines and find largest line
    size_t shipWidth = 0;
    size_t lines = 0;
    while (std::getline(shipFile, line)) {
        if (line.size() > shipWidth) shipWidth = line.size();
        lines++;
    }

    shipFile.clear();
    shipFile.seekg(0);
    y = Root_Window->lines() / 4;
    int x = Root_Window->cols() / 2 - shipWidth / 2;
    while (std::getline(shipFile, line)) {
        Root_Window->addstr(y++, x, line.c_str());
    }

    message = "Press any key to start...";
    Root_Window->addstr(y + 4, Root_Window->cols() / 2 - message.size() / 2,
                        message.c_str());

    Root_Window->getch();
    Root_Window->clear();
}
