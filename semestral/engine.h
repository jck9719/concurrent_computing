#ifndef _ENGINE_H_
#define _ENGINE_H_

#define ROWS 25
#define COLS 25
#define EMPTY 0
#define CIRCLE 1
#define CROSS 1000
#define WIN 5
#define GAME_END -1
#define KEY 666
#define SEM_1 0
#define SEM_2 1

extern int g_sharedMemory, g_semaphores;

void show_board(int** board);
int movement(int** board, int col, int row, int sign);
int state_check(int** board);
void cleanup(int signal);

#endif
