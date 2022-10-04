#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Window/Game.h"
#include "Window/StartGame.h"
#include "Objects/PlayerShip.h"
#include "Objects/Asteroid.h"
#include "Objects/Mouse.h"
#include "Objects/Bullet.h"

using namespace std;

//Player
Ship playerShip;

//HealthBar
Vector2 healthBarPos;
Texture2D fullHealthBar;
Texture2D midHealthBar;
Texture2D lowHealthBar;

//Bullet
const int maxBullets = 10;
Bullet bullet[maxBullets];

//Mouse
Mouse mouse;

//Asteroid
const int maxAteroids = 10;
int asteroidsCount = 10;
Asteroid asteroid[maxAteroids];

const int maxNorAsteroids = 20;
int asteroidsNorCount = 0;
Asteroid asteroidNor[maxNorAsteroids];

const int maxSmallAsteroids = 60;
int asteroidsSmallCount = 0;
Asteroid asteroidSmall[maxSmallAsteroids];

int totalAsteoroidsCount = 6;

//Window
Texture2D background;
int screenWidth = 1024;
int screenHeight = 768;

//Font
Font gameFont;

//Timer
float timer = -0.1f;

void StartGame()
{
	InitGame();

	GameLoop();
}

void InitGame()
{
	//Window
	InitWindow(screenWidth, screenHeight, "Asteroids_FacundoSantos");
	SetWindowState(FLAG_VSYNC_HINT);
	gameFont = LoadFont("resources/Font/04B_30__.TTF");

	background = LoadTexture("resources/Sprites/Background.png");

	fullHealthBar = LoadTexture("resources/Sprites/FullHealthBar.png");
	midHealthBar = LoadTexture("resources/Sprites/MidHealthBar.png");
	lowHealthBar = LoadTexture("resources/Sprites/LowHealthBar.png");

	//Player
	playerShip = CreateShip();
	playerShip.shipRec = GetRec(playerShip, playerShip.widht, playerShip.height);
	playerShip.shipOriginRec.x = playerShip.shipRec.width / 2;
	playerShip.shipOriginRec.y = playerShip.shipRec.height / 2;

	//HealthBar
	healthBarPos.x = static_cast<float>(screenWidth /2.2);
	healthBarPos.y = 1;

	//Mouse
	HideCursor();
	mouse = CreateMouse();
	mouse.mouseRec = GetRecMouse(mouse);

	//Asteroid

	for (int i = 0; i < maxAteroids; i++)
	{
		asteroid[i].size = Size::Big;
		asteroid[i] = CreateAsteroid(asteroid[i].size);
	}

	for (int i = 0; i < maxNorAsteroids; i++)
	{
		asteroidNor[i].size = Size::Normal;
		asteroidNor[i] = CreateAsteroid(asteroidNor[i].size);
	}

	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		asteroidSmall[i].size = Size::Small;
		asteroidSmall[i] = CreateAsteroid(asteroidSmall[i].size);
	}

	//Bullet
	for (int i = 0; i < maxBullets; i++)
	{
		bullet[i] = CreateBullet();
	}
}

void GameLoop()
{
	SetExitKey(NULL);

	while (IsAlive(playerShip))
	{
		Input();
		Update();
		Collision();
		Draw();
	}

	UnloadData();
	CloseWindow();
}

void Input()
{
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		playerShip.shipDirNormalize = Vector2Normalize(playerShip.direction);

		playerShip.aceleration.x += playerShip.shipDirNormalize.x;
		playerShip.aceleration.y += playerShip.shipDirNormalize.y;
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		for (int i = 0; i < maxBullets; i++)
		{
			if (bullet[i].isActive == false)
			{
				if (!bullet[i].isMoving)
				{
					bullet[i].isActive = true;
					bullet[i].isMoving = true;

					bullet[i].direction.x = mouse.position.x - bullet[i].position.x;
					bullet[i].direction.y = mouse.position.y - bullet[i].position.y;

					bullet[i].direction = Vector2Normalize(bullet[i].direction);

					break;
				}
			}
		}
	}
}

