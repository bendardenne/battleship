//
// Created by bdardenn on 18/09/17.
//
#pragma once


#include <cursesf.h>
#include <vector>
#include "../../model/GameConfiguration.hpp"
#include "AResettableField.hpp"

class ConfigWindow : public NCursesForm{
public:
    ConfigWindow(GameConfiguration& config);
    int virtualize(int c) override;
public:
protected:
private:
    std::vector<AResettableField*> configFields;
    NCursesFormField **createFields(GameConfiguration &configuration);
    void resetFields();
    void apply();
};



