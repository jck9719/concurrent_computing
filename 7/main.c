#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include "engine.h"


int main ()
{
    signal(SIGINT, cleanup);
    g_sharedMemory = shmget (KEY, ROWS * COLS * sizeof(int), 0777|IPC_CREAT);
    int *shMem = shmat (g_sharedMemory, 0, 0);
    int **board = malloc (ROWS * sizeof(board[0]));

    for (int i = 0; i < ROWS; i++)
        board[i] = (shMem + i*ROWS);

    struct sembuf attemptMoveX={SEM_1, -1, 0},
                  unlockO={SEM_2, 1, 0},
                  attemptMoveO={SEM_2, -1, 0},
                  unlockX={SEM_1, 1, 0},
                  *attemptMove,
                  *unlockOpponent;

    int playerSign = 0;
    if((g_semaphores = semget (KEY, 2, 0777|IPC_CREAT|IPC_EXCL)) > 0)
    {
        printf("You start as \tX!\n");
        playerSign = CROSS;
        semctl(g_semaphores, SEM_1, SETVAL, 0);
        semctl(g_semaphores, SEM_2, SETVAL, 0);
        attemptMove = &attemptMoveX;
        unlockOpponent = &unlockO;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = EMPTY;
            }
        }
    }
    else
    {
        printf("You are \tO!\n");
        playerSign = CIRCLE;
        g_semaphores = semget(KEY, 2, 077|IPC_CREAT);
        attemptMove = &attemptMoveO;
        unlockOpponent = &unlockX;
        semop(g_semaphores, unlockOpponent, 1);
    }

    while(1)
    {
        printf("Waiting...\n");
        semop(g_semaphores, attemptMove, 1);

        show_board(board);

        if (state_check(board) == GAME_END)
        {
            cleanup(0);
        }

        int row, col;
        do
        {
            printf("Your turn!\nEnter row number and column nuber!\n");
            scanf("%d %d", &row, &col);
        } while(movement(board, row-1, col-1, playerSign) < 0);

        show_board(board);
        semop(g_semaphores, unlockOpponent, 1);
    }

    free(board);
    cleanup(0);
}