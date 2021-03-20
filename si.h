#ifndef SI_H
#define SI_H
#include "geometry.h"
#include "sensor_data.h"

struct Task{
    Point<int> destination;
    Direction direction;
};

class SI
{
public:
    SI();
    Task Call(Position<int> position, SensorData sensorData);
};

#endif // SI_H
