#pragma once

#include "raylib.h"

#include "Objects/Mouse.h"

struct MenuButton
{
	Vector2 pos;

	float width;
	float height;

	int size;

	bool isActive;

	Texture texture;

	Color color;
};

enum class Menu
{
	MainMenu,
	Play,
	Controlls,
	Rules,
	Credits,
	Quit
};

void InitMenu();
void MenuCollisions(Mouse& mouse, int& optionSelect);
void MenuInputs(Mouse& mouse, int& optionSelect, bool& playGame, Sound selectOption);
void DrawMenu(Texture2D menuBackGround, Font gameFont);
void DrawControlls(Texture2D menuBackGroundEmpty, Texture texControlls, Font gameFont);
void DrawRules(Texture2D menuBackGroundEmpty, Font gameFont);
void DrawCredits(Texture2D menuBackGroundEmpty, Font gameFont);