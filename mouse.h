#ifndef MOUSE_H
#define MOUSE_H
#include "si.h"
#include "sensor.h"
#include <iostream>

#define MOUSE_LINES {Line<double>(Point<double>(0.2,0.5),Point<double>(0.8,0.8))}
#define MOVE_STEP 0.1

/**
 * @brief Mouse (agent) representation in simulation 
 * 
 */
class Mouse
{
public:
    /**
     * @brief Get the Position object
     * 
     * @return Position<double> 
     */
    Position<double> GetPosition();
    /**
     * @brief Construct a new Mouse object
     * 
     * @param start 
     * @param direction 
     * @param _si 
     */
    Mouse(Point<int> start, Direction direction, SI *_si);
    /**
     * @brief Construct a new Mouse object
     * 
     */
    Mouse(){}
    /**
     * @brief Destroy the Mouse object
     * 
     */
    ~Mouse();
    /**
     * @brief Call mouse object (single tick)
     * 
     * @param map 
     * @return true 
     * @return false 
     */
    bool Call(shared_ptr<Map> map);
    /**
     * @brief Set the Speed oof mouse object
     *
     * @param _speed 
     */
    void SetSpeed(int _speed);
private:
    Position<double> position;
    SI *si;
    Sensor sensor;
    Task task;
    Point<double> move;
    Point<double> moveTarget;
    double speed;

};

#endif // MOUSE_H
