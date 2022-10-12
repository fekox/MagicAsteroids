#pragma once
#include "Objects/Asteroid.h"
#include "Objects/PlayerShip.h"
#include "Objects/Bullet.h"

struct SubMenu
{
	Vector2 pos;

	float width;
	float height;

	Texture texture;

	bool isActive;
};

struct Button
{
	Vector2 pos;

	float width;
	float height;

	int size;

	Texture texture;

	Color color;
};

void Input(bool& gameOn);
void Update();
void Collision();
void Draw();
void UnloadData();

void ShipMovement();
void BulletMovement();
void AsteroidMovement(Asteroid asteroids[], int const maxObjects);
void MouseMovement();

void AsteroidCollision(Ship& player, Asteroid asteroids[], int const maxObjects);
void BulletCollision();
bool CheckCollsisionCirCir(Vector2 Obj1Pos, float obj1Radius, Vector2 obj2Pos, float obj2Radius);
void ObjCollisionLimit(Vector2& shipPosition);
void AsteroidCollisionLimit(Asteroid asteroids[]);
void BulletCollisonLimit();
void PauseMenuCollisions();
void RestarGameMenuCollisions();

void RespawnAsteroids();

void DrawGame();
void DrawRestarGameMenu();
void DrawPauseMenu();

void RestartGame();
