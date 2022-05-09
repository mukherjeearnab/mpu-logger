// WRITE ENABLE PIN number
const int WRITE_ENABLE_PIN = 7;
const int ACTIVITY_LED_PIN = 8;

// Reading and writing globals
String filename = "def.csv";
float readings[6];
String csvString;

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

    filename = String(counter) + ".csv";

    // Update Counter File
    write2SDCard("count", String(++counter));

    // Write CSV Headers to SD Card
    write2SDCard(filename, "ts,ax,ay,az,gx,gy,gz\n");
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
    if (digitalRead(WRITE_ENABLE_PIN) == LOW)
        write2SDCard(filename, csvString);
    else
        Serial.print("Write Disabled!");

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
