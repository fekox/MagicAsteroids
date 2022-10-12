#include "raylib.h"

#include "Objects/Mouse.h"

Mouse CreateMouse() 
{
	Mouse mouse;

	mouse.position.x = 0;
	mouse.position.y = 0;

	mouse.width = 20.0f;
	mouse.height = 20.0f;

	mouse.texture = LoadTexture("resources/Sprites/Cross.png");

	return mouse;
}

Rectangle GetRecMouse(Mouse& mouse)
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
	DrawRectanglePro(GetRecMouse(mouse), CreateRecOriginMouse(mouseRec), 0.0f, BLANK);
	DrawTexture(mouse.texture, static_cast<int>(mouse.position.x - 16), static_cast<int>(mouse.position.y -16), WHITE);
}