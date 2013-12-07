#include "edge.h"
#include <cmath>

double Edge::length()
{
    return sqrt((p1.x() - p2.x())*(p1.x() - p2.x()) + (p1.y() - p2.y())*(p1.y() - p2.y()));
}

