#ifndef EXPANDER_H
#define EXPANDER_H

#include "si.h"

/**
 * @brief Expander smart memory path
 * 
 */
struct ExpanderPath{
    shared_ptr<Path<int>> path;
    Direction origin;
};

/**
 * @brief Expander SI algorithm
 * 
 */
class Expander : public SI
{
public:
    /**
     * @brief Construct a new Expander object
     * 
     */
    Expander();
    /**
     * @brief Logic implementation of Expander
     * 
     * @param sensorData 
     * @return Task 
     */
    Task Logic(SensorData sensorData);
private:

    shared_ptr<Path<int>> FirstUnnown();
    Direction NearestPath(shared_ptr<Path<int>> target);
    Direction NearestPathToUnnown();
    shared_ptr<Path<int>> GetPathByLoc(Point<int> loc);
    shared_ptr<Path<int>> nowPath;
    Direction nowDireciton;
    vector<shared_ptr<Path<int>>> pathList;
};

#endif // EXPANDER_H
