#ifndef GAME_H
#define GAME_H

void InitGame();
void DrawGame();
void HandleGameClick(int x, int y);
void ResetGame();

extern int gameOver;
extern char winner;

int CheckDraw();

#endif