/* 
=====================================================
|                 WIRING PARAMETERS                 |
=====================================================
| MODULE                |       ARDUINO             |
+-----------------------+---------------------------+
|       Ultrasonic      |                           |
+-----------------------+---------------------------+
|       Vcc             |       +5v                 |
|       Trig            |       13                  |
|       Echo            |       12                  |
|       GND             |       GND                 |
+-----------------------+---------------------------+
|       IR Receiver     |                           |
+-----------------------+---------------------------+
|       Out             |       11                  |
|       GND             |       GND                 |
|       Vcc             |       +5v                 |
+-----------------------+---------------------------+
|       L298N/L293D     |                           |
+-----------------------+---------------------------+
|       POWER1          |       +5v                 |
|       GND             |       GND                 |
|       EnA/En1&2       |       10                  |
|       EnB/En3&4       |       9                   |
|       IN1             |       8                   |
|       IN2             |       7                   |
|       IN3             |       6                   |
|       IN4             |       5                   |
|       POWER2          |       BAT+ ~ +6v to +12v  |
+-----------------------+---------------------------+
*/

#include <Arduino.h>  
#include <IRremote.h>  

#define trig 13 
#define echo 12 
#define infra 11 

#define enable_1a2 10 
#define enable_3a4 9 

#define input1 8 
#define input2 7 
#define input3 6 
#define input4 5 

int forward_action = 0;
int backward_action = 0;
int turn_left_action = 0;
int turn_right_action = 0;
int stop_action = 0;

int distance_treashold = 40;
int defined_speed = 150;

void forward() { 
    analogWrite(enable_1a2, defined_speed);
    analogWrite(enable_3a4, defined_speed);
    digitalWrite(input1, LOW); 
    digitalWrite(input2, HIGH);
    digitalWrite(input3, HIGH);
    digitalWrite(input4, LOW); 
    Serial.println("FORWARDING");
}
void backward() { 
    analogWrite(enable_1a2, defined_speed);
    analogWrite(enable_3a4, defined_speed);
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW); 
    digitalWrite(input3, LOW); 
    digitalWrite(input4, HIGH); 
    Serial.println("BACKING UP");
}
void turn_right() { 
    analogWrite(enable_1a2, defined_speed); 
    analogWrite(enable_3a4, defined_speed);
    digitalWrite(input1, HIGH); 
    digitalWrite(input2, LOW); 
    digitalWrite(input3, HIGH); 
    digitalWrite(input4, LOW); 
    Serial.println("TURNING RIGHT");
}
void turn_left() { 
    analogWrite(enable_1a2, defined_speed); 
    analogWrite(enable_3a4, defined_speed); 
    digitalWrite(input1, LOW); 
    digitalWrite(input2, HIGH); 
    digitalWrite(input3, LOW); 
    digitalWrite(input4, HIGH); 
    Serial.println("TURNING LEFT");
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

    // Serial.println(distance);

    if (distance > 40) {
        if (IrReceiver.decode()) {
            int remoteValue = IrReceiver.decodedIRData.command;
            if (remoteValue == forward_action) {
                forward();
            }
            else if (remoteValue == backward_action) {
                backward();
            }
            else if (remoteValue == turn_left_action) {
                turn_left();
            }
            else if (remoteValue == turn_right_action) {
                turn_right();
            }
            else if (remoteValue == stop_action) {
                stop();
            }

            Serial.println(remoteValue);
            IrReceiver.resume();
        }
    }
    else {
        stop();
        delay(1000);
        backward();
        delay(1000);
        turn_left();
    }

    delay(100);
}