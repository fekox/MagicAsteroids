#include "Objects/Bullet.h"

Bullet CreateBullet()
{
	Bullet bullet;

	bullet.position.x = 0;
	bullet.position.y = 0;

	bullet.radius = 20.0f;

	bullet.speed = 90.0f;

	bullet.texture;

	return bullet;
}

void DrawBullet(Bullet bullet)
{
	DrawCircle(bullet.position.x, bullet.position.y, bullet.radius, GREEN);
}