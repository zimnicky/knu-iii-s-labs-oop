#include <X11/Xlib.h>

extern "C"{

struct Circle
{
    int x, y, r;
};

int f(int x, int y, int r)
{
    return x*x + y*y - r*r;
}

int Fst(int x, int y, int r)
{
    return f(x+1,y,r) + f(x,y-1,r); // sign is the same as sign of middle point
}

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

}
