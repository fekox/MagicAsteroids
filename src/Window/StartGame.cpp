#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Window/Menu.h"
#include "Window/Game.h"
#include "Window/StartGame.h"
#include "Objects/PlayerShip.h"
#include "Objects/Asteroid.h"
#include "Objects/Mouse.h"
#include "Objects/Bullet.h"

using namespace std;

//Menu
Texture2D menuBackGround;
int optionSelect = 0;

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
//int screenWidth = 1920;
//int screenHeight = 1080;

//Restart Menu
SubMenu restartMenu;
Button restartButton;
Button returnMenuButton;
Button quitGameButton;

//Pause Menu
bool pause = false;
SubMenu pauseMenu;
Button pauseButtonOff;
Button pauseButtonOn;
Button resumeButton;

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
	
	//***************************************************************************

	//Menu
	InitMenu();
	menuBackGround = LoadTexture("resources/Sprites/MenuBackground.png");

	//***************************************************************************

	//Restart menu
	restartMenu.width = 600;
	restartMenu.height = 500;
	restartMenu.pos.x = static_cast<float>(screenWidth / 4.5);
	restartMenu.pos.y = static_cast<float>(screenHeight / 4.5);
	restartMenu.isActive = false;
	restartMenu.texture = LoadTexture("resources/Sprites/RestartGameMenu.png");

	//Restart Button
	restartButton.width = static_cast<float>(screenWidth / 2.5);
	restartButton.height = static_cast<float>(screenHeight / 2.1);
	restartButton.size = 40;
	restartButton.color = ORANGE;

	//Menu Button
	returnMenuButton.width = static_cast<float>(screenWidth / 2.2);
	returnMenuButton.height = static_cast<float>(screenHeight / 1.65);
	returnMenuButton.size = 40;
	returnMenuButton.color = ORANGE;

	//Quit Button
	quitGameButton.width = static_cast<float>(screenWidth / 2.15);
	quitGameButton.height = static_cast<float>(screenHeight / 1.37);
	quitGameButton.size = 40;
	quitGameButton.color = ORANGE;

	//***************************************************************************

	//Pause Menu
	pauseMenu.width = 600;
	pauseMenu.height = 500;
	pauseMenu.pos.x = static_cast<float>(screenWidth / 4.5);
	pauseMenu.pos.y = static_cast<float>(screenHeight / 4.5);
	pauseMenu.isActive = false;
	pauseMenu.texture = LoadTexture("resources/Sprites/RestartGameMenu.png");

	//Pause Button Off
	pauseButtonOff.pos.x = static_cast<float>(screenWidth / 1.2);
	pauseButtonOff.pos.y = static_cast<float>(screenHeight / 20);
	pauseButtonOff.width = 64;
	pauseButtonOff.height = 64;
	pauseButtonOff.color = WHITE;
	pauseButtonOff.texture = LoadTexture("resources/Sprites/PauseButtonOff.png");

	//Pause Button On
	pauseButtonOn.pos.x = static_cast<float>(screenWidth / 1.2);
	pauseButtonOn.pos.y = static_cast<float>(screenHeight / 20);
	pauseButtonOn.width = 64;
	pauseButtonOn.height = 64;
	pauseButtonOn.color = WHITE;
	pauseButtonOn.texture = LoadTexture("resources/Sprites/PauseButtonOn.png");

	//Resume Button
	resumeButton.width = static_cast<float>(screenWidth / 2.4);
	resumeButton.height = static_cast<float>(screenHeight / 2.1);
	resumeButton.size = 40;
	resumeButton.color = ORANGE;
	
	//***************************************************************************

	//Player
	playerShip = CreateShip();
	playerShip.shipRec = GetRec(playerShip, playerShip.widht, playerShip.height);
	playerShip.shipOriginRec.x = playerShip.shipRec.width / 2;
	playerShip.shipOriginRec.y = playerShip.shipRec.height / 2;

	playerShip.isActive = true;

	//***************************************************************************

	//HealthBar
	healthBarPos.x = static_cast<float>(screenWidth /2.2);
	healthBarPos.y = 1;

	//***************************************************************************

	//Mouse
	HideCursor();
	mouse = CreateMouse();
	mouse.mouseRec = GetRecMouse(mouse);

	//***************************************************************************

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

	//***************************************************************************

	//Bullet
	for (int i = 0; i < maxBullets; i++)
	{
		bullet[i] = CreateBullet();
	}
}

