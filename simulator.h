#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <memory>
#include "map.h"
#include <QMainWindow>


class Simulator
{
public:
    Simulator();
    bool SetMap(string mathFilePath);

    shared_ptr<Map> map;

private:

};

#endif // SIMULATOR_H
