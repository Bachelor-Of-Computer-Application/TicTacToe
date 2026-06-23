#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include "game.h"

// STATE 
int screen = 0;
int loginError = 0;
int showStats = 0;

//  INPUT
char username[50] = "";
char password[50] = "";

int usernameLen = 0;
int passwordLen = 0;

int typingUsername = 0;
int typingPassword = 0;

//  LOGIN
int CheckLogin(char *u, char *p)
{
    FILE *f = fopen("users.txt", "r");
    if (!f) return 0;

    char fu[50], fp[50];

    while (fscanf(f, "%49s %49s", fu, fp) != EOF)
    {
        if (strcmp(u, fu) == 0 && strcmp(p, fp) == 0)
        {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

//  SIGNUP
void SaveUser(char *u, char *p)
{
    FILE *f = fopen("users.txt", "a");
    if (f)
    {
        fprintf(f, "%s %s\n", u, p);
        fclose(f);
    }
}

//  MAIN 
int main()
{
    InitWindow(800, 600, "TicTacToe");
    SetTargetFPS(60);

    FILE *fcheck = fopen("users.txt", "r");
    if (!fcheck)
        screen = 1;
    else
    {
        screen = 2;
        fclose(fcheck);
    }

    InitGame();

    while (!WindowShouldClose())
    {
        Vector2 m = GetMousePosition();

        //  TEXT INPUT 
        int key = GetCharPressed();
        while (key > 0)
        {
            if (key != ' ')
            {
                if (typingUsername && usernameLen < 49)
                {
                    username[usernameLen++] = (char)key;
                    username[usernameLen] = '\0';
                }

                if (typingPassword && passwordLen < 49)
                {
                    password[passwordLen++] = (char)key;
                    password[passwordLen] = '\0';
                }
            }

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            if (typingUsername && usernameLen > 0)
                username[--usernameLen] = '\0';

            if (typingPassword && passwordLen > 0)
                password[--passwordLen] = '\0';
        }

        // MOUSE 
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            typingUsername = 0;
            typingPassword = 0;

            // GAME SCREEN 
            if (screen == 3)
            {
                // STATS BUTTON CLICK
                if (m.x >= 10 && m.x <= 130 &&
                    m.y >= 10 && m.y <= 50)
                {
                    showStats = !showStats;
                }
                else
                {
                    HandleGameClick(m.x, m.y);
                }
            }

            // SIGNUP 
            if (screen == 1)
            {
                loginError = 0;

                if (m.x >= 250 && m.x <= 550 &&
                    m.y >= 200 && m.y <= 240)
                    typingUsername = 1;

                if (m.x >= 250 && m.x <= 550 &&
                    m.y >= 260 && m.y <= 300)
                    typingPassword = 1;

                if (m.x >= 250 && m.x <= 550 &&
                    m.y >= 340 && m.y <= 390)
                {
                    SaveUser(username, password);
                    screen = 2;
                }
            }

            //  LOGIN 
            if (screen == 2)
            {
                loginError = 0;

                if (m.x >= 250 && m.x <= 550 &&
                    m.y >= 200 && m.y <= 240)
                    typingUsername = 1;

                if (m.x >= 250 && m.x <= 550 &&
                    m.y >= 260 && m.y <= 300)
                    typingPassword = 1;

                if (m.x >= 250 && m.x <= 550 &&
                    m.y >= 340 && m.y <= 390)
                {
                    if (CheckLogin(username, password))
                    {
                        screen = 3;
                        loginError = 0;
                    }
                    else
                    {
                        loginError = 1;
                    }
                }
            }
        }

        // DRAW 
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //  SIGNUP 
        if (screen == 1)
        {
            DrawText("SIGN UP", 320, 120, 30, BLACK);

            DrawRectangle(250, 200, 300, 40, LIGHTGRAY);
            DrawText(username, 260, 210, 20, BLACK);

            DrawRectangle(250, 260, 300, 40, LIGHTGRAY);

            char hidden[50];
            for (int i = 0; i < passwordLen; i++) hidden[i] = '*';
            hidden[passwordLen] = '\0';

            DrawText(hidden, 260, 270, 20, BLACK);

            DrawRectangle(250, 340, 300, 50, GREEN);
            DrawText("CREATE ACCOUNT", 270, 355, 20, BLACK);
        }

        // LOGIN 
        else if (screen == 2)
        {
            DrawText("LOGIN", 340, 120, 30, BLACK);

            DrawRectangle(250, 200, 300, 40, LIGHTGRAY);
            DrawText(username, 260, 210, 20, BLACK);

            DrawRectangle(250, 260, 300, 40, LIGHTGRAY);

            char hidden[50];
            for (int i = 0; i < passwordLen; i++) hidden[i] = '*';
            hidden[passwordLen] = '\0';

            DrawText(hidden, 260, 270, 20, BLACK);

            DrawRectangle(250, 340, 300, 50, BLUE);
            DrawText("LOGIN", 360, 355, 20, WHITE);

            if (loginError)
                DrawText("Wrong username/password", 220, 420, 20, RED);
        }

        // GAME 
        else if (screen == 3)
        {
            DrawGame();

            // STATS BUTTON
            DrawRectangle(10, 10, 120, 40, DARKGRAY);
            DrawText("STATS", 35, 20, 20, WHITE);

            //  STATS OVERLAY 
            if (showStats)
            {
                DrawRectangle(150, 80, 500, 420, Fade(BLACK, 0.85f));
                DrawText("MATCH HISTORY", 280, 100, 25, WHITE);

                int xWins = 0, oWins = 0, draws = 0;
                GetMatchStats(&xWins, &oWins, &draws);
                char statsStr[100];
                sprintf(statsStr, "Player X: %d  |  Player O: %d  |  Draws: %d", xWins, oWins, draws);
                DrawText(statsStr, 200, 140, 20, YELLOW);

                FILE *f = fopen("stats.txt", "r");

                if (f == NULL)
                {
                    DrawText("No stats available", 280, 200, 20, WHITE);
                }
                else
                {
                    char line[100];
                    int y = 180;

                    while (fgets(line, sizeof(line), f))
                    {
                        DrawText(line, 200, y, 20, WHITE);
                        y += 30;
                    }

                    fclose(f);
                }

                DrawText("Click STATS again to close", 220, 500, 18, LIGHTGRAY);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}