void GameLoop()
{
	SetExitKey(NULL);
	bool gameOn = true;
	bool playGame = false;

	while (!WindowShouldClose() && gameOn)
	{	
		if (gameOn == true)
		{
			mouseMovement();
			MenuCollisions(mouse);
			MenuInputs(mouse, optionSelect, playGame);

			if (playGame == true)
			{
				Input(gameOn);

				if (!pause)
				{
					Update();
					Collision();
				}

				PauseMenuCollisions();
			}

			switch (optionSelect)
			{
				case static_cast<int>(Menu::MainMenu):
					BeginDrawing();
					ClearBackground(BLACK);

					ShowCursor();
					DrawMenu(menuBackGround, gameFont);

					EndDrawing();

				break;

				case static_cast<int>(Menu::Play):
					Draw();
				break;

				default:
				break;
			}
		}
	}

	if (gameOn == false)
	{
		UnloadData();
		CloseWindow();
	}
}

void Input(bool& gameOn)
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

	if (restartMenu.isActive)
	{
		//Restart Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 2.2), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 10) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				RestartGame();
			}
		}

		//Return Menu Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 1.7), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 12) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				RestartGame();
				restartMenu.isActive = false;
				optionSelect = 0;
			}
		}

		//Quit Game Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 1.4), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 12) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				gameOn = false;
			}
		}
	}

	if (pauseMenu.isActive)
	{
		//Resume Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 2.2), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 10) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				pause = false;
				pauseMenu.isActive = false;
			}
		}

		//Return Menu Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 1.7), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 12) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				RestartGame();
				pause = false;
				pauseMenu.isActive = false;
				optionSelect = 0;
			}
		}

		//Quit Game Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 1.4), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 12) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				gameOn = false;
			}
		}
	}

	if (!restartMenu.isActive && !pauseMenu.isActive)
	{
		if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_P))
		{
			pauseMenu.isActive = true;
			pause = true;
		}

		if (CheckCollisionPointRec(mouse.position, Rectangle{ pauseButtonOff.pos.x, pauseButtonOff.pos.y, pauseButtonOff.width, pauseButtonOff.height}))
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				pauseMenu.isActive = true;
				pause = true;
			}
		}
	}

	else
	{
		if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_P))
		{
			pauseMenu.isActive = false;
			pause = false;
			HideCursor();
		}

		if (CheckCollisionPointRec(mouse.position, Rectangle{ pauseButtonOn.pos.x, pauseButtonOn.pos.y, pauseButtonOn.width, pauseButtonOn.height }))
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				pauseMenu.isActive = false;
				pause = false;
				HideCursor();
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

	RestarGameMenuCollisions();
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

	if (timer > 0)
	{
		playerShip.color.a -= static_cast <unsigned char>(GetFrameTime() * 1000.0f);
	}

	if (timer < 0)
	{
		playerShip.color.a = 255;
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

	if (!pauseMenu.isActive)
	{
		DrawRectangle(static_cast<int>(pauseButtonOff.pos.x), static_cast<int>(pauseButtonOff.pos.y), static_cast<int>(pauseButtonOff.width), static_cast<int>(pauseButtonOff.height), BLANK);
		DrawTexture(pauseButtonOff.texture, static_cast<int>(pauseButtonOff.pos.x), static_cast<int>(pauseButtonOff.pos.y), pauseButtonOff.color);
	}

	if (pauseMenu.isActive)
	{
		DrawRectangle(static_cast<int>(pauseButtonOff.pos.x), static_cast<int>(pauseButtonOff.pos.y), static_cast<int>(pauseButtonOff.width), static_cast<int>(pauseButtonOff.height), BLANK);
		DrawTexture(pauseButtonOn.texture, static_cast<int>(pauseButtonOn.pos.x), static_cast<int>(pauseButtonOn.pos.y), pauseButtonOn.color);

		DrawPauseMenu();
	}

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

	if (!IsAlive(playerShip) || playerWin(playerShip))
	{
		DrawRestarGameMenu();
	}

	if (!restartMenu.isActive && !pauseMenu.isActive)
	{
		DrawMouse(mouse, mouse.mouseRec);
	}
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
					timer = 45.0f;
					
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
						//cout << "colision bala" << endl;
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
						//cout << "colision bala" << endl;
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
						//cout << "colision bala" << endl;
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

	int asteroidsSpawn = 5;

	for (int i = 0; i < maxAteroids; i++)
	{
		if (!asteroid[i].isActive)
		{
			asteroid[i].size = Size::Big;
			asteroid[i] = CreateAsteroid(asteroid[i].size);
			asteroidsSpawn--;

			if (asteroidsSpawn <= 0)
			{
				break;
			}
		}
	}

	asteroidsCount = asteroidsCount + 5;
	asteroidsNorCount = 0;
	asteroidsSmallCount = 0;
}

