#pragma once

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
#include <string>
#include <vector>

// Forward declaration due to mutual inclusion.
class BattleshipApplication;

class Menu : public NCursesMenu {

public:
    Menu(BattleshipApplication* application);
    int virtualize(int c) override;
    void On_Menu_Termination() override;

private:
    BattleshipApplication* const _application;

    class QuitAction;
    class StartGameAction;
    class ShowConfigAction;
};
