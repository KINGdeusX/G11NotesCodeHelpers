#include <Arduino.h>
void policeLED(int r, int g, int b) {
    analogWrite(r, 255);
    delay(75);
    analogWrite(r, 0);
    delay(75);
    analogWrite(r, 255);
    delay(75);
    analogWrite(r, 0);
    delay(75);
    analogWrite(r, 255);
    delay(75);
    analogWrite(r, 0);
    delay(500);
    analogWrite(b, 255);
    delay(75);
    analogWrite(b, 0);
    delay(75);
    analogWrite(b, 255);
    delay(75);
    analogWrite(b, 0);
    delay(75);
    analogWrite(b, 255);
    delay(75);
    analogWrite(b, 0);
    delay(500);
}

void yellowLED(int r, int g, int b) {
    analogWrite(r, 255);
    analogWrite(g, 255);
    delay(1000);
    analogWrite(r, 0);
    analogWrite(g, 0);

}
void redLED(int r, int g, int b) {
    analogWrite(r, 255);
    delay(1000);
    analogWrite(r, 0);
}