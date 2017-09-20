//
// Created by bdardenn on 20/09/17.
//

#pragma once


#include "AResettableField.hpp"

#include <vector>
#include <string>
#include <sstream>

template<typename T> class NumericResettableField : public AResettableField {
public:
    NumericResettableField(T& target, int cols, int lines, int x, int y) :
            AResettableField(cols, lines, x, y), _target(target), _originalValue(target){

    }

    void reset() override{
        set_value(to_str().c_str());
    }

    void apply() override {
        _target = from_str(value());
    }


protected:
    virtual T from_str(std::string value) {
        T tmp;
        std::istringstream ss(value);
        ss >> tmp;
        return tmp;
    }

    // Default implementation, overridable for non-primitive types for which std::to_string is not defined
    virtual std::string to_str() {
        return std::to_string(_originalValue);
    }

private:
    T&  _target;
    const T _originalValue;
};

