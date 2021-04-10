#ifndef HUMANCONTROLL_H
#define HUMANCONTROLL_H
#include "geometry.h"
#include "expander.h"
class HumanControll: public SI
{
public:
    HumanControll(Direction initDirection);
    Task Logic(SensorData sensorData);
    void SetDirection(Direction d);
private:
    Direction mouseDirection;
    Direction nextDirection;
};

#endif // HUMANCONTROLL_H
