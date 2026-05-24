#include "raylib.h"

int main()
{
    InitWindow(800, 600, "TicTacToe");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("My First C Game!", 220, 250, 40, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}