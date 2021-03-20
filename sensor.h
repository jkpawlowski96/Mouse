#ifndef SENSOR_H
#define SENSOR_H
#include "geometry.h"
#include "map.h"
#include "mouse.h"
#include <memory>
#include "sensor_data.h"

class Sensor{
    SensorData Measure(shared_ptr<Map> map, shared_ptr<Mouse> mouse){
        return SensorData(false);
    }

};

#endif // SENSOR_H
