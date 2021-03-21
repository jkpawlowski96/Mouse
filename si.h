#ifndef SI_H
#define SI_H
#include "geometry.h"
#include "map.h"
#include "sensor_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Task{
    TaskUnnown=-1,
    Forward=0,
    RotateUp=1,
    RotateLeft=2,
    RotateRight=3,
    RotateDown=4
};

class SI :private Map
{
public:
    SI();
    virtual Task Call(Position<int> position, SensorData sensorData);
private:
    void UpdateMap(Position<int> position, SensorData sensorData);
    shared_ptr<Path<int>> FirstUnnown();
    shared_ptr<Path<int>> PathTo(shared_ptr<Path<int>> start, shared_ptr<Path<int>> stop);
    Task RandomTask(Position<int> position, SensorData sensorData);
    //vector<Path<int>> mapPaths;
};

#endif // SI_H
