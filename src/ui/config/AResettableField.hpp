//
// Created by bdardenn on 20/09/17.
//

#pragma once


#include <cursesf.h>

class AResettableField : public NCursesFormField {
public:

    AResettableField(int lines, int cols, int y, int x) : NCursesFormField(lines, cols, y, x) {    }

    virtual void reset() = 0;
    virtual void apply() = 0;
protected:
private:
};

