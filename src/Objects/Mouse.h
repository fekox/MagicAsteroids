#pragma once

struct Mouse
{
	Vector2 position;

	float width;

	float height;
};

Mouse CreateMouse();

Rectangle CreateRectangle(Mouse& mouse);

Vector2 CreateRecOrigin(Rectangle& rec);

void DrawMouse(Mouse& mouse, Rectangle& rec);