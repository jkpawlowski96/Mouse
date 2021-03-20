#ifndef SI_H
#define SI_H
#include "geometry.h"
#include "sensor_data.h"

enum Task{
    TaskUnnown=-1,
    Forward=0,
    RotateUp=1,
    RotateLeft=2,
    RotateRight=3,
    RotateDown=4
};

class SI
{
public:
    SI();
    Task Call(Position<int> position, SensorData sensorData);
};

#endif // SI_H
