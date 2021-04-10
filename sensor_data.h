#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

/**
 * @brief Data received from sensor device
 * 
 */
struct SensorData{
    bool wallDetected;
    /**
     * @brief Construct a new Sensor Data object
     * 
     */
    SensorData(){};
    /**
     * @brief Construct a new Sensor Data object
     * 
     * @param _wallDetected 
     */
    SensorData(bool _wallDetected):wallDetected(_wallDetected){}
};


#endif // SENSOR_DATA_H
