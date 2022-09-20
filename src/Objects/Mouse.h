#pragma once

struct Mouse
{
	Vector2 position;

	float width;

	float height;
};

Mouse CreateMouse();

Rectangle CreateRectangleMouse(Mouse& mouse);

Vector2 CreateRecOriginMouse(Rectangle& mouseRec);

void DrawMouse(Mouse& mouse, Rectangle& mouseRec);