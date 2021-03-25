#ifndef MOUSE_H
#define MOUSE_H
#include "si.h"
#include "sensor.h"
#include <iostream>

#define MOUSE_LINES {Line<double>(Point<double>(0.2,0.5),Point<double>(0.8,0.8))}
#define MOVE_STEP 0.1

class Mouse
{
public:
    Position<double> GetPosition();
    Mouse(Point<int> start, SI *_si);
    Mouse(){}
    void Call(shared_ptr<Map> map);
    void SetSpeed(int _speed);
private:
    Position<double> position;
    //shared_ptr<SI> si;
    SI *si;
    Sensor sensor;
    Task task;
    Point<double> move;
    Point<double> moveTarget;
    double speed;

};

#endif // MOUSE_H
