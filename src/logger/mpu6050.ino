// MPU6050 dependencies
#include <Adafruit_MPU6050.h>  // v2.2.0
#include <Adafruit_Sensor.h>
#include <Wire.h>

// MPU6050 object
Adafruit_MPU6050 mpu;

// Initialize MPU6050
void initMPU6050() {
    Serial.println("Initializing MPU6050.");

    // Try to initialize!
    if (!mpu.begin()) {
        Serial.println("MPU6050 initialization failed!");
        while (1) {
            delay(10);
        }
    }
    Serial.println("Found MPU6050.");

    // set accelerometer range to +-8G
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

    // set gyro range to +- 500 deg/s
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);

    // set filter bandwidth to 21 Hz
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    Serial.println("MPU6050 initialization done.");
}

// Get MPU6050 readings
void getMPU6050Reading() {
    /* Get new sensor events with the readings */
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Populate Sensor Reading
    readings[0] = a.acceleration.x;
    readings[1] = a.acceleration.y;
    readings[2] = a.acceleration.z;
    readings[3] = g.gyro.x;
    readings[4] = g.gyro.y;
    readings[5] = g.gyro.z;
}
