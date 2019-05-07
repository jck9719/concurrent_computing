#include <X11/Xlib.h>
#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include "window.h"


int draw (int n, char* host)
{
	Display *display;
	Window window;
	XSetWindowAttributes window_attributes;
	GC gc;
	Visual *visual;
	XEvent event;
  	XColor xcolor;

    int depth, screen, i, j;

	display = XOpenDisplay (host);
	screen = DefaultScreen (display);
	visual = DefaultVisual (display, screen);
	depth = DefaultDepth (display, screen);

	window_attributes.background_pixel = XWhitePixel (display, screen);
	window_attributes.override_redirect = False;

	window = XCreateWindow(
    display,
    XRootWindow (display, screen),
    X, Y, WIDTH, HEIGHT, BORDER_WIDTH,
    depth, InputOutput, visual,
    CWBackPixel|CWOverrideRedirect,
    &window_attributes
    );

	XSelectInput (display, window, ExposureMask|KeyPressMask);
	XMapWindow (display, window);
	gc = DefaultGC(display, screen);

    while (1)
    {
		XNextEvent (display, &event);
		switch (event.type)
        {
		    case Expose:
			    for (i = 0; i < 32; ++i)
                    {
				        for (j = 0; j < 32; ++j)
                            {
                                XSetForeground(display, gc, xcolor.pixel + PIXEL_I * i + PIXEL_J * j);
						        XFillRectangle(display, window, gc, 150 * i + n, 250 * j + n, 350 * (i + 1), 450 * (j + 1));
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