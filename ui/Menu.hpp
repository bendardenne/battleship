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

#include "BattleshipApplication.hpp"


class Menu : public NCursesMenu {

public:
    Menu(BattleshipApplication* aBattleship);
    int virtualize(int c) override;
    void On_Menu_Termination() override;

private:
    BattleshipApplication* _application;
};
