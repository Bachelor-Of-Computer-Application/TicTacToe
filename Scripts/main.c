#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include "game.h"

// ---------------- STATE ----------------
int screen = 0;
int loginError = 0;
int showStats = 0;

// ---------------- INPUT ----------------
char username[50] = "";
char password[50] = "";

int usernameLen = 0;
int passwordLen = 0;

int typingUsername = 0;
int typingPassword = 0;

// ---------------- LOGIN ----------------
int CheckLogin(char *u, char *p)
{
    FILE *f = fopen("users.txt", "r");
    if (!f) return 0;

    char fu[50], fp[50];

    while (fscanf(f, "%s %s", fu, fp) != EOF)
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

// ---------------- SIGNUP ----------------
void SaveUser(char *u, char *p)
{
    FILE *f = fopen("users.txt", "a");
    if (f)
    {
        fprintf(f, "%s %s\n", u, p);
        fclose(f);
    }
}
/ ---------------- MAIN ----------------
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

        // ---------------- TEXT INPUT ----------------
        int key = GetCharPressed();
        while (key > 0)
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

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            if (typingUsername && usernameLen > 0)
                username[--usernameLen] = '\0';

            if (typingPassword && passwordLen > 0)
                password[--passwordLen] = '\0';
        }
