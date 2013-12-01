#include <X11/Xlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "lsystem.h"

using namespace std;

void initWindow(Display *&display, Window &window, GC &gc)
{
    display = XOpenDisplay(NULL);

    int screen = DefaultScreen(display);
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

}

void redraw(Display *display, Window &window, GC &gc, LSystem &lsystem)
{
    XWindowAttributes attributes;
    XSetForeground(display, gc, 0xFFFFFF);
    XGetWindowAttributes(display, window, &attributes);
    XFillRectangle(display, window, gc, 0, 0, attributes.width, attributes.height);
    XSetForeground(display, gc, 0);
    XPoint center;
    center.x = attributes.width / 2;
    center.y = attributes.height /2;
    lsystem.drawFractal(center, display, window, gc, 20);
}

int main()
{
    LSystem lSystem;
    ifstream f("input.txt");
    lSystem.loadParams(f);
    f.close();

    Display *display;
    Window window;
    GC gc;

    initWindow(display, window, gc);

    XEvent event;

    while (1)
    {
        XNextEvent(display, &event);
        switch (event.type) {
            case ButtonPress:{
                    if (event.xbutton.button ==  Button1)
                    {
                    }
                    else if(event.xbutton.button ==  Button3)
                    {
                        redraw(display, window, gc, lSystem);
                    }
                    break;
            }
            case Expose:
                    redraw(display, window, gc, lSystem);
                    break;
            default:
                    break;
        }
    }

    XFreeGC(display, gc);
    XCloseDisplay(display);
    return 0;
}
