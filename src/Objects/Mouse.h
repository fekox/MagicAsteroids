#pragma once

struct Mouse
{
	Vector2 position;

	float width;

	float height;

	Texture2D texture;
};

Mouse CreateMouse();

Rectangle GetRecMouse(Mouse& mouse, float mouseWidth, float mouseHeight);

Vector2 CreateRecOriginMouse(Rectangle& mouseRec);

void DrawMouse(Mouse& mouse, Rectangle& mouseRec);