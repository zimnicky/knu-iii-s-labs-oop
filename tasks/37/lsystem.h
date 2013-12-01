#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <X11/Xlib.h>

using namespace std;

/* Interpretation:
 *      F: move ahead with drawing
 *      f: move ahead
 *      +: turn left
 *      -: turn right
 *      [: push state
 *      ]: pop state
 *      ^: turn up
 *      &: turn down
 *      \: bend to the left
 *      /: bend to the right
 *      |: turn 180 degrees
 */
class LSystem
{
protected:
    struct Rule
    {
        char symbol;
        string replacement;
    };

    struct State
    {
        XPoint pos;
        float rotation;
        float step;
        State(const XPoint &position, float angle, float st = 1.0):pos(position),rotation(angle),step(st){}
        State(const State &state):pos(state.pos), rotation(state.rotation), step(state.step){}
    };

    string axiom;
    vector<Rule> rules;
    bool ruleshasF;         // true if there are rules with F

    float rotationAngle;      // angle of turns
    unsigned int level;     // level of fractal

    stack<State> memory;    // saved states

    Display *display;
    Drawable *drawable;
    GC *gc;
    virtual void draw(const string &axiom, State state, unsigned int currLevel);
public:
    LSystem();
    virtual void loadParams(istream &in);
    virtual void drawFractal(XPoint pos, Display *display, Drawable &drawable, GC &gc, float step = 10);
};

#endif // LSYSTEM_H
