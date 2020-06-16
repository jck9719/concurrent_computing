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

void show_board(int** board)
{
    printf(" ");
    for (int i = 0; i < COLS; i++)
    {
        // printf(" %d", i + 1);
        if (i == 0) {
            printf("   %d", i + 1);
        } else  if (i < 10) {
            printf("   %d", i + 1);
        } else {
            printf("  %d", i + 1);
        }
        
    }
    printf("\n");
    for(int i = 0; i < COLS; i++)
    {
        if (i + 1 > 9)
        {
            printf("%d|", i + 1);
        } else {
            printf("%d |", i + 1);
        }
        
        for(int j = 0; j < ROWS; j++)
        {
            if (board[i][j] == CIRCLE)
            {
                printf(" O");
            }

            if (board[i][j] == CROSS)
            {
                printf(" X");
            }

            if (board[i][j] == EMPTY)
            {
                printf(" ");
            }

             if (board[i][j] == CROSS || board[i][j] == CIRCLE)
             {
                 printf(" |");
             } else {
                 printf("  |");
             }
        }

        printf("\n");
    }

    // printf("%d", ROWS);
    printf("\n");
}

int movement(int** board, int col, int row, int sign)
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

int state_check(int** board)
{
    int sumVertical = 0;
    int sumDiagonal = 0;
    int sumHorizontal = 0;

    //Check vertical
    for (int i = 0; i < ROWS; i++)
    {
        sumVertical = 0;
        for (int j = 0; j < COLS; j++)
        {
            sumVertical = 0;
            if (j < 20) {
                for (int k = j; k < j + WIN; k++)
                {
                    sumVertical += board[i][k];
                }
                if (sumVertical == WIN * CIRCLE) {
                    printf("O has won!\n");
                    return GAME_END;
                } else if (sumVertical == WIN * CROSS) {
                    printf("X has won!\n");
                    return GAME_END;
                }
            } else {
                break;
            }
        }
    }

    //Check horizontal
    for (int i = 0; i < ROWS; i++)
    {
        sumHorizontal = 0;
        for (int j = 0; j < COLS; j++)
        {
            sumHorizontal = 0;
            if (j < 20) {
                for (int k = j; k < j + WIN; k++)
                {
                    sumHorizontal += board[k][i];
                }
                if (sumHorizontal == WIN * CIRCLE) {
                    printf("O has won!\n");
                    return GAME_END;
                } else if (sumHorizontal == WIN * CROSS) {
                    printf("X has won!\n");
                    return GAME_END;
                }
            } else {
                break;
            }
        }
    }

    for (int i = 0; i < ROWS - WIN + 1; i++)
    {
        sumDiagonal = 0;
        for (int j = 0; j < ROWS - WIN + 1; j++)
        {
            sumDiagonal = 0;
            //diagonal left-right
            for (int k = 0; k < WIN; k++)
            {
                sumDiagonal += board[i + k][j + k];
            }


            //ifs
            if (sumDiagonal == WIN * CIRCLE) {
                    printf("O has won!\n");
                    return GAME_END;
                } else if (sumDiagonal == WIN * CROSS) {
                    printf("X has won!\n");
                    return GAME_END;
                } else {
                sumDiagonal = 0;
            }

            for (int k = 0; k < WIN; k++)
            {
                sumDiagonal += board[i + k][j + WIN - 1 - k];
            }

            //ifs
            if (sumDiagonal == WIN * CIRCLE) {
                    printf("O has won!\n");
                    return GAME_END;
                } else if (sumDiagonal == WIN * CROSS) {
                    printf("X has won!\n");
                    return GAME_END;
                }
        }

    }

    return 0;
}

void cleanup(int signal)
{
    semctl(g_semaphores, 0, IPC_RMID, 0);
    shmctl(g_sharedMemory, IPC_RMID, 0);
    printf ("Game exited!\n");
    exit(0);
}