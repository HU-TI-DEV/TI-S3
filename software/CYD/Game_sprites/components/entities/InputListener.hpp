/*! \brief Headerfile for InputListener
*
* Minimal base for “input" in the world.
*
* An interface for controllable things.
*/
#pragma once
#include "AnalogButtonReader.hpp" // for Button enum

class InputListener {
public:
    virtual ~InputListener() = default;
    virtual void onButton(Button b) = 0;
};
