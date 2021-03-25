#ifndef EXPANDER_H
#define EXPANDER_H

#include "si.h"

struct ExpanderPath{
    shared_ptr<Path<int>> path;
    Direction origin;
};

class Expander : public SI
{
public:
    Expander();
    Task Logic(SensorData sensorData);
private:
    shared_ptr<Path<int>> FirstUnnown();
    Direction NearestPath(shared_ptr<Path<int>> target);

    shared_ptr<Path<int>> nowPath;
    Direction nowDireciton;
    vector<shared_ptr<Path<int>>> pathList;


};
Task operator>(Direction a, Direction b);

#endif // EXPANDER_H