void Update()
{
	shipMovement();
	asteroidMovement(asteroid, maxAteroids);
	asteroidMovement(asteroidNor, maxNorAsteroids);
	asteroidMovement(asteroidSmall, maxSmallAsteroids);
	bulletMovement();
	mouseMovement();
}

void Collision()
{
	AsteroidCollision(playerShip, asteroid);
	AsteroidCollision(playerShip, asteroidNor);
	AsteroidCollision(playerShip, asteroidSmall);

	BulletCollision();

	AsteroidCollisionLimit(asteroid);
	AsteroidCollisionLimit(asteroidNor);
	AsteroidCollisionLimit(asteroidSmall);

	objCollisionLimit(playerShip.position, screenWidth, screenHeight);

	bulletCollisonLimit();
}

#pragma warning(disable: 4459)
void AsteroidCollisionLimit(Asteroid asteroid[])
{
#pragma warning(default:4459)
	for (int i = 0; i < maxAteroids; i++)
	{
		if (asteroid[i].isActive)
		{
			objCollisionLimit(asteroid[i].position, screenWidth, screenHeight);
		}
	}
}

void Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	drawGame();
	EndDrawing();
}

void drawGame()
{
	DrawTexture(background, 0, 0, WHITE);

	for (int i = 0; i < maxBullets; i++)
	{
		DrawBullet(bullet[i]);
	}

	DrawShip(playerShip, playerShip.shipOriginRec, playerShip.widht, playerShip.height);

	for (int i = 0; i < maxAteroids; i++)
	{
		if (asteroid[i].isActive)
		{
			DrawAsteroidBig(asteroid[i]);
		}
	}

	for (int i = 0; i < maxNorAsteroids; i++)
	{
		if (asteroidNor[i].isActive)
		{
			DrawAsteroidNormal(asteroidNor[i]);
		}
	}

	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		if (asteroidSmall[i].isActive)
		{
			DrawAsteroidSmall(asteroidSmall[i]);
		}
	}
	
	DrawTextEx(gameFont, "Score: ", {10, 10}, 40, 0, ORANGE);
	DrawText(TextFormat("%2i", playerShip.points), 200, 10, 40, ORANGE);

	if (playerShip.lifes >= 3)
	{
		DrawTexture(fullHealthBar, static_cast<int>(healthBarPos.x), static_cast<int>(healthBarPos.y), WHITE);
	}

	if (playerShip.lifes == 2)
	{
		DrawTexture(midHealthBar, static_cast<int>(healthBarPos.x), static_cast<int>(healthBarPos.y), WHITE);
	}

	if (playerShip.lifes == 1)
	{
		DrawTexture(lowHealthBar, static_cast<int>(healthBarPos.x), static_cast<int>(healthBarPos.y), WHITE);
	}

	DrawMouse(mouse, mouse.mouseRec);
}

void mouseMovement()
{
	mouse.position = GetMousePosition();
}

void shipMovement()
{
	Vector2 shipActualPos;

	playerShip.source = { 0,0, static_cast<float>(playerShip.texture.width), static_cast<float>(playerShip.texture.height) };
	playerShip.dest = { playerShip.position.x, playerShip.position.y, playerShip.widht, playerShip.height };

	shipActualPos.x = playerShip.position.x;
	shipActualPos.y = playerShip.position.y;

	playerShip.direction.x = mouse.position.x - shipActualPos.x;
	playerShip.direction.y = mouse.position.y - shipActualPos.y;

	float angle = atan(playerShip.direction.y / playerShip.direction.x);
	angle = angle * 180 / PI;

	if (playerShip.direction.x < 0)
	{
		angle += 180;
	}

	playerShip.rotation = angle;

	playerShip.position.x = playerShip.position.x + playerShip.aceleration.x * GetFrameTime();
	playerShip.position.y = playerShip.position.y + playerShip.aceleration.y * GetFrameTime();
}

