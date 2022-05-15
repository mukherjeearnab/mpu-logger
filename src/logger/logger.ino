#include <SD.h>
#include <SPI.h>

// WRITE ENABLE PIN number
const int WRITE_ENABLE_PIN = 7;
const int ACTIVITY_LED_PIN = 8;

// Reading and writing globals
String filename = "def.csv";
float readings[6];
String csvString;
File csvFile;
int closeFile = -1;

// Setup Method
void setup() {
    Serial.begin(115200);

    // Set Activity Pin
    pinMode(ACTIVITY_LED_PIN, OUTPUT);

    // Set Write Enable Pin
    pinMode(WRITE_ENABLE_PIN, INPUT_PULLUP);

    // Initialize SD Card
    initSDCard();

    // Initialize MPU6050
    initMPU6050();

    // Get File counter to determine filename
    int counter = getFileCounter();
    getFileName(counter);

    // Update Counter File
    // 1. Remove Counter File
    removeFile("count");
    // 2. Write latest count to file
    write2SDCard("count", incrementCounter(counter));

    // Write CSV Headers to SD Card
    write2SDCard(filename, "ts,ax,ay,az,gx,gy,gz\n");

    // Initialize Global CSV File Object (for Open Write)
    csvFile = SD.open(filename, FILE_WRITE);
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
    if (digitalRead(WRITE_ENABLE_PIN) == LOW) {
        openWrite(csvString);
        closeFile = 1;
    } else {
        if (closeFile == 1) {
            closeOWF();
            Serial.println("File Closed!");
        }
        if (closeFile != -1)
            closeFile = 0;
        Serial.println("Write Disabled!");
    }

    // Sleep for 25ms
    delay(25);
}

// -------------------
// Auxiliary functions
// -------------------

// Generate MPU6050 readings as CSV String
void getCSVOutput(float* readings) {
    csvString = String(millis()) + "," +
                String(readings[0]) + "," +
                String(readings[1]) + "," +
                String(readings[2]) + "," +
                String(readings[3]) + "," +
                String(readings[4]) + "," +
                String(readings[5]) + "\n";
}

// Generate filename from counter integer
void getFileName(int counter) {
    // Seperate 0th and 1st characters
    char c0 = char(counter % 100);
    char c1 = char(counter / 100);

    // Create the filename
    filename = String(c1) + String(c0) + String(".csv");
}

// Increment file counter
String incrementCounter(int counter) {
    // Seperate 0th and 1st characters
    char c0 = char(counter % 100);
    char c1 = char(counter / 100);

    c0++;
    if (c0 == '[') {
        c1++;
        c0 = 'A';
    }

    if (c1 == '[')
        c1 = 'A';

    return String(c1) + String(c0);
}

// Write Reading Content to SD Card (Open Write) -> should be faster
void openWrite(String content) {
    // Turn on Activity LED
    digitalWrite(ACTIVITY_LED_PIN, HIGH);

    // if the file opened okay, write to it:
    if (csvFile) {
        Serial.print("W-> ");
        Serial.println(filename);

        // Write to the file
        csvFile.print(content);
        Serial.println("Done");
    } else {
        // if the file didn't open, print error:
        Serial.print("OW Error! ");
        Serial.println(filename);
    }

    // Turn off Activity LED
    digitalWrite(ACTIVITY_LED_PIN, LOW);
}

// Close Open Write File
void closeOWF() {
    // close the file:
    csvFile.close();
}