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
    RotateLeft=1,
    RotateRight=2,
    TurnAround=3
};

class SI :protected Map
{
public:
    SI();
    virtual Task Call(SensorData sensorData);
    virtual Task Logic(SensorData sensorData);
private:
    void UpdateMap(Position<int> position, SensorData sensorData);
    shared_ptr<Path<int>> PathTo(shared_ptr<Path<int>> start, shared_ptr<Path<int>> stop);
    Task RandomTask(SensorData sensorData);
    //vector<Path<int>> mapPaths;
};

Task operator>(Direction a, Direction b);

#endif // SI_H
