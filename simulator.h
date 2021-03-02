#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <memory>
#include "map.h"


class Simulator
{
public:
    Simulator();
    bool SetMap(string mathFilePath);
private:
    unique_ptr<Map> map;

};

#endif // SIMULATOR_H
