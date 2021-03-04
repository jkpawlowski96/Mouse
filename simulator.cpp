#include "simulator.h"

Simulator::Simulator()
{
}

bool Simulator::SetMap(string mapFilePath){
    this->map = make_shared<Map>(mapFilePath);
    return true;
}
