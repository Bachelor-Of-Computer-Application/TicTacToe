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


