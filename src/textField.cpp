
#include "./textField.h"

extern Font font1;

textField::textField(Rectangle rec)
{
    textBox = rec;
}
bool textField::handleInput()
{
    if (!isVisible)
    {
        return false;
    }
	
	bool eventDetected = false;
    
	if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
	else mouseOnText = false;

	if (mouseOnText)
	{
		SetMouseCursor(MOUSE_CURSOR_IBEAM);

		int key = GetCharPressed();

		while (key > 0)
		{

			if ((key >= 32) && (key <= 125))
			{
				input += key;
			}

			key = GetCharPressed();
			eventDetected = true;
		}

		if (IsKeyPressed(KEY_BACKSPACE))
		{
			if (input.size() > 0)
			{
				input.pop_back();
			}
			eventDetected = true;
			
		}
	}
	else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

	return eventDetected;
}
void textField::drawTextField()
{
    if (!isVisible)
    {
        return;
    }

	DrawRectangleRec(textBox, LIGHTGRAY);
	if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
	else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

	//DrawTextPro(font1,label.c_str(),(Vector2){7 + rectangleX, rectangleY + 15},{0,0},0,15,0,BLACK);
	DrawText(input.c_str(), (int)textBox.x + 5, (int)textBox.y + 4, 38, MAROON);
}
int textField::inputToNumber()
{
    return std::stoi(input);
}

void textField::setVisible(bool set)
{
    isVisible = set;
}