void DrawPauseMenu()
{
	DrawRectangle(static_cast<int>(restartMenu.pos.x), static_cast<int>(restartMenu.pos.y), static_cast<int>(restartMenu.width), static_cast<int>(restartMenu.height), BLANK);
	DrawTexture(restartMenu.texture, static_cast<int>(restartMenu.pos.x), static_cast<int>(restartMenu.pos.y), WHITE);

	DrawTextEx(gameFont, "Pause", { static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 3.1) }, 70, 0, ORANGE);

	//Restart Button
	DrawRectangle(static_cast<int>(screenWidth / 2.5), static_cast<int>(screenHeight / 2.2), static_cast<int>(screenWidth / 4), static_cast<int>(screenHeight / 10), BLANK);
	DrawTextEx(gameFont, "RESUME", { static_cast<float>(resumeButton.width), static_cast<float>(resumeButton.height) }, static_cast<float>(resumeButton.size), 0, resumeButton.color);

	//Return Menu Button
	DrawRectangle(static_cast<int>(screenWidth / 2.5), static_cast<int>(screenHeight / 1.7), static_cast<int>(screenWidth / 4), static_cast<int>(screenHeight / 12), BLANK);
	DrawTextEx(gameFont, "MENU", { static_cast<float>(returnMenuButton.width), static_cast<float>(returnMenuButton.height) }, static_cast<float>(returnMenuButton.size), 0, returnMenuButton.color);

	//Quit Game Button
	DrawRectangle(static_cast<int>(screenWidth / 2.5), static_cast<int>(screenHeight / 1.4), static_cast<int>(screenWidth / 4), static_cast<int>(screenHeight / 12), BLANK);
	DrawTextEx(gameFont, "QUIT", { static_cast<float>(quitGameButton.width), static_cast<float>(quitGameButton.height) }, static_cast<float>(quitGameButton.size), 0, quitGameButton.color);

}

void PauseMenuCollisions()
{
	if (pauseMenu.isActive)
	{
		ShowCursor();

		//Restart Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 2.2), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 10) }))
		{
			resumeButton.color = BLACK;
		}

		else
		{
			resumeButton.color = ORANGE;
		}

		//Return Menu Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 1.7), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 12) }))
		{
			returnMenuButton.color = BLACK;
		}

		else
		{
			returnMenuButton.color = ORANGE;
		}

		//Quit Game Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 1.4), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 12) }))
		{
			quitGameButton.color = BLACK;
		}

		else
		{
			quitGameButton.color = ORANGE;
		}
	}
}

