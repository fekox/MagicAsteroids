#include "raylib.h"
#include "Objects/Mouse.h"

Mouse CreateMouse() 
{
	Mouse mouse;

	mouse.position.x = 0;
	mouse.position.y = 0;

	mouse.width = 20.0f;
	mouse.height = 20.0f;

	return mouse;
}

Rectangle GetRecMouse(Mouse& mouse, float mouseWidth, float mouseHeight)
{
	return Rectangle{ mouse.position.x - mouse.width / 2, mouse.position.y - mouse.height / 2, mouse.width, mouse.height};
}

Vector2 CreateRecOriginMouse(Rectangle& mouseRec)
{
	Vector2 originRec;

	originRec.x = mouseRec.width /2 - mouseRec.width /2;
	originRec.y = mouseRec.height /2 - mouseRec.height /2;

	return originRec;
}

void DrawMouse(Mouse& mouse, Rectangle& mouseRec)
{
	DrawRectanglePro(GetRecMouse(mouse, mouse.width, mouse.height), CreateRecOriginMouse(mouseRec), 0.0f, YELLOW);
}