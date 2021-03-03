#include "simulator.h"

Simulator::Simulator()
{
}

bool Simulator::SetMap(string mapFilePath){
    Map newMap(mapFilePath);
    this->map.release();
    this->map.reset(&newMap);
    return true;
}
