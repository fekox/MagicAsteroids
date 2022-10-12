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
Texture2D menuBackGroundEmpty;
Texture2D texControlls;
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
bool playGame = false;
Texture2D background;
int screenWidth = 1024;
int screenHeight = 768;

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

//Music
Music music;
Sound asteroidDestroid;
Sound selectOption;
Sound shipCollision;
Sound shoot;

float musicPitch = 0.9f;

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

	//Music
	InitAudioDevice();

	music = LoadMusicStream("resources/Sounds/Interplanetary Odyssey.ogg");
	music.looping = true;

	asteroidDestroid = LoadSound("resources/Sounds/Asteroid Destroid.mp3");

	selectOption = LoadSound("resources/Sounds/Select Option.mp3");

	shipCollision = LoadSound("resources/Sounds/Ship Collision.mp3");

	shoot = LoadSound("resources/Sounds/Shoot.mp3");

	PlayMusicStream(music);
	SetMusicVolume(music, 0.5f);
	
	//***************************************************************************

	//Menu
	InitMenu();
	menuBackGround = LoadTexture("resources/Sprites/MenuBackground.png");
	menuBackGroundEmpty = LoadTexture("resources/Sprites/BackgroundEmpty.png");
	texControlls = LoadTexture("resources/Sprites/Controlls.png");

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
		asteroid[i] = CreateAsteroid(asteroid[i].size, asteroid[i]);
	}

	for (int i = 0; i < maxNorAsteroids; i++)
	{
		asteroidNor[i].size = Size::Normal;
		asteroidNor[i] = CreateAsteroid(asteroidNor[i].size, asteroidNor[i]);
	}

	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		asteroidSmall[i].size = Size::Small;
		asteroidSmall[i] = CreateAsteroid(asteroidSmall[i].size, asteroidSmall[i]);
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

	while (!WindowShouldClose() && gameOn)
	{	
		if (gameOn == true)
		{
			UpdateMusicStream(music);
			SetMusicPitch(music, musicPitch);

			MouseMovement();
			MenuCollisions(mouse, optionSelect);
			MenuInputs(mouse, optionSelect, playGame, selectOption);

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

				case static_cast<int>(Menu::Controlls):
					BeginDrawing();
					ClearBackground(BLACK);
					DrawControlls(menuBackGroundEmpty, texControlls, gameFont);
					EndDrawing();
				break;

				case static_cast<int>(Menu::Rules):
					BeginDrawing();
					ClearBackground(BLACK);
					DrawRules(menuBackGroundEmpty, gameFont);
					EndDrawing();
				break;

				case static_cast<int>(Menu::Credits):
					BeginDrawing();
					ClearBackground(BLACK);
					DrawCredits(menuBackGroundEmpty, gameFont);
					EndDrawing();
				break;

				case static_cast<int>(Menu::Quit):
					gameOn = false;
				break;
			}
		}
	}

	if (gameOn == false)
	{
		UnloadData();
		CloseAudioDevice();
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
					if(!restartMenu.isActive && !pauseMenu.isActive)
					{
						PlaySound(shoot);
					}

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
				PlaySound(selectOption);
				RestartGame();
			}
		}

		//Return Menu Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 1.7), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 12) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				PlaySound(selectOption);
				RestartGame();
				restartMenu.isActive = false;
				playGame = false;
				optionSelect = 0;
			}
		}

		//Quit Game Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 1.4), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 12) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				PlaySound(selectOption);
				gameOn = false;
			}
		}
	}

	if (pauseMenu.isActive)
	{
		PauseMusicStream(music);

		//Resume Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 2.2), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 10) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				PlaySound(selectOption);
				pause = false;
				pauseMenu.isActive = false;
				ResumeMusicStream(music);
			}
		}

		//Return Menu Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 1.7), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 12) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				PlaySound(selectOption);
				RestartGame();
				pause = false;
				playGame = false;
				pauseMenu.isActive = false;
				optionSelect = 0;
				ResumeMusicStream(music);
			}
		}

		//Quit Game Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(screenWidth / 2.5), static_cast<float>(screenHeight / 1.4), static_cast<float>(screenWidth / 4), static_cast<float>(screenHeight / 12) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				PlaySound(selectOption);
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
			ResumeMusicStream(music);
			HideCursor();
		}

		if (CheckCollisionPointRec(mouse.position, Rectangle{ pauseButtonOn.pos.x, pauseButtonOn.pos.y, pauseButtonOn.width, pauseButtonOn.height }))
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				pauseMenu.isActive = false;
				pause = false;
				ResumeMusicStream(music);
				HideCursor();
			}
		}
	}
}

