#include "raylib.h"
#include <stdio.h>
#include "game.h"
#include <string.h>

char board[3][3];
int currentPlayer = 1;
int gameOver = 0;
char winner = ' ';

int matchCount = 0;


void InitGame()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';

    currentPlayer = 1;
    gameOver = 0;
    winner = ' ';
}
void ResetGame()
{
    InitGame();
}


void SaveMatch(char w)
{
    FILE *f = fopen("stats.txt", "a+");
    if (!f) return;

    // Count existing games
    int count = 0;
    char line[100];

    rewind(f);
    while (fgets(line, sizeof(line), f))
    {
        if (strncmp(line, "Game", 4) == 0)
            count++;
    }

    fprintf(f, "Game %d: %c\n", count + 1, w);

    fclose(f);
}


