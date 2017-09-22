//
// Created by bdardenn on 02/08/17.
//

#include "BattleshipApplication.hpp"
#include "Menu.hpp"

class Menu::QuitAction : public NCursesMenuItem {
public:
    QuitAction(BattleshipApplication* application, const char *name, const char *desc = nullptr)
            : NCursesMenuItem(name, desc), _application(application) {}

    bool action() override {
        _application->quit();
        return true;
    }

private:
    BattleshipApplication* const _application;
};


class Menu::StartGameAction : public NCursesMenuItem {
public:
    StartGameAction(BattleshipApplication* application, const char *name, const char *desc = nullptr) :
            NCursesMenuItem(name, desc), _application(application) {}

    bool action() override {
        _application->startGame();
        return true;
    }


private:
    BattleshipApplication* const _application;
};

class Menu::ShowConfigAction : public NCursesMenuItem {
public:
    ShowConfigAction(BattleshipApplication* application, const char *name, const char *desc = nullptr) :
            NCursesMenuItem(name, desc), _application(application) {}

    bool action() override {
        _application->showConfig();
        return true;
    }

private:
    BattleshipApplication* const _application;
};


Menu::Menu(BattleshipApplication *application) : NCursesMenu(lines(), cols()), _application(application) {
    bkgd(COLOR_PAIR(1));
    set_mark("# ");
    setSpacing(8, 0, 0);

    // TODO is this deleted??
    auto items = new NCursesMenuItem *[4];
    items[0] = new StartGameAction(_application, "Start a Game", "Let's sink some ships!");
    items[1] = new ShowConfigAction(_application, "Options");
    items[2] = new QuitAction(_application, "Quit");
    items[3] = new NCursesMenuItem();

    InitMenu(items, false, true);
    int w, h;
    scale(w, h); // Get the numer of rows and columns for this _menu
    wresize(w, h);  // shrink to smallest required dimension
}

void Menu::On_Menu_Termination() {
    hide();
}

int Menu::virtualize(int c) {

    // TODO
    // Intercept Q to Quit _menu
    switch (c) {
//        case 'q':
//            return MAX_COMMAND + 1;    this means "enter" on current entry
        default:
            return NCursesMenu::virtualize(c);
    }
}