void Update()
{
	ShipMovement();
	AsteroidMovement(asteroid, maxAteroids);
	AsteroidMovement(asteroidNor, maxNorAsteroids);
	AsteroidMovement(asteroidSmall, maxSmallAsteroids);
	BulletMovement();
}

void Collision()
{
	AsteroidCollision(playerShip, asteroid, maxAteroids);
	AsteroidCollision(playerShip, asteroidNor, maxNorAsteroids);
	AsteroidCollision(playerShip, asteroidSmall, maxSmallAsteroids);

	BulletCollision();

	AsteroidCollisionLimit(asteroid);
	AsteroidCollisionLimit(asteroidNor);
	AsteroidCollisionLimit(asteroidSmall);

	ObjCollisionLimit(playerShip.position);

	BulletCollisonLimit();

	RestarGameMenuCollisions();
}

void Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawGame();
	EndDrawing();
}

void DrawGame()
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

	if (!IsAlive(playerShip) || PlayerWin(playerShip))
	{
		DrawRestarGameMenu();
	}

	if (!restartMenu.isActive && !pauseMenu.isActive)
	{
		DrawMouse(mouse, mouse.mouseRec);
	}
}

void MouseMovement()
{
	mouse.position = GetMousePosition();
}

void ShipMovement()
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


void AsteroidMovement(Asteroid asteroids[], int const maxObjects)
{
	for (int i = 0; i < maxObjects; i++)
	{
		if (asteroids[i].isActive)
		{
			if (asteroids[i].speed.x != 0 && asteroids[i].speed.y != 0)
			{
				asteroids[i].position.x += asteroids[i].speed.x * GetFrameTime();
				asteroids[i].position.y += asteroids[i].speed.y * GetFrameTime();
			}

			else
			{
				asteroids[i].speed.x = static_cast<float>(GetRandomValue(-70, 70));
				asteroids[i].speed.y = static_cast<float>(GetRandomValue(-70, 70));

				asteroids[i].position.x += asteroids[i].speed.x * GetFrameTime();
				asteroids[i].position.y += asteroids[i].speed.y * GetFrameTime();
			}
		}
	}
}

void BulletMovement()
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

