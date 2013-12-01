#include "lsystem.h"
#include <cmath>


LSystem::LSystem()
{
    rotationAngle = M_PI/2;
}

void LSystem::loadParams(istream &in)
{
    ruleshasF = false;
    getline(in, axiom,'\n');
    int countRules = 0;
    in >> countRules;
    rules.resize(countRules);
    for (int i = 0; i < countRules; i++)
    {
        in >> rules[i].symbol;
        if (rules[i].symbol == 'F')
            ruleshasF = true;
        in.get();
        getline(in, rules[i].replacement,'\n');
    }
    in >> rotationAngle >> level;
}


void LSystem::drawFractal(XPoint pos, Display *display, Drawable &drawable, GC &gc, float step)
{
    this->display = display;
    this->drawable = &drawable;
    this->gc = &gc;
    draw(axiom, State(pos,0.f, step), 0);
}

void LSystem::draw(const string &axiom, State state, unsigned int currLevel)
{
    if (currLevel == level)
        return;
    for (auto c: axiom)
    {
        switch (c)
        {
        case 'f':   // go ahead
        {
            state.pos.x = round(state.pos.x + state.step * cos(state.rotation));
            state.pos.y = round(state.pos.y + state.step * sin(state.rotation));
            break;
        }
        case '+':   // rotate left
            state.rotation -= rotationAngle;
            break;
        case '-':   // rotate right
            state.rotation += rotationAngle;
            break;
        case '[':   // push state
            memory.push(state);
            break;
        case ']':   // pop state
            state = memory.top();
            memory.pop();
            break;
        case '^':
            state.rotation = -M_PI/2;
            break;
        case '&':
            state.rotation = M_PI/2;
            break;
        case '/':
            state.rotation = 0;
            break;
        case '\\':
            state.rotation = -M_PI;
            break;
        case '|':
            state.rotation += M_PI;
            break;
        case 'F':   // go ahead and draw line
        {
            if (!ruleshasF || currLevel == level - 1)
            {
                XPoint t(state.pos);
                state.pos.x = round(state.pos.x + state.step * cos(state.rotation));
                state.pos.y = round(state.pos.y + state.step * sin(state.rotation));

                XDrawLine(display, *drawable, *gc, t.x, t.y, state.pos.x, state.pos.y);
                break;
            }
        }
        default: // replacement
        {
            for (auto i: rules)
                if (i.symbol == c)
                {
                    draw(i.replacement, State(state), currLevel + 1);
                    break;
                }
        }
        };
    }
}
