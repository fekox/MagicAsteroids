#include "raylib.h"
#include "Objects/PlayerShip.h"

Ship CreateShip()
{
	Ship playerShip;

	playerShip.posX = 0;
	playerShip.posY = 0;

	playerShip.height = 0;
	playerShip.widht = 0;

	playerShip.speed = 0;

	playerShip.lifes = 0;

	playerShip.points = 0;

	playerShip.rotation = 0;

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