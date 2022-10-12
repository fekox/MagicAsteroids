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
void DrawGame();

void MouseMovement();
void ShipMovement();
void AsteroidMovement(Asteroid asteroids[], int const maxObjects);
void BulletMovement();

void ObjCollisionLimit(Vector2& shipPosition);
void AsteroidCollisionLimit(Asteroid asteroids[]);
void BulletCollisonLimit();
bool CheckCollsisionCirCir(Vector2 Obj1Pos, float obj1Radius, Vector2 obj2Pos, float obj2Radius);
void AsteroidCollision(Ship& player, Asteroid asteroids[], int const maxObjects);
void BulletCollision();

void RespawnAsteroids();

void DrawPauseMenu();
void PauseMenuCollisions();

void DrawRestarGameMenu();
void RestartGame();
void RestarGameMenuCollisions();

void UnloadData();
