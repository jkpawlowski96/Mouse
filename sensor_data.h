#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

struct SensorData{
    bool wallDetected;
    SensorData(){};
    SensorData(bool _wallDetected):wallDetected(_wallDetected){}
};


#endif // SENSOR_DATA_H
