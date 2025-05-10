
#ifndef TEXT_FIELD
#define TEXT_FIELD

#include <iostream>
#include "raylib.h"

class textField
{
    public:

    Rectangle textBox;
    std::string input = "";
    bool mouseOnText = false;
    bool isVisible = true;

    textField(Rectangle rec);
    bool handleInput();
    void drawTextField();
    int inputToNumber();
    void setVisible(bool set);


};

#endif
