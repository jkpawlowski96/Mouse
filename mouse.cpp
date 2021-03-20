#include "mouse.h"

Mouse::Mouse(Point<int> start)
{
    position.localization = start;
}

Position<int> Mouse::GetPosition(){
    position.localization = position.localization + Point<int>(-1,0);
    return position;
}


