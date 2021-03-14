#ifndef SENSOR_H
#define SENSOR_H
#include "map.h"
#include "mouse.h"
#include <memory>

struct SensorData{
    bool wallDetected;
    SensorData(bool _wallDetected):wallDetected(_wallDetected){}
};

class Sensor{
    SensorData Measure(shared_ptr<Map> map, shared_ptr<Mouse> mouse){
        return SensorData(false);
    }

};

#endif // SENSOR_H
