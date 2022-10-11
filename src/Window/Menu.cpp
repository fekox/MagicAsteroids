#include "Window/Menu.h"

MenuButton play;
MenuButton controlls;
MenuButton rules;
MenuButton credits;
MenuButton quit;
MenuButton returnMenu;

void InitMenu()
{
	//Play Button

	play.pos.x = static_cast<float>(GetScreenWidth() / 20);
	play.pos.y = static_cast<float>(GetScreenHeight() / 3.2);
	play.width = static_cast<float>(GetScreenWidth() / 7);
	play.height = static_cast<float>(GetScreenHeight() / 10);
	play.size = 40;

	play.color = ORANGE;

	//Controlls Button

	controlls.pos.x = static_cast<float>(GetScreenWidth() / 20);
	controlls.pos.y = static_cast<float>(GetScreenHeight() / 2.35);
	controlls.width = static_cast<float>(GetScreenWidth() / 3.1);
	controlls.height = static_cast<float>(GetScreenHeight() / 10);
	controlls.size = 40;

	controlls.color = ORANGE;

	//Rules Button

	rules.pos.x = static_cast<float>(GetScreenWidth() / 20);
	rules.pos.y = static_cast<float>(GetScreenHeight() / 1.84);
	rules.width = static_cast<float>(GetScreenWidth() / 5.6);
	rules.height = static_cast<float>(GetScreenHeight() / 10);
	rules.size = 40;

	rules.color = ORANGE;

	//Credits Button

	credits.pos.x = static_cast<float>(GetScreenWidth() / 1.5);
	credits.pos.y = static_cast<float>(GetScreenHeight() / 1.1);
	credits.width = static_cast<float>(GetScreenWidth() / 4.2);
	credits.height = static_cast<float>(GetScreenHeight() / 10);
	credits.size = 40;

	credits.color = ORANGE;

	//Quit Button

	quit.pos.x = static_cast<float>(GetScreenWidth() / 20);
	quit.pos.y = static_cast<float>(GetScreenHeight() / 1.53);
	quit.width = static_cast<float>(GetScreenWidth() / 7.8);
	quit.height = static_cast<float>(GetScreenHeight() / 10);
	quit.size = 40;

	quit.color = ORANGE;

	//ReturnMenu Button

	returnMenu.pos.x = static_cast<float>(GetScreenWidth() / 2.5);
	returnMenu.pos.y = static_cast<float>(GetScreenHeight() / 1.1);
	returnMenu.width = static_cast<float>(GetScreenWidth() / 7.8);
	returnMenu.height = static_cast<float>(GetScreenHeight() / 10);
	returnMenu.size = 40;

	returnMenu.color = ORANGE;
}

void MenuCollisions(Mouse& mouse)
{
	//Play Button
	if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(GetScreenWidth() / 20), static_cast<float>(GetScreenHeight() / 3.5), static_cast<float>(play.width), static_cast<float>(play.height)}))
	{
		play.color = BLACK;
	}

	else
	{
		play.color = ORANGE;
	}

	//Controlls Button
	if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(GetScreenWidth() / 20), static_cast<float>(GetScreenHeight() / 2.5), static_cast<float>(controlls.width), static_cast<float>(controlls.height) }))
	{
		controlls.color = BLACK;
	}

	else
	{
		controlls.color = ORANGE;
	}

	//Rules Button
	if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(GetScreenWidth() / 20), static_cast<float>(GetScreenHeight() / 1.94), static_cast<float>(rules.width), static_cast<float>(rules.height) }))
	{
		rules.color = BLACK;
	}

	else
	{
		rules.color = ORANGE;
	}

	//Credits Button
	if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(GetScreenWidth() / 1.5), static_cast<float>(GetScreenHeight() / 1.13), static_cast<float>(credits.width), static_cast<float>(credits.height) }))
	{
		credits.color = BLACK;
	}

	else
	{
		credits.color = ORANGE;
	}

	//Quit Button
	if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(GetScreenWidth() / 20), static_cast<float>(GetScreenHeight() / 1.59), static_cast<float>(quit.width), static_cast<float>(quit.height) }))
	{
		quit.color = BLACK;
	}

	else
	{
		quit.color = ORANGE;
	}

	//ReturnMenu Button
	if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(GetScreenWidth() / 2.5), static_cast<float>(GetScreenHeight() / 1.1), static_cast<float>(quit.width), static_cast<float>(quit.height) }))
	{
		returnMenu.color = BLACK;
	}

	else
	{
		returnMenu.color = ORANGE;
	}
}

