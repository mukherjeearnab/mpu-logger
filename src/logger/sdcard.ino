// SD Card dependencies
#include <SD.h>
#include <SPI.h>

// SD Card initialization
void initSDCard() {
    // Initialize SD Card
    Serial.println("SDC init.");
    if (!SD.begin(10)) {
        Serial.println("Init. failed!");
        while (1)
            ;
    }

    Serial.println("Init. Succ");
}

// Write Content to SD Card
void write2SDCard(String filename, String content) {
    // Turn on Activity LED
    digitalWrite(ACTIVITY_LED_PIN, HIGH);

    // Initialize File Object
    File file = SD.open(filename, FILE_WRITE);

    // if the file opened okay, write to it:
    if (file) {
        Serial.print("W-> ");
        Serial.println(filename);

        // Write to the file
        file.print(content);

        // close the file:
        file.close();

        Serial.println("Done");
    } else {
        // if the file didn't open, print error:
        Serial.print("Error! ");
        Serial.println(filename);
    }

    // Turn off Activity LED
    digitalWrite(ACTIVITY_LED_PIN, LOW);
}

// Function to read file counters from  file 'count'
int getFileCounter() {
    // Turn on Activity LED
    digitalWrite(ACTIVITY_LED_PIN, HIGH);

    // Return File Int String
    int count = 6565;  // character 'A'

    // Initialize File Object
    File file = SD.open("count");

    // if the file opened okay, write to it:
    if (file) {
        Serial.println("R-> count");

        // read the first byte / character from the counter file
        if (file.available()) {
            count = int(file.read()) * 100;
        }

        if (file.available()) {
            count += int(file.read());
        }

        // close the file:
        file.close();

    } else {
        // if the file didn't open, print error:
        Serial.print("Error count!");
    }

    // Turn off Activity LED
    digitalWrite(ACTIVITY_LED_PIN, LOW);

    return count;
}

// Remove / delete a from from SD Card
void removeFile(String filename) {
    Serial.print("D-> ");
    Serial.println(filename);

    SD.remove(filename);

    Serial.println("Done");
}