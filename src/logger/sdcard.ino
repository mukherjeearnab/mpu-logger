// SD Card dependencies
#include <SD.h>
#include <SPI.h>

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
    digitalWrite(ACTIVITY_LED_PIN, HIGH);

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
    digitalWrite(ACTIVITY_LED_PIN, LOW);
}

// Function to read file counters from counter.txt
char getFileCounter() {
    // Turn on Activity LED
    digitalWrite(ACTIVITY_LED_PIN, HIGH);

    // Return File Int String
    int count = 0;

    // Initialize File Object
    File file = SD.open("counter.txt");

    // if the file opened okay, write to it:
    if (file) {
        Serial.println("Reading Counter.");

        // read the first byte / character from the counter file
        if (file.available()) {
            count = int(file.read());
        }

        // close the file:
        file.close();

    } else {
        // if the file didn't open, print error:
        Serial.print("Error opening counter.txt ");
    }

    // Turn off Activity LED
    digitalWrite(ACTIVITY_LED_PIN, LOW);

    return count;
}