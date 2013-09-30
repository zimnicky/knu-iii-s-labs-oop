#include <X11/Xlib.h>
#include <iostream>

using namespace std;

int main()
{
	Display *display;
	Window window;
	XEvent event;
	GC gc;
	int screen;

	display = XOpenDisplay(NULL);

	screen = DefaultScreen(display);
	window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, 400, 400, 1,
						   0, 0xFFFFFF);

	XGCValues values;
	values.plane_mask = AllPlanes;
	values.foreground = 0;
	values.background = 0xFFFFFF;
	unsigned long valuemask = GCPlaneMask | GCForeground | GCBackground;
	gc = XCreateGC(display, window, valuemask, &values);

	XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask
								  | ButtonReleaseMask | PointerMotionMask);
	XMapWindow(display, window);

	XStoreName(display, window, "Lab #2");

	while (1)
	{
		XNextEvent(display, &event);
		switch (event.type) {
			case ButtonPress:{
					if (event.xbutton.button ==  Button1)
					{
						int x = event.xbutton.x;
						int y = event.xbutton.y;
						cout << "Button1 pressed " << x << " " << y << endl;
					}
					break;
			}
			case ButtonRelease:{
					if (event.xbutton.button ==  Button1)
					{
						int x = event.xbutton.x;
						int y = event.xbutton.y;
						cout << "Button1 realised " << x << " " << y << endl;
					}
					break;
			}
			case MotionNotify:{
				if (event.xmotion.state & Button1MotionMask)
				{
					int x = event.xbutton.x;
					int y = event.xbutton.y;
					XDrawPoint(display, window, gc, x, y);
					//cout << x << " " << y << endl;
				}
				break;
			}
			default:
					break;
		}
	}

	XFreeGC(display, gc);
	XCloseDisplay(display);
	return 0;
}
