
#include <iostream>
#include "raylib.h"

class button
{
public:
    Rectangle rec;
    std::string text = "";
    bool isVisible = true;
    int font = 10;
    button(Rectangle rec , std::string text , int font);
    void setVisible(bool set);
    bool onHover();
    bool onclick();
    void drawButton();
};