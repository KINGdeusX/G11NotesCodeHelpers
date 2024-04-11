/* 
--------------------------------------------

   This firmware is coded and signed by 
TNKLegacy7i0 and is the author of this repo 
   TNK_ACTA_BOT_FIRMWARE_VERSION_1.35.5

--------------------------------------------

*/

#include <Arduino.h>
#include <Wire.h>
#include <IRremote.h>
#include <emojis.h>
#include <customLights.h>

#define positive_sonic 11
#define echo 13
#define trig 12

#define positive_ir 8
#define negative_ir 9
#define infra 10

#define enable_1a2 0
#define enable_3a4 0
#define input1 0
#define input2 0
#define input3 0
#define input4 0

#define negative_led A0
#define Blue A1
#define Green A2
#define Red A3

int speed_variable = 150;
int turn_speed_variable;

int max_speed = 255;
int mid_speed = 125;
int min_speed = 10;
int no_speed = 0;

int vol_speed_increment = 10;
int treashold = 30;

void forward(int speed_variable) {
    analogWrite(enable_1a2, speed_variable);
    analogWrite(enable_3a4, speed_variable);
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    digitalWrite(input3, HIGH);
    digitalWrite(input4, LOW);
}
void backward(int speed_variable) {
    analogWrite(enable_1a2, speed_variable);
    analogWrite(enable_3a4, speed_variable);
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    digitalWrite(input3, LOW);
    digitalWrite(input4, HIGH);
}
void turn_right(int speed_variable, int turn_speed_variable) {
    analogWrite(enable_1a2, turn_speed_variable);
    analogWrite(enable_3a4, speed_variable);
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    digitalWrite(input3, HIGH);
    digitalWrite(input4, LOW);
}
void turn_left(int speed_variable, int turn_speed_variable) {
    analogWrite(enable_1a2, speed_variable);
    analogWrite(enable_3a4, turn_speed_variable);
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    digitalWrite(input3, HIGH);
    digitalWrite(input4, LOW);
}
void stop() {
    analogWrite(enable_1a2, 0);
    analogWrite(enable_3a4, 0);
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
    digitalWrite(input3, LOW);
    digitalWrite(input4, LOW);
    Serial.println("STOPED");
}

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(infra);

    lcd.init();
    lcd.backlight();

    pinMode(positive_sonic, OUTPUT);
    pinMode(positive_ir, OUTPUT);
    pinMode(negative_ir, OUTPUT);
    pinMode(negative_led, OUTPUT);

    digitalWrite(positive_sonic, HIGH);
    digitalWrite(positive_ir, HIGH);
    digitalWrite(negative_ir, LOW);
    digitalWrite(negative_led, LOW);

    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);

    pinMode(enable_1a2, OUTPUT);
    pinMode(enable_3a4, OUTPUT);
    pinMode(input1, OUTPUT);
    pinMode(input2, OUTPUT);
    pinMode(input3, OUTPUT);
    pinMode(input4, OUTPUT);
}

void loop() {
	float duration, distance; 

    digitalWrite(trig, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trig, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(trig, LOW); 

    duration = pulseIn(echo, HIGH); 
    distance = (duration * 0.0343) / 2; 

    if (distance <= treashold) {
        stop();
		lcd.clear();
		mad();
		policeLED(Red, Green, Blue);
    }
    else {
		if (IrReceiver.decode()) {
			int remoteValue = IrReceiver.decodedIRData.command;

            if (remoteValue == 7) {
                speed_variable -= vol_speed_increment;
                Serial.println("Speed decreased to " + String(speed_variable));
				lcd.clear();
				lcd.setCursor(0, 0);
				lcd.print("Speed dec " + String(speed_variable));
            }
            else if (remoteValue == 21) {
                speed_variable += vol_speed_increment;
                Serial.println("Speed increased to " + String(speed_variable));
				lcd.clear();
				lcd.setCursor(0, 0);
				lcd.print("Speed in " + String(speed_variable));
            }
            else if (remoteValue == 13) {
                turn_speed_variable -= vol_speed_increment;
                Serial.println("Turn Speed decreased to " + String(turn_speed_variable));
				lcd.clear();
				lcd.setCursor(0, 0);
				lcd.print("Turn dec " + String(turn_speed_variable));
            }
            else if (remoteValue == 25) {
                turn_speed_variable += vol_speed_increment;
                Serial.println("Turn Speed increased to " + String(turn_speed_variable));
				lcd.clear();
				lcd.setCursor(0, 0);
				lcd.print("Turn in " + String(turn_speed_variable));
            }

            else if (remoteValue == 24) {
                forward(speed_variable);
                Serial.println("FORWARDING with SPEED " + String(speed_variable));
				lcd.clear();
				happy();
				yellowLED(Red, Green, Blue);
            }
            else if (remoteValue == 82) {
                backward(speed_variable);
                Serial.println("BACWARDS with SPEED " + String(speed_variable));
				lcd.clear();
				shock();
            }
            else if (remoteValue == 8) {
                turn_left(speed_variable,turn_speed_variable);
                Serial.println("TURNING LEFT with SPEED " + String(speed_variable));
				lcd.clear();
				nargesFACES();
            }
            else if (remoteValue == 90) {
                turn_right(speed_variable,turn_speed_variable);
                Serial.println("TURNING RIGHT with SPEED " + String(speed_variable));
				lcd.clear();
				nargesFACES();
            }
            else {
                stop();
                Serial.println("Unasigned Key Value Stoping (" + String(remoteValue) + ")");
				lcd.clear();
				sad();
				redLED(Red, Green, Blue);
            }
			// Serial.println(remoteValue);
			IrReceiver.resume();
		}
    }
    delay(100);
}