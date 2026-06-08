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