void DrawRestarGameMenu()
{
	for (int i = 0; i < maxAteroids; i++)
	{
		asteroid[i].isActive = false;
	}

	for (int i = 0; i < maxNorAsteroids; i++)
	{
		asteroidNor[i].isActive = false;
	}

	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		asteroidSmall[i].isActive = false;
	}

	for (int i = 0; i < maxBullets; i++)
	{
		bullet[i].isActive = false;
	}

	playerShip.isActive = false;

	DrawRectangle(static_cast<int>(restartMenu.pos.x), static_cast<int>(restartMenu.pos.y), static_cast<int>(restartMenu.width), static_cast<int>(restartMenu.height), BLANK);
	restartMenu.isActive = true;

	DrawTexture(restartMenu.texture, static_cast<int>(restartMenu.pos.x), static_cast<int>(restartMenu.pos.y), WHITE);

	if (!IsAlive(playerShip))
	{
		DrawTextEx(gameFont, "You Lose", { static_cast<float>(screenWidth / 3.5), static_cast<float>(screenHeight / 3.1) }, 70, 0, ORANGE);
	}

	if (playerWin(playerShip))
	{
		DrawTextEx(gameFont, "You Win", { static_cast<float>(screenWidth / 3.1), static_cast<float>(screenHeight / 3.1) }, 70, 0, ORANGE);
	}

	//Restart Button
	DrawRectangle(static_cast<int>(screenWidth /2.5), static_cast<int>(screenHeight /2.2), static_cast<int>(screenWidth /4), static_cast<int>(screenHeight /10), BLANK);
	DrawTextEx(gameFont, "RESTART", { static_cast<float>(restartButton.width), static_cast<float>(restartButton.height) }, static_cast<float>(restartButton.size), 0, restartButton.color);


	//Return Menu Button
	DrawRectangle(static_cast<int>(screenWidth / 2.5), static_cast<int>(screenHeight / 1.7), static_cast<int>(screenWidth / 4), static_cast<int>(screenHeight / 12), BLANK);
	DrawTextEx(gameFont, "MENU", { static_cast<float>(returnMenuButton.width), static_cast<float>(returnMenuButton.height) }, static_cast<float>(returnMenuButton.size), 0, returnMenuButton.color);

	//Quit Game Button
	DrawRectangle(static_cast<int>(screenWidth / 2.5), static_cast<int>(screenHeight / 1.4), static_cast<int>(screenWidth / 4), static_cast<int>(screenHeight / 12), BLANK);
	DrawTextEx(gameFont, "QUIT", { static_cast<float>(quitGameButton.width), static_cast<float>(quitGameButton.height) }, static_cast<float>(quitGameButton.size), 0, quitGameButton.color);
}

void RestartGame()
{
	gameFont = LoadFont("resources/Font/04B_30__.TTF");

	background = LoadTexture("resources/Sprites/Background.png");

	fullHealthBar = LoadTexture("resources/Sprites/FullHealthBar.png");
	midHealthBar = LoadTexture("resources/Sprites/MidHealthBar.png");
	lowHealthBar = LoadTexture("resources/Sprites/LowHealthBar.png");

	restartMenu.width = 600;
	restartMenu.height = 500;
	restartMenu.pos.x = static_cast<float>(screenWidth / 4.5);
	restartMenu.pos.y = static_cast<float>(screenHeight / 4.5);
	restartMenu.isActive = false;

	//Player
	playerShip = CreateShip();
	playerShip.shipRec = GetRec(playerShip, playerShip.widht, playerShip.height);
	playerShip.shipOriginRec.x = playerShip.shipRec.width / 2;
	playerShip.shipOriginRec.y = playerShip.shipRec.height / 2;
	playerShip.isActive = true;

	//HealthBar
	healthBarPos.x = static_cast<float>(screenWidth / 2.2);
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

void RestarGameMenuCollisions()
{
	if (restartMenu.isActive)
	{
		ShowCursor();

		//Restart Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 2.2), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 10) }))
		{
			restartButton.color = BLACK;
		}

		else
		{
			restartButton.color = ORANGE;
		}

		//Return Menu Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 1.7), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 12) }))
		{
			returnMenuButton.color = BLACK;
		}

		else
		{
			returnMenuButton.color = ORANGE;
		}

		//Quit Game Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 1.4), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 12) }))
		{
			quitGameButton.color = BLACK;
		}

		else
		{
			quitGameButton.color = ORANGE;
		}
	}
}

void UnloadData()
{
	UnloadTexture(menuBackGround);

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
	UnloadTexture(restartMenu.texture);
	UnloadTexture(pauseButtonOff.texture);
	UnloadTexture(pauseButtonOn.texture);
}