#ifndef MOUSE_H
#define MOUSE_H
#include "geometry.h"

#define MOUSE_LINES {Line<double>(Point<double>(0.2,0.5),Point<double>(0.8,0.8))}

class Mouse
{
public:
    Position<int> GetPosition();
    Mouse(Point<int> start);
    Mouse(){}

private:
    Position<int> position;
};

#endif // MOUSE_H
