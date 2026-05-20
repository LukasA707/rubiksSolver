#define SENSOR_H 

class Sensor {
  public:
    int pin;
    bool magnetDetected();
    Sensor(int sensorPin);
};