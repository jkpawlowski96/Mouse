#include "si.h"

SI::SI()
{

}

Task SI::Call(Position<int> position, SensorData sensorData)
{
    Task task;
    task.destination = position.localization + Point<int>(-1,0);
    return task;
}
