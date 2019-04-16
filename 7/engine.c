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

int g_sharedMemory, g_semaphores;

void printBoard(int** board)
{
    printf(" ");
    for (int i = 0; i < COLS; i++)
    {
        printf(" %d", i + 1);
    }
    printf("\n");
    for(int i = 0; i < COLS; i++)
    {
        printf("%d|", i + 1);
        for(int j = 0; j < ROWS; j++)
        {
            if (board[i][j] == CIRCLE)
            {
                printf("O");
            }

            if (board[i][j] == CROSS)
            {
                printf("X");
            }

            if (board[i][j] == EMPTY)
            {
                printf(" ");
            }

            printf("|");
        }

        printf("\n");
    }

    printf("\n");
}

int makeMove(int** board, int col, int row, int sign)
{
    if((col < COLS) && (row < ROWS) && (col >= 0) && (row >= 0) && (board[col][row] == EMPTY))
    {
        board[col][row] = sign;
        return 0;
    }
    else
    {
        printf("Incorrect movement.\n");
        return -1;
    }
}

int checkMove(int** board)
{
    int occupiedFields = 0;
    for (int i = 0; i < 3; i++)
    {
        int sumVertical = 0;
        int sumHorizontal = 0;
        int sumDiagonal = 0;
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != EMPTY)
            {
                occupiedFields += 1;
            }

            sumVertical += board[i][j];
            sumHorizontal += board[j][i];
            sumDiagonal += board[j][j];
        }

        if ((sumVertical == 3 * CIRCLE) || (sumHorizontal == 3 * CIRCLE) || (sumDiagonal == 3 * CIRCLE))
        {
            printf("O has won!\n");
            return GAME_END;
        }

        if ((sumVertical == 3 * CROSS) || (sumHorizontal == 3 * CROSS) || (sumDiagonal == 3 * CROSS))
        {
            printf("X has won!\n");
            return GAME_END;
        }
    }

    if (occupiedFields == COLS * ROWS)
    {
        printf("Draw!\n");
        return GAME_END;
    }

    return 0;
}

void cleanup(int signal)
{
    semctl(g_semaphores, 0, IPC_RMID, 0);
    shmctl(g_sharedMemory, IPC_RMID, 0);
    exit(0);
}