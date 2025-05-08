
#include "./button.h"



button::button(Rectangle rec , std::string text , int font)
{
    this->rec = rec;
    this->text = text;
    this->font = font;
}
void button::setVisible(bool set)
{
    isVisible = set;
}
bool button::onHover()
{
    return CheckCollisionPointRec(GetMousePosition(),rec);
}   
bool button::onclick()
{
    return onHover() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}
void button::drawButton()
{
	DrawRectangleRec(rec , LIGHTGRAY);
	DrawText(text.c_str() , (rec.x + rec.width/2) - MeasureText(text.c_str(), font)/2 , rec.y + 5 , font , BLACK);
    if (onHover())
        DrawRectangleLinesEx(rec , 2 , RED);
    else
        DrawRectangleLinesEx(rec , 2 , DARKGRAY);

}