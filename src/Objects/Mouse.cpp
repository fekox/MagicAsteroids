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

Rectangle CreateRectangle(Mouse& mouse)
{
	Rectangle rec;

	rec.x = mouse.position.x;
	rec.y = mouse.position.y;

	rec.width = mouse.width;
	rec.height = mouse.height;

	return rec;
}

Vector2 CreateRecOrigin(Rectangle& rec)
{
	Vector2 originRec;

	originRec.x = rec.width /2;
	originRec.y = rec.width /-2;

	return originRec;
}

void DrawMouse(Mouse& mouse, Rectangle& rec)
{
	DrawRectanglePro(CreateRectangle(mouse), CreateRecOrigin(rec), 0.0f, YELLOW);
}