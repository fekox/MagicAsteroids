#include "raylib.h"
#include "Objects/Mouse.h"

Mouse CreateMouse() 
{
	Mouse mouse;

	mouse.position.x = 0;
	mouse.position.y = 0;

	mouse.width = 20;
	mouse.height = 20;

	return mouse;
}

Rectangle CreateRectangleMouse(Mouse& mouse)
{
	Rectangle mouseRec;

	mouseRec.x = mouse.position.x;
	mouseRec.y = mouse.position.y;

	mouseRec.width = mouse.width;
	mouseRec.height = mouse.height;

	return mouseRec;
}

Vector2 CreateRecOriginMouse(Rectangle& mouseRec)
{
	Vector2 originRec;

	originRec.x = mouseRec.width /2;
	originRec.y = mouseRec.width /-2;

	return originRec;
}

void DrawMouse(Mouse& mouse, Rectangle& mouseRec)
{
	DrawRectanglePro(CreateRectangleMouse(mouse), CreateRecOriginMouse(mouseRec), 0.0f, YELLOW);
}