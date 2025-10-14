// Drawable 
// abstract base class
#pragma once

// Forward declaration
class Ili9341Display;

class Drawable {
public:
    virtual void draw(Ili9341Display& display) const = 0;
    virtual ~Drawable() = default; // Define the virtual destructor explicitly.
};