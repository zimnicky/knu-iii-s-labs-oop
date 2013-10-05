#include <X11/Xlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <dlfcn.h>

using namespace std;

struct Circle
{
    Circle(XPoint p, int r)
    {
        x = p.x;
        y = p.y;
        this->r = r;
    }
    int x, y, r;
};

typedef void (*DrawCirclesFunc)(Circle *, int, Display *, Drawable &, GC &);
typedef void (*DrawCircleFunc)(int, int,int, Display *, Drawable &, GC &);

DrawCircleFunc drawCircle;
DrawCirclesFunc drawCircles;

inline int sqr(int x)
{
    return x*x;
}

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

void redraw(Display *display, Window &window, GC &gc, vector<Circle> &circles, void* lib)
{
    XWindowAttributes attributes;
    XSetForeground(display, gc, 0xFFFFFF);
    XGetWindowAttributes(display, window, &attributes);
    XFillRectangle(display, window, gc, 0, 0, attributes.width, attributes.height);
    XSetForeground(display, gc, 0);
    drawCircles(circles.data(), circles.size(), display, window, gc);
}

int main()
{
    void* lib = dlopen("./lib2lib.so", RTLD_NOW);
    if (!lib)
    {
        fprintf(stderr,"dlopen() error: %s\n", dlerror());
        return 1;
    };

    drawCircle = (DrawCircleFunc)dlsym(lib, "drawCircle");
    drawCircles = (DrawCirclesFunc)dlsym(lib,"drawCircles");

    Display *display;
    Window window;
    GC gc;

    initWindow(display, window, gc);

    XEvent event;

    vector<Circle> circles;
    XPoint newCenter;       // center of new circle
    bool newCircle = false;

	while (1)
	{
		XNextEvent(display, &event);
        switch (event.type) {
            case ButtonPress:{
                    if (event.xbutton.button ==  Button1)
                    {
                        newCenter.x = event.xbutton.x;
                        newCenter.y = event.xbutton.y;
                        newCircle = true;
                    }
                    else if(event.xbutton.button ==  Button3)
                    {
                        newCircle = false;
                        redraw(display, window, gc, circles, lib);
                    }
                    break;
            }
            case ButtonRelease:{
                    if (event.xbutton.button ==  Button1 && newCircle)
                    {
                        int x = event.xbutton.x;
                        int y = event.xbutton.y;
                        int r = sqr(x-newCenter.x) + sqr(y-newCenter.y);
                        r = sqrt(r);
                        circles.push_back(Circle(newCenter, r));
                    }
                    break;
            }
            case MotionNotify:{
                if (event.xmotion.state & Button1MotionMask && newCircle)
                {
                    int x = event.xbutton.x;
                    int y = event.xbutton.y;

                    int r = sqr(x-newCenter.x) + sqr(y-newCenter.y);
                    r = sqrt(r);

                    redraw(display, window, gc, circles, lib);
                    drawCircle(newCenter.x, newCenter.y, r, display, window, gc);
                }
                break;
            case Expose:
                    redraw(display, window, gc, circles, lib);
                    break;
            }
            default:
                    break;
        }
	}

	XFreeGC(display, gc);
	XCloseDisplay(display);
    dlclose(lib);
	return 0;
}
