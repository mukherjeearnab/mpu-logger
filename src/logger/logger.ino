// WRITE ENABLE PIN number
const int WRITE_ENABLE_PIN = 7;

// Reading and writing globals
float readings[6];
char csvString[100];

// Setup Method
void setup() {
    // Set Activity Pin
    pinMode(LED_BUILTIN, OUTPUT);

    // Set Write Enable Pin
    pinMode(LED_BUILTIN, INPUT);

    // Initialize SD Card
    initSDCard();

    // Initialize MPU6050
    initMPU6050();

    // Write CSV Headers to SD Card
    write2SDCard("test.csv", "timestamp,ax,ay,az,gx,gy,gz\n");
}

// LOOP method
void loop() {
    // Fetch MPU6050 Reading
    getMPU6050Reading();

    // Generate CSV String for the Readings
    getCSVOutput(readings);

    // Log CSV Output to console
    Serial.print(csvString);

    // If Writing is enabled, write to the CSV
    if (digitalRead(WRITE_ENABLE_PIN) == HIGH)
        write2SDCard("test.csv", csvString);
    else
        Serial.print("Writing to SD card Disabled!");

    // Sleep for 25ms
    delay(25);
}

// -------------------
// Auxiliary functions
// -------------------

// Generate MPU6050 readings as CSV String
void getCSVOutput(float* readings) {
    // fstring '%d,%02f,%02f,%02f,%02f,%02f,%02f\n'
    sprintf(csvString, "%d,%02f,%02f,%02f,%02f,%02f,%02f\n", micros(), readings[0], readings[1], readings[2], readings[3], readings[4], readings[5]);
}
