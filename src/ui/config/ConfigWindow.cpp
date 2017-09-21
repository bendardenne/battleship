//
// Created by bdardenn on 18/09/17.
//

#include "ConfigWindow.hpp"
#include "NumericResettableField.hpp"

#include <algorithm>
#include <iostream>

class Label : public NCursesFormField {
public:
    Label(const std::string& label, int y, int x) : NCursesFormField(1, label.length(), y, x) {
        set_value(label.c_str());
        options_off(O_EDIT | O_ACTIVE);
        bkgd(COLOR_PAIR(1));
    }
};

ConfigWindow::ConfigWindow(GameConfiguration &config) : NCursesForm(createFields(config), 0, 0, 0, 0, true, true) {
    keypad(true);

    wresize(lines() / 2 , cols() / 2);
    boldframe("Game configuration");
    bkgd(COLOR_PAIR(1));
}


int ConfigWindow::virtualize(int c) {
    switch (c) {
        case '\n':
            apply();
            return MAX_COMMAND + 1;
        case '\t':
        case KEY_DOWN:
            return REQ_NEXT_FIELD;
        case KEY_UP:
            return REQ_PREV_FIELD;
        case 'r':
            resetFields();
            break;
        case 'q':
            return MAX_COMMAND + 1;
    }

    return NCursesForm::virtualize(c);
}

NCursesFormField **ConfigWindow::createFields(GameConfiguration &config) {
    std::vector<std::string> labels = {"Grid width (5-20)",
                                       "Grid height (5-20)",
                                       "Shots per turn (1-5)"};


    long longestLabel = std::max_element(labels.begin(), labels.end(), [](std::string &a, std::string &b) {
        return a.size() < b.size();
    })->size();

    int offset = 5;
    int row = 0;
    auto col = static_cast<int>(longestLabel + offset);

    std::vector<NCursesFormField *> *fields = new std::vector<NCursesFormField *>{
            new NumericResettableField<typeof(config.gridWidth)>(config.gridWidth, 1, 3, row++, col),
            new NumericResettableField<typeof(config.gridHeight)>(config.gridHeight, 1, 3, row++, col),
            new NumericResettableField<typeof(config.shotsPerTurn)>(config.shotsPerTurn, 1, 3, row++, col),
    };


    row = 0;
    for (const std::string& label : labels) {
        fields->push_back(new Label(label, row++, 0));
    }


    (*fields)[0]->set_value(std::to_string(config.gridWidth).c_str());
    (*fields)[1]->set_value(std::to_string(config.gridHeight).c_str());
    (*fields)[2]->set_value(std::to_string(config.shotsPerTurn).c_str());

//    Integer_Field dimensionFieldType = Integer_Field(2, 5, 20);

    // Terminating empty field
    fields->push_back(new NCursesFormField());

    return &(*fields)[0];
}

void ConfigWindow::resetFields() {
    for(auto i = 0; i < count(); i++) {
        if(dynamic_cast<AResettableField*>((*this)[i]) != nullptr) {
            auto f = dynamic_cast<AResettableField*>((*this)[i]);
            f->reset();
        }
    }
}


void ConfigWindow::apply() {
    for(auto i = 0; i < count(); i++) {
        if(dynamic_cast<AResettableField*>((*this)[i]) != nullptr) {
            auto f = dynamic_cast<AResettableField*>((*this)[i]);
            f->apply();
        }
    }
}

