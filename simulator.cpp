#include "simulator.h"

Simulator::Simulator()
{
}

bool Simulator::SetMap(string mapFilePath){
    Map newMap(mapFilePath);
    this->map.reset(&newMap);
    return true;
}
