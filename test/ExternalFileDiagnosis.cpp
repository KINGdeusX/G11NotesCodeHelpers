#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(10, 11); // RX, TX

void setup() {
  bluetoothSerial.begin(115200); // Set the baud rate to match your Bluetooth module
  Serial.begin(115200);
}

void loop() {
  if (bluetoothSerial.available()) { // Check if there is data available to read from Bluetooth
    char received = bluetoothSerial.read(); // Read the incoming data
    Serial.print(String(received)); // Concatenate and print the received data to the Serial Monitor
  }
  if (Serial.available()) { // Check if there is data available to read from Serial Monitor
    char toSend = Serial.read(); // Read the incoming data
    bluetoothSerial.write(toSend); // Send the data to the Bluetooth module
  }
}