#pragma warning(disable: 4459)
void asteroidMovement(Asteroid asteroid[], int const maxAteroids)
{
#pragma warning(default:4459)

	for (int i = 0; i < maxAteroids; i++)
	{
		if (asteroid[i].isActive)
		{
			if (asteroid[i].speed.x != 0 && asteroid[i].speed.y != 0)
			{
				asteroid[i].position.x += asteroid[i].speed.x * GetFrameTime();
				asteroid[i].position.y += asteroid[i].speed.y * GetFrameTime();
			}

			else
			{
				asteroid[i].speed.x = static_cast<float>(GetRandomValue(-70, 70));
				asteroid[i].speed.y = static_cast<float>(GetRandomValue(-70, 70));

				asteroid[i].position.x += asteroid[i].speed.x * GetFrameTime();
				asteroid[i].position.y += asteroid[i].speed.y * GetFrameTime();
			}
		}
	}
}

void bulletMovement()
{
	for (int i = 0; i < maxBullets; i++)
	{
		if (bullet[i].isMoving == false)
		{
			bullet[i].position.x = playerShip.position.x - playerShip.widht / 2;
			bullet[i].position.y = playerShip.position.y - playerShip.height / 2;
		}

		if (bullet[i].isMoving)
		{
			bullet[i].position.x += bullet[i].direction.x * bullet[i].speed * GetFrameTime();
			bullet[i].position.y += bullet[i].direction.y * bullet[i].speed * GetFrameTime();
		}
	}
}
#pragma warning(disable: 4459)
void objCollisionLimit(Vector2& objPosition, int screenWidth, int screenHeight)
{
#pragma warning(default: 4459)


	if (objPosition.x < 0)
	{
		objPosition.x = objPosition.x + screenWidth;
	}

	if (objPosition.x >= screenWidth)
	{
		objPosition.x = objPosition.x - screenWidth;
	}

	if (objPosition.y < 0)
	{
		objPosition.y = objPosition.y + screenHeight;
	}

	if (objPosition.y >= screenHeight)
	{
		objPosition.y = objPosition.y - screenHeight;
	}
}

void bulletCollisonLimit()
{
	for (int i = 0; i < maxBullets; i++)
	{
		if (bullet[i].isMoving)
		{
			if (bullet[i].position.x < 0)
			{
				bullet[i].isMoving = false;
				bullet[i].isActive = false;
			}

			if (bullet[i].position.x >= screenWidth)
			{
				bullet[i].isMoving = false;
				bullet[i].isActive = false;
			}

			if (bullet[i].position.y < 0)
			{
				bullet[i].isMoving = false;
				bullet[i].isActive = false;
			}

			if (bullet[i].position.y >= screenHeight)
			{
				bullet[i].isMoving = false;
				bullet[i].isActive = false;
			}
		}
	}
}

bool CheckCollsisionCirCir(Vector2 Obj1Pos, float obj1Radius, Vector2 obj2Pos, float obj2Radius)
{
	float distX = Obj1Pos.x - obj2Pos.x;
	float distY = Obj1Pos.y - obj2Pos.y;

	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= obj1Radius + obj2Radius)
	{
		return true;
	}

	return false;
}

#pragma warning(disable: 4459)
void AsteroidCollision(Ship& playerShip, Asteroid asteroid[])
{
#pragma warning(default: 4459)

	for (int i = 0; i < maxAteroids; i++)
	{
		if (asteroid[i].isActive)
		{
			if (timer < 0)
			{
				if (CheckCollsisionCirCir(playerShip.position, playerShip.radius, asteroid[i].position, asteroid[i].radius))
				{
					//cout << "colision" << endl;
					playerShip.isCollision = true;

					loseLife(playerShip);
					IsAlive(playerShip);
					//cout << "Vidas: " << playerShip.lifes << endl;
					timer = 15.0f;
					
					playerShip.isCollision = false;
				}
			}

			if (timer > 0)
			{
				timer -= GetFrameTime();
				//cout << timer << endl;
			}
		}
	}
}

