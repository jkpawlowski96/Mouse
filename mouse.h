#ifndef MOUSE_H
#define MOUSE_H
#include "si.h"

#define MOUSE_LINES {Line<double>(Point<double>(0.2,0.5),Point<double>(0.8,0.8))}
#define MOVE_STEP 0.1

class Mouse
{
public:
    Position<double> GetPosition();
    Mouse(Point<int> start, shared_ptr<SI> _si);
    Mouse(){}
    void Call(SensorData sensorData);
private:
    Position<double> position;
    shared_ptr<SI> si;
    shared_ptr<Task> task;


};

#endif // MOUSE_H
