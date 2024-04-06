//#include <Arduino.h>  
#include <IRremote.h>  

#define trig 13 
#define echo 12 
#define infra 11 

#define enable_1a2 9 
#define enable_3a4 10 

#define input1 6 
#define input2 5 
#define input3 7 
#define input4 8 

void forward() { 
    analogWrite(enable_1a2, 150);
    analogWrite(enable_3a4, 150);
    digitalWrite(input1, LOW); 
    digitalWrite(input2, HIGH);
    digitalWrite(input3, HIGH);
    digitalWrite(input4, LOW); 
    Serial.println("FORWARDING");
}
void backward() { 
    analogWrite(enable_1a2, 150);
    analogWrite(enable_3a4, 150);
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW); 
    digitalWrite(input3, LOW); 
    digitalWrite(input4, HIGH); 
    Serial.println("BACKING UP");
}
void turn_right() { 
    analogWrite(enable_1a2, 0); 
    analogWrite(enable_3a4, 150);
    digitalWrite(input1, LOW); 
    digitalWrite(input2, HIGH); 
    digitalWrite(input3, HIGH); 
    digitalWrite(input4, LOW); 
    Serial.println("TURNING RIGHT");
}
void turn_left() { 
    analogWrite(enable_1a2, 150); 
    analogWrite(enable_3a4, 0); 
    digitalWrite(input1, LOW); 
    digitalWrite(input2, HIGH); 
    digitalWrite(input3, HIGH); 
    digitalWrite(input4, LOW); 
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
    IrReceiver.begin(infra, true); 

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

    Serial.println(distance);
    
    IrReceiver.decode();
    int remoteValue = IrReceiver.decodedIRData.command;
    Serial.println(remoteValue);
    IrReceiver.resume();

    forward();

    delay(100);
}