#include "Objects/Bullet.h"

Bullet CreateBullet()
{
	Bullet bullet;

	bullet.position.x = 0;
	bullet.position.y = 0;

	bullet.direction.x = 0;
	bullet.direction.y = 0;

	bullet.isMoving = false;

	bullet.isActive = false;


	bullet.radius = 10.0f;

	bullet.speed = 500.0f;

	bullet.texture = LoadTexture("resources/Sprites/Bullet.png");

	return bullet;
}

void DrawBullet(Bullet bullet)
{
	if (bullet.isActive == true)
	{
		DrawCircle(static_cast<int>(bullet.position.x), static_cast<int>(bullet.position.y), bullet.radius, RED);
		DrawTexture(bullet.texture, static_cast<int>(bullet.position.x - 12), static_cast<int>(bullet.position.y - 12), WHITE);
	}
}