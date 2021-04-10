#ifndef HUMANCONTROLL_H
#define HUMANCONTROLL_H
#include "geometry.h"
#include "expander.h"

/**
 * @brief Human controlled si
 * 
 */
class HumanControll: public SI
{
public:
    /**
     * @brief Construct a new Human Controll object
     * 
     * @param initDirection 
     */
    HumanControll(Direction initDirection);
    /**
     * @brief Login implementation
     * 
     * @param sensorData 
     * @return Task 
     */
    Task Logic(SensorData sensorData);
    /**
     * @brief Set the Direction of mouse
     * 
     * @param d 
     */
    void SetDirection(Direction d);
private:
    Direction mouseDirection;
    Direction nextDirection;
};

#endif // HUMANCONTROLL_H
