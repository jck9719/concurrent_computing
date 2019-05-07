#include <X11/Xlib.h>
#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int new_window(int n, char* host)
{
	Display *display;
	Window window;
	XSetWindowAttributes window_attributes;
	GC gc;
	Visual *visual;
	int depth;
	int screen;
	XEvent event;
  XColor xcolor;

	display = XOpenDisplay(host);
	screen = DefaultScreen(display);
	visual = DefaultVisual(display,screen);
	depth = DefaultDepth(display,screen);

	window_attributes.background_pixel = XWhitePixel(display,screen);
	window_attributes.override_redirect = False;

	window = XCreateWindow(
    display,
    XRootWindow(display, screen),
    100, 100, 200, 200, 10,
    depth, InputOutput, visual,
    CWBackPixel|CWOverrideRedirect,
    &window_attributes
  );
	XSelectInput(display,window,ExposureMask|KeyPressMask);
	XMapWindow(display,window);
	gc = DefaultGC(display,screen);

	int i, j;

	while (1)
  {
		XNextEvent(display,&event);
		switch (event.type)
    {
			case Expose:
				for (i = 0; i < 32; i++)
        {
					for (j = 0; j < 32; j++)
          {
            XSetForeground(display, gc, xcolor.pixel+1345002*i+6789121*j);
						XFillRectangle(display, window, gc, 150*i+n, 250*j+n, 350*(i+1), 450*(j+1));
						XFlush(display);
					}
				}
				break;
			case KeyPress:
				XCloseDisplay(display);
				exit(n);
		}
	}
}

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
