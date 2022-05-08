// MPU6050 dependencies
#include <Adafruit_MPU6050.h>  // v2.2.0
#include <Adafruit_Sensor.h>
#include <Wire.h>

// SD Card dependencies
#include <SD.h>
#include <SPI.h>

// MPU6050 object
Adafruit_MPU6050 mpu;

void setup() {
    // Set Activity Pin
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
}

// -------------------
// Auxiliary functions
// -------------------

// ***** START SD Card Functions *****

// SD Card initialization
void initSDCard() {
    // Initialize SD Card
    Serial.println("Initializing SD Card.");
    if (!SD.begin(10)) {
        Serial.println("SD Card initialization failed!");
        while (1)
            ;
    }

    Serial.println("SD Card initialization done.");
}

// Write Content to SD Card
void write2SDCard(String filename, String content) {
    // Turn on Activity LED
    digitalWrite(LED_BUILTIN, HIGH);

    // Initialize File Object
    File file = SD.open(filename, FILE_WRITE);

    // if the file opened okay, write to it:
    if (file) {
        Serial.print("Writing to ");
        Serial.println(filename);

        // Write to the file
        file.print(content);

        // close the file:
        file.close();

        Serial.println("Done writing to file.");
    } else {
        // if the file didn't open, print error:
        Serial.print("Error opening file ");
        Serial.println(filename);
    }

    // Turn off Activity LED
    digitalWrite(LED_BUILTIN, LOW);
}

// ***** END SD Card Functions *****

// ***** START MPU6050 Functions *****

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

// ***** END MPU6050 Functions *****
