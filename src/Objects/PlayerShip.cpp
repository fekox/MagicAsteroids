#include <iostream>
#include "raylib.h"
#include "Objects/PlayerShip.h"

using namespace std;

Ship CreateShip()
{
	Ship playerShip;

	playerShip.position.x = GetScreenWidth() / 2;
	playerShip.position.y = GetScreenHeight() / 2;

	playerShip.direction.x = 0;
	playerShip.direction.y = 0;

	playerShip.aceleration.x = 100.0f;
	playerShip.aceleration.y = 100.0f;

	playerShip.height = 60.0f;
	playerShip.widht = 60.0f;

	playerShip.rotation = 0;

	playerShip.speed = 100.0f;

	playerShip.lifes = 3;

	playerShip.points = 0;

	playerShip.texture = LoadTexture("resources/Ship.png");

	return playerShip;
}

Rectangle GetRec(Ship& playerShip, float playerWidth, float playerHeight)
{
	return Rectangle{ playerShip.position.x - playerWidth / 2, playerShip.position.y - playerHeight / 2, playerWidth, playerHeight };
}

void DrawShip(Ship& playerShip, Vector2& shipOriginRec)
{
	DrawRectanglePro(GetRec(playerShip, playerShip.widht, playerShip.height), shipOriginRec, playerShip.rotation, RED);
	DrawTexturePro(playerShip.texture, Rectangle{0,0, (float)playerShip.texture.width, (float)playerShip.texture.height}, Rectangle{playerShip.position.x - 30, playerShip.position.y - 30, playerShip.widht, playerShip.height}, shipOriginRec, playerShip.rotation, WHITE);
}

void AddPoint()
{

}

int GetPoint()
{


	return 1;
}