void BulletCollision()
{

	for (int i = 0; i < maxBullets; i++)
	{
		for (int j = 0; j < maxAteroids; j++)
		{
			if (bullet[i].isActive == true)
			{
				if (asteroid[j].isActive == true)
				{
					if (CheckCollsisionCirCir(bullet[i].position, bullet[i].radius, asteroid[j].position, asteroid[j].radius))
					{
						for (int k = 0; k < 2; k++)
						{
							bullet[i].isMoving = false;
							asteroid[j].isActive = false;
							asteroidNor[asteroidsNorCount].isActive = true;

							asteroidNor[asteroidsNorCount].position.x = asteroid[j].position.x;
							asteroidNor[asteroidsNorCount].position.y = asteroid[j].position.y;
							asteroidsNorCount++;

							bullet[i].isActive = false;
						}

						asteroidsCount--;
						totalAsteoroidsCount--;
						AddPoint(playerShip);
						cout << "colision bala" << endl;
					}
				}
			}
		}
	}

	for (int i = 0; i < maxBullets; i++)
	{
		for (int j = 0; j < maxNorAsteroids; j++)
		{
			if (bullet[i].isActive == true)
			{
				if (asteroidNor[j].isActive == true)
				{
					if (CheckCollsisionCirCir(bullet[i].position, bullet[i].radius, asteroidNor[j].position, asteroidNor[j].radius))
					{
						for (int k = 0; k < 3; k++)
						{
							bullet[i].isMoving = false;
							asteroidNor[j].isActive = false;
							asteroidSmall[asteroidsSmallCount].isActive = true;

							asteroidSmall[asteroidsSmallCount].position.x = asteroidNor[j].position.x;
							asteroidSmall[asteroidsSmallCount].position.y = asteroidNor[j].position.y;
							asteroidsSmallCount++;

							bullet[i].isActive = false;
						}

						asteroidsNorCount--;
						totalAsteoroidsCount--;
						AddPoint(playerShip);
						cout << "colision bala" << endl;
					}
				}
			}
		}
	}

	for (int i = 0; i < maxBullets; i++)
	{
		for (int j = 0; j < maxSmallAsteroids; j++)
		{
			if (bullet[i].isActive == true)
			{
				if (asteroidSmall[j].isActive == true)
				{
					if (CheckCollsisionCirCir(bullet[i].position, bullet[i].radius, asteroidSmall[j].position, asteroidSmall[j].radius))
					{

						bullet[i].isMoving = false;
						asteroidSmall[j].isActive = false;
						bullet[i].isActive = false;

						asteroidsSmallCount--;
						totalAsteoroidsCount--;
						AddPoint(playerShip);
						cout << "colision bala" << endl;
					}
				}
			}
		}
	}

	if (totalAsteoroidsCount <= 0)
	{
		RespawnAsteroids();
	}
}

void RespawnAsteroids()
{
	totalAsteoroidsCount = 20;

	for (int i = 0; i < 5; i++)
	{
		asteroid[i].size = Size::Big;
		asteroid[i] = CreateAsteroid(asteroid[i].size);
	}

	asteroidsCount = asteroidsCount + 5;
	asteroidsNorCount = 0;
	asteroidsSmallCount = 0;


}

void UnloadData()
{
	UnloadTexture(playerShip.texture);

	for (int i = 0; i < maxAteroids; i++)
	{
		UnloadTexture(asteroid[i].texture);
	}

	for (int i = 0; i < maxNorAsteroids; i++)
	{
		UnloadTexture(asteroidNor[i].texture);
	}

	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		UnloadTexture(asteroidSmall[i].texture);
	}


	for (int i = 0; i < maxBullets; i++)
	{
		UnloadTexture(bullet[i].texture);
	}

	UnloadTexture(mouse.texture);
	UnloadTexture(background);

	UnloadTexture(fullHealthBar);
	UnloadTexture(midHealthBar);
	UnloadTexture(lowHealthBar);
}


/*Color tilt;
tilt.a = 0;
tilt.b = 0;
tilt.g = 0;
tilt.r = 0;

float color = 0.0f;

color += GetFrameTime() * 25.0f;

tilt.r = (unsigned char)color;

cout << color << " " << (int)tilt.r << endl;
*/