void ObjCollisionLimit(Vector2& objPosition)
{
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

void AsteroidCollisionLimit(Asteroid asteroids[])
{
	for (int i = 0; i < maxAteroids; i++)
	{
		if (asteroids[i].isActive)
		{
			ObjCollisionLimit(asteroids[i].position);
		}
	}
}

void BulletCollisonLimit()
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


void AsteroidCollision(Ship& player, Asteroid asteroids[], int const maxObjects)
{
	for (int i = 0; i < maxObjects; i++)
	{
		if (asteroids[i].isActive)
		{
			if (timer < 0)
			{
				if (CheckCollsisionCirCir(player.position, player.radius, asteroids[i].position, asteroids[i].radius))
				{
					player.isCollision = true;

					PlaySound(shipCollision);
					LoseLife(player);
					IsAlive(player);
					timer = 45.0f;
					
					player.isCollision = false;
				}
			}

			if (timer > 0)
			{
				timer -= GetFrameTime();
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
						PlaySound(asteroidDestroid);
						asteroidsCount--;
						totalAsteoroidsCount--;
						AddPoint(playerShip);
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

						PlaySound(asteroidDestroid);
						asteroidsNorCount--;
						totalAsteoroidsCount--;
						AddPoint(playerShip);
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

						PlaySound(asteroidDestroid);
						asteroidsSmallCount--;
						totalAsteoroidsCount--;
						AddPoint(playerShip);
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
			asteroid[i] = CreateAsteroid(asteroid[i].size, asteroid[i]);
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

	if (PlayerWin(playerShip))
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
	restartMenu.width = 600;
	restartMenu.height = 500;
	restartMenu.pos.x = static_cast<float>(screenWidth / 4.5);
	restartMenu.pos.y = static_cast<float>(screenHeight / 4.5);
	restartMenu.isActive = false;

	//Player
	playerShip.position.x = static_cast<float>(GetScreenWidth() / 2);
	playerShip.position.y = static_cast<float>(GetScreenHeight() / 2);
	playerShip.direction.x = 0;
	playerShip.direction.y = 0;
	playerShip.aceleration.x = 50.0f;
	playerShip.aceleration.y = 50.0f;
	playerShip.height = 60.0f;
	playerShip.widht = 60.0f;
	playerShip.radius = 25.0f;
	playerShip.rotation = 0;
	playerShip.speed = 100.0f;
	playerShip.lifes = 3;
	playerShip.points = 0;
	playerShip.isCollision = false;
	playerShip.isAlive = true;
	playerShip.isActive = true;
	playerShip.win = false;
	playerShip.color.a = 255;
	playerShip.color.b = 255;
	playerShip.color.g = 255;
	playerShip.color.r = 255;


	//HealthBar
	healthBarPos.x = static_cast<float>(screenWidth / 2.2);
	healthBarPos.y = 1;

	//Mouse
	HideCursor();
	mouse.position.x = 0;
	mouse.position.y = 0;
	mouse.width = 20.0f;
	mouse.height = 20.0f;
	mouse.mouseRec = GetRecMouse(mouse);

	//Asteroid

	for (int i = 0; i < maxAteroids; i++)
	{
		asteroid[i].size = Size::Big;
		asteroid[i].position.x = static_cast<float>(GetRandomValue(700, 1000));
		asteroid[i].position.y = static_cast<float>(GetRandomValue(700, 900));
		asteroid[i].radius = 60.0f;
		asteroid[i].isActive = true;
		asteroid[i].speed.x = static_cast<float>(GetRandomValue(-70, 70));
		asteroid[i].speed.y = static_cast<float>(GetRandomValue(-70, 70));
	}

	for (int i = 0; i < maxNorAsteroids; i++)
	{
		asteroidNor[i].size = Size::Normal;
		asteroidNor[i].position.x = 0;
		asteroidNor[i].position.y = 0;
		asteroidNor[i].radius = 45.0f;
		asteroidNor[i].isActive = false;
		asteroidNor[i].speed.x = static_cast<float>(GetRandomValue(-90, 90));
		asteroidNor[i].speed.y = static_cast<float>(GetRandomValue(-90, 90));
	}

	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		asteroidSmall[i].size = Size::Small;
		asteroidSmall[i].position.x = 0;
		asteroidSmall[i].position.y = 0;
		asteroidSmall[i].radius = 35.0f;
		asteroidSmall[i].isActive = false;
		asteroidSmall[i].speed.x = static_cast<float>(GetRandomValue(-110, 110));
		asteroidSmall[i].speed.y = static_cast<float>(GetRandomValue(-110, 110));
	}

	//Bullet
	for (int i = 0; i < maxBullets; i++)
	{
		bullet[i].position.x = 0;
		bullet[i].position.y = 0;
		bullet[i].direction.x = 0;
		bullet[i].direction.y = 0;
		bullet[i].isMoving = false;
		bullet[i].isActive = false;
		bullet[i].radius = 10.0f;
		bullet[i].speed = 500.0f;
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
	UnloadTexture(menuBackGroundEmpty);

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

	UnloadMusicStream(music);
	UnloadSound(shipCollision);
	UnloadSound(asteroidDestroid);
	UnloadSound(selectOption);
	UnloadSound(shoot);
}