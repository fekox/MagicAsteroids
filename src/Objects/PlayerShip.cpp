#include "raylib.h"
#include "Objects/PlayerShip.h"

Ship CreateShip()
{
	Ship playerShip;

	playerShip.posX = GetScreenWidth() / 2;
	playerShip.posY = GetScreenWidth() / 2;

	playerShip.height = 40.0f;
	playerShip.widht = 40.0f;

	playerShip.speed = 500.0f;

	playerShip.lifes = 3;

	playerShip.points = 0;

	return playerShip;
}

void DrawShip()
{

}

void AddPoint()
{

}

int GetPoint()
{


	return 1;
}