#include "raylib.h"

int main(void)
{
    // Init
    //----------------------------------------------------------------------------------

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight, "Asteroids_FacundoSantos");

    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Congrats! You created your first window!", GetScreenWidth() /2.5, GetScreenHeight() /2, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();       
}


