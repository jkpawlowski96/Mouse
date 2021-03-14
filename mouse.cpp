#include "mouse.h"

Mouse::Mouse(Point<int> start)
{
    position.localization = start;
}

Position<int> Mouse::GetPosition(){
    return position;
}


