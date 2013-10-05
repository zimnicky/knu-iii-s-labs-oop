#include <X11/Xlib.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int f(int x, int y, int r)
{
    return x*x + y*y - r*r;
}

int Fst(int x, int y, int r)
{
    return f(x+1,y,r) + f(x,y-1,r); // sign is the same as sign of middle point
}

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

void drawCircle(int posX, int posY, int r, Display *display, Drawable &drawable, GC &gc)
{
    int x = 0;
    int y = r;
    /* Si & Ti -- the nearest integer point to the circle
     * Qi -- middle point between Si & Ti
     *    ____Ti
     *   | \  |
     *   |__\_|
     *   Si
    */

    //build quarter of circle
    while (y >= 0)
    {
        //circle is symmetric, draw 4 points(one in each quarter)
        XDrawPoint(display, drawable, gc, posX + x, posY + y);
        XDrawPoint(display, drawable, gc, posX - x, posY - y);
        XDrawPoint(display, drawable, gc, posX + x, posY - y);
        XDrawPoint(display, drawable, gc, posX - x, posY + y);

        //Choose point. If middle point is inside -- S, else  -- T
        if (Fst(x,y,r) < 0)
            x++;
        else
            y--;
    }
}

void drawCircles(Circle *circles, int count, Display *display, Drawable &drawable, GC &gc)
{
    for (int i = 0; i < count; i++)
    {
        drawCircle(circles[i].x, circles[i].y, circles[i].r, display, drawable, gc);
    }
}

inline int sqr(int x)
{
    return x*x;
}

void redraw(Display *display, Window &window, GC &gc, vector<Circle> &circles)
{
    XWindowAttributes attributes;
    XSetForeground(display, gc, 0xFFFFFF);
    XGetWindowAttributes(display, window, &attributes);
    XFillRectangle(display, window, gc, 0, 0, attributes.width, attributes.height);
    XSetForeground(display, gc, 0);
    drawCircles(circles.data(), circles.size(), display, window, gc);
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

int main()
{
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
                        redraw(display, window, gc, circles);
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

                    redraw(display, window, gc, circles);
                    drawCircle(newCenter.x, newCenter.y, r, display, window, gc);
                }
                break;
            case Expose:
                    redraw(display, window, gc, circles);
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
