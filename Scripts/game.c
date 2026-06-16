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

int CheckWin()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != ' ' &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
            return 1;
    }

    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] != ' ' &&
            board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
            return 1;
    }

    if (board[0][0] != ' ' &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
        return 1;

    if (board[0][2] != ' ' &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
        return 1;

    return 0;
}


void HandleGameClick(int x, int y)
{
    if (gameOver) 
    {
         if (x >= 300 && x <= 500 &&
        y >= 470 && y <= 520)
       {
           ResetGame();
       }
        return;
    }

    int col = (x - 100) / 200;
    int row = (y - 150) / 100;

    if (col >= 0 && col < 3 && row >= 0 && row < 3)
    {
        if (board[row][col] == ' ')
        {
            board[row][col] = (currentPlayer == 1) ? 'X' : 'O';

            if (CheckWin())
            {
                gameOver = 1;
                winner = (currentPlayer == 1) ? 'X' : 'O';
                SaveMatch(winner);
            }
            else if (CheckDraw())
            {
                gameOver = 1;
                winner = 'D';  // D = Draw
                SaveMatch(winner);
            }

            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }
    }
}


void DrawGame()
{
    DrawText("TIC TAC TOE", 300, 40, 30, BLACK);

    DrawRectangle(10, 10, 120, 40, DARKGRAY);
    DrawText("STATS", 35, 20, 20, WHITE);

    DrawLine(300, 150, 300, 450, BLACK);
    DrawLine(500, 150, 500, 450, BLACK);
    DrawLine(100, 250, 700, 250, BLACK);
    DrawLine(100, 350, 700, 350, BLACK);

   
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int x = 170 + j * 200;
            int y = 180 + i * 100;

            if (board[i][j] == 'X')
                DrawText("X", x, y, 60, RED);

            if (board[i][j] == 'O')
                DrawText("O", x, y, 60, BLUE);
        }
    }


    if (gameOver)
    {
        if (winner == 'X')
            DrawText("Player X WON!", 280, 520, 30, GREEN);
        else if (winner == 'O')
            DrawText("Player O WON!", 280, 520, 30, GREEN);
        else if (winner == 'D')
            DrawText("GAME DRAW!", 300, 520, 30, ORANGE);

        DrawRectangle(300, 470, 200, 50, DARKGREEN);
        DrawText("NEW GAME", 335, 485, 20, WHITE);
    }
}

int CheckDraw()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;

    return 1;
}
