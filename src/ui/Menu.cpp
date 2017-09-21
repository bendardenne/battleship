//
// Created by bdardenn on 02/08/17.
//

#include "Menu.hpp"


// TODO actual actions !
class QuitAction : public NCursesMenuItem {

public:
    QuitAction(const char *name, const char *desc = nullptr) : NCursesMenuItem(name, desc) { }

    bool action() override {
        return true;
    }
};


class StartGameAction : public NCursesMenuItem {
public:
    StartGameAction(const char *name, const char *desc = nullptr) : NCursesMenuItem(name, desc) {}

    bool action() override {
        return true;
    }
};


Menu::Menu(BattleshipApplication *aBattleship) : NCursesMenu(lines(), cols()), _application(aBattleship) {
    bkgd(COLOR_PAIR(1));
    set_mark("# ");
    setSpacing(8, 0, 0);

    // TODO is this deleted??
    auto items = new NCursesMenuItem *[4];
    items[0] = new StartGameAction("Start a Game", "Let's sink some ships!");
    items[1] = new QuitAction("Options");
    items[2] = new QuitAction("Quit");
    items[3] = new NCursesMenuItem();

    InitMenu(items, false, true);
    int w, h;
    scale(w, h); // Get the numer of rows and columns for this menu
    wresize(w, h);  // shrink to smallest required dimension
}

void Menu::On_Menu_Termination() {
    hide();
}

int Menu::virtualize(int c) {

    // TODO
    // Intercept Q to Quit menu
    switch (c) {
//        case 'q':
//            return MAX_COMMAND + 1;    this means "enter" on current entry
        default:
            return NCursesMenu::virtualize(c);
    }
}