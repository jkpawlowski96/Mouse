#ifndef SI_H
#define SI_H
#include "geometry.h"
#include "map.h"
#include "sensor_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Task for mouse
 * 
 */
enum Task{
    TaskUnnown=-1,
    Forward=0,
    RotateLeft=1,
    RotateRight=2,
    TurnAround=3
};

/**
 * @brief SI - mouse controll logic
 * 
 */
class SI
{
public:
    /**
     * @brief Construct a new SI object
     * 
     */
    SI();
    /**
     * @brief Destroy the SI object
     * 
     */
    virtual ~SI();
    /**
     * @brief Call SI to get task
     * 
     * @param sensorData 
     * @return Task 
     */
    Task Call(SensorData sensorData);
    /**
     * @brief Logic implementation
     * 
     * @param sensorData 
     * @return Task 
     */
    virtual Task Logic(SensorData sensorData);
private:
    Task RandomTask(SensorData sensorData);
};

/**
 * @brief Get task of rotation from start direction to target direction
 * 
 * @param a 
 * @param b 
 * @return Task 
 */
Task operator>(Direction a, Direction b);

#endif // SI_H
