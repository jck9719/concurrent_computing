#include <X11/Xlib.h>
#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include "window.h"

int main(int argc, char *argv[])
{
    pid_t child_pid, wpid;
    int status = 0;
    int i;
    time_t start_time;
    time(&start_time);

    for (i = 1; i < argc; i++)
    {
        if ((child_pid = fork()) == 0)
        {
            new_window(i, NULL);
            exit(0);
        }
    }

  	while ((wpid = wait(&status)) > 0)
    {
      int n = status >> 8;
      time_t end_time;
      time(&end_time);
      double t = difftime(end_time, start_time);
      printf("[PID: %5d] XDisplay number %d closed after %2.f second(s) (%s).\n", (int) wpid, n, t, argv[n]);
    }
    return 0;
}