void MenuInputs(Mouse& mouse, int& optionSelect, bool& playGame)
{
	if (!playGame)
	{
		//Play Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(GetScreenWidth() / 20), static_cast<float>(GetScreenHeight() / 3.5), static_cast<float>(play.width), static_cast<float>(play.height) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				optionSelect = 1;
				playGame = true;
				HideCursor();
			}
		}

		//Controlls Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(GetScreenWidth() / 20), static_cast<float>(GetScreenHeight() / 2.5), static_cast<float>(controlls.width), static_cast<float>(controlls.height) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				optionSelect = 2;
			}
		}

		//Rules Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(GetScreenWidth() / 20), static_cast<float>(GetScreenHeight() / 1.94), static_cast<float>(rules.width), static_cast<float>(rules.height) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				optionSelect = 3;
			}
		}

		//Credits Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(GetScreenWidth() / 1.5), static_cast<float>(GetScreenHeight() / 1.13), static_cast<float>(credits.width), static_cast<float>(credits.height) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				optionSelect = 4;
			}
		}

		//Quit Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(GetScreenWidth() / 20), static_cast<float>(GetScreenHeight() / 1.59), static_cast<float>(quit.width), static_cast<float>(quit.height) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				optionSelect = 5;
			}
		}

		//ReturnMenu Button
		if (CheckCollisionPointRec(mouse.position, Rectangle{ static_cast<float>(GetScreenWidth() / 2.5), static_cast<float>(GetScreenHeight() / 1.1), static_cast<float>(quit.width), static_cast<float>(quit.height) }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				optionSelect = 0;
				playGame = false;
			}
		}
	}
}

void DrawMenu(Texture2D menuBackGround, Font gameFont)
{
	ShowCursor();
	DrawTexture(menuBackGround, 0, 0, WHITE);
	DrawTextEx(gameFont, "  Magic\nAsteroids", { static_cast<float>(GetScreenWidth() / 20) , static_cast<float>(GetScreenHeight() / 20) }, 60, 0, GOLD);

	//Play Button

	DrawRectangle(static_cast<int>(GetScreenWidth() / 20), static_cast<int>(GetScreenHeight() / 3.5), static_cast<int>(play.width), static_cast<int>(play.height), BLANK);
	DrawTextEx(gameFont, "PLAY", play.pos, static_cast<float>(play.size), 0, play.color);

	//Controlls Button

	DrawRectangle(static_cast<int>(GetScreenWidth() / 20), static_cast<int>(GetScreenHeight() / 2.5), static_cast<int>(controlls.width), static_cast<int>(controlls.height), BLANK);
	DrawTextEx(gameFont, "CONTROLLS", controlls.pos, static_cast<float>(controlls.size), 0, controlls.color);

	//Rules Button

	DrawRectangle(static_cast<int>(GetScreenWidth() / 20), static_cast<int>(GetScreenHeight() / 1.94), static_cast<int>(rules.width), static_cast<int>(rules.height), BLANK);
	DrawTextEx(gameFont, "RULES", rules.pos, static_cast<float>(rules.size), 0, rules.color);

	//Credits Button

	DrawRectangle(static_cast<int>(GetScreenWidth() / 1.5), static_cast<int>(GetScreenHeight() / 1.13), static_cast<int>(credits.width), static_cast<int>(credits.height), BLANK);
	DrawTextEx(gameFont, "CREDITS", credits.pos, static_cast<float>(credits.size), 0, credits.color);

	//Quit Button

	DrawRectangle(static_cast<int>(GetScreenWidth() / 20), static_cast<int>(GetScreenHeight() / 1.59), static_cast<int>(quit.width), static_cast<int>(quit.height), BLANK);
	DrawTextEx(gameFont, "QUIT", quit.pos, static_cast<float>(quit.size), 0, quit.color);

}

void DrawControlls(Texture2D menuBackGroundEmpty, Texture texControlls, Font gameFont)
{
	DrawTexture(menuBackGroundEmpty, 0, 0, WHITE);
	DrawTexture(texControlls, 0, 0, WHITE);

	DrawTextEx(gameFont, "Controlls", { static_cast<float>(GetScreenWidth() / 3.5) , static_cast<float>(GetScreenHeight() / 15) }, 60, 0, ORANGE);

	//ReturnMenu Button

	DrawRectangle(static_cast<int>(GetScreenWidth() / 2.5), static_cast<int>(GetScreenHeight() / 1.1), static_cast<int>(returnMenu.width), static_cast<int>(returnMenu.height), BLANK);
	DrawTextEx(gameFont, "MENU", returnMenu.pos, static_cast<float>(returnMenu.size), 0, returnMenu.color);
}

void DrawRules(Texture2D menuBackGroundEmpty, Font gameFont)
{
	DrawTexture(menuBackGroundEmpty, 0, 0, WHITE);

	DrawTextEx(gameFont, "RULES", { static_cast<float>(GetScreenWidth() / 2.7) , static_cast<float>(GetScreenHeight() / 15) }, 60, 0, ORANGE);

	DrawTextEx(gameFont, "Play as a space pilot who must survive a\nasteroid rain, if they hit you three times\nyou lose, if you reach three thousand\npoints you win.\nShoot the asteroids to prevent them from\ncolliding whit the ship but be careful,\nwhen you shoot an asteroid it breaks\ninto two or three parts.\n\nGood luck pilot.", 
	{ static_cast<float>(GetScreenWidth() / 25) , static_cast<float>(GetScreenHeight() / 5) }, 30, 0, ORANGE);

	//ReturnMenu Button

	DrawRectangle(static_cast<int>(GetScreenWidth() / 2.5), static_cast<int>(GetScreenHeight() / 1.1), static_cast<int>(returnMenu.width), static_cast<int>(returnMenu.height), BLANK);
	DrawTextEx(gameFont, "MENU", returnMenu.pos, static_cast<float>(returnMenu.size), 0, returnMenu.color);
}

void DrawCredits(Texture2D menuBackGroundEmpty, Font gameFont)
{
	DrawTexture(menuBackGroundEmpty, 0, 0, WHITE);

	DrawTextEx(gameFont, "CREDITS", { static_cast<float>(GetScreenWidth() / 3) , static_cast<float>(GetScreenHeight() / 15) }, 60, 0, ORANGE);
	
	DrawTextEx(gameFont, "GAME MADE BY\nFacundo Santos", { static_cast<float>(GetScreenWidth() / 3.5) , static_cast<float>(GetScreenHeight() / 3.5) }, 40, 0, ORANGE);

	DrawTextEx(gameFont, "FONT", { static_cast<float>(GetScreenWidth() / 2.3) , static_cast<float>(GetScreenHeight() / 1.8) }, 40, 0, ORANGE);
	DrawTextEx(gameFont, "https://www.dafont.com/es/04b-30.font", { static_cast<float>(GetScreenWidth() / 15) , static_cast<float>(GetScreenHeight() / 1.5) }, 30, 0, ORANGE);

	//ReturnMenu Button

	DrawRectangle(static_cast<int>(GetScreenWidth() / 2.5), static_cast<int>(GetScreenHeight() / 1.1), static_cast<int>(returnMenu.width), static_cast<int>(returnMenu.height), BLANK);
	DrawTextEx(gameFont, "MENU", returnMenu.pos, static_cast<float>(returnMenu.size), 0, returnMenu.color);
}