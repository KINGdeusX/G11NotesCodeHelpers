/* 
--------------------------------------------

   This firmware is coded and signed by 
TNKLegacy7i0 and is the author of this repo 
   TNK_ACTA_BOT_FIRMWARE_VERSION_2.20.1

--------------------------------------------

*/

// System Declarations
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

#define enable_1a2 6
#define enable_3a4 5
#define input1 7
#define input2 4
#define input3 2
#define input4 3

#define negative_led A0
#define Blue A1
#define Green A2
#define Red A3

// Sub-system declarations
int hash = 312;

int speed_variable = 150;
int turn_speed_variable;

int max_speed = 255;
int mid_speed = 125;
int min_speed = 10;
int no_speed = 0;

int vol_speed_increment = 10;
int treashold = 30;

int assigned_forwards = 24;
int assigned_backwards = 82;
int assigned_turn_left = 8;
int assigned_turn_right = 90;
int assigned_stop = 28;

int assigned_add_speed = 21;
int assigned_reduce_speed = 7;
int assigned_add_turn_speed = 25; 
int assigned_reduce_turn_speed = 13;
int assigned_add_dist_tol = 71;
int assigned_reduce_dist_tol = 69;

bool reverse_wire_prot_p1 = LOW;
bool reverse_wire_prot_p2 = HIGH;

// Custom Fuctions
void forward(int speed_variable)
{
    analogWrite(enable_1a2, speed_variable);
    analogWrite(enable_3a4, speed_variable);
    digitalWrite(input1, reverse_wire_prot_p1);
    digitalWrite(input2, reverse_wire_prot_p2);
    digitalWrite(input3, reverse_wire_prot_p2);
    digitalWrite(input4, reverse_wire_prot_p1);
}
void backward(int speed_variable)
{
    analogWrite(enable_1a2, speed_variable);
    analogWrite(enable_3a4, speed_variable);
    digitalWrite(input1, reverse_wire_prot_p2);
    digitalWrite(input2, reverse_wire_prot_p1);
    digitalWrite(input3, reverse_wire_prot_p1);
    digitalWrite(input4, reverse_wire_prot_p2);
}
void turn_right(int speed_variable, int turn_speed_variable)
{
    analogWrite(enable_1a2, turn_speed_variable);
    analogWrite(enable_3a4, speed_variable);
    digitalWrite(input1, reverse_wire_prot_p1);
    digitalWrite(input2, reverse_wire_prot_p2);
    digitalWrite(input3, reverse_wire_prot_p2);
    digitalWrite(input4, reverse_wire_prot_p1);
}
void turn_left(int speed_variable, int turn_speed_variable)
{
    analogWrite(enable_1a2, speed_variable);
    analogWrite(enable_3a4, turn_speed_variable);
    digitalWrite(input1, reverse_wire_prot_p1);
    digitalWrite(input2, reverse_wire_prot_p2);
    digitalWrite(input3, reverse_wire_prot_p2);
    digitalWrite(input4, reverse_wire_prot_p1);
}
void stop()
{
    analogWrite(enable_1a2, 0);
    analogWrite(enable_3a4, 0);
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
    digitalWrite(input3, LOW);
    digitalWrite(input4, LOW);
    Serial.println("STOPED");
}

void setup()
{
    Serial.begin(115200);
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

void loop()
{
    float duration, distance;

    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    duration = pulseIn(echo, HIGH);
    distance = (duration * 0.0343) / 2;

    if (distance <= treashold)
    {
        lcd.clear();

        //AUTO MANUVER
        stop();
        delay(500);
        turn_left(speed_variable, turn_speed_variable);
        delay(500);
        stop();

        mad();
        policeLED(Red, Green, Blue);
    }
    else
    {
        if (Serial.available()) {
            char serial_message(Serial.read());
            String decoded_message = String(serial_message);

            if (decoded_message == "F") {
                forward(speed_variable);
                lcd.clear();
                happy();
                greenLED(Red, Green, Blue);
            }
            else if (decoded_message == "B") {
                backward(speed_variable);
                lcd.clear();
                shock();
                purpleLED(Red, Green, Blue);
            }
            else if (decoded_message == "L") {
                turn_left(speed_variable, turn_speed_variable);
                lcd.clear();
                nargesFACES();
                blueLED(Red, Green, Blue);
            }
            else if (decoded_message == "R") {
                turn_right(speed_variable, turn_speed_variable);
                lcd.clear();
                nargesFACES();
                blueLED(Red, Green, Blue);
            }
        }
        else if (IrReceiver.decode())
        {
            int remoteValue = IrReceiver.decodedIRData.command + hash;

            if (remoteValue == assigned_reduce_speed + hash)
            {
                speed_variable -= vol_speed_increment;
                Serial.println("Speed decreased to " + String(speed_variable));
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Speed - " + String(speed_variable));
            }
            else if (remoteValue == assigned_add_speed + hash)
            {
                speed_variable += vol_speed_increment;
                Serial.println("Speed increased to " + String(speed_variable));
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Speed + " + String(speed_variable));
            }
            else if (remoteValue == assigned_reduce_turn_speed + hash)
            {
                turn_speed_variable -= vol_speed_increment;
                Serial.println("Turn Speed decreased to " + String(turn_speed_variable));
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Turn - " + String(turn_speed_variable));
            }
            else if (remoteValue == assigned_add_turn_speed + hash)
            {
                turn_speed_variable += vol_speed_increment;
                Serial.println("Turn Speed increased to " + String(turn_speed_variable));
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Turn + " + String(turn_speed_variable));
            }
            else if (remoteValue == assigned_forwards + hash)
            {
                forward(speed_variable);
                Serial.println("FORWARDING with SPEED " + String(speed_variable));
                lcd.clear();
                happy();
                greenLED(Red, Green, Blue);
            }
            else if (remoteValue == assigned_backwards + hash)
            {
                backward(speed_variable);
                Serial.println("BACWARDS with SPEED " + String(speed_variable));
                lcd.clear();
                shock();
                purpleLED(Red, Green, Blue);
            }
            else if (remoteValue == assigned_turn_left + hash)
            {
                turn_left(speed_variable, turn_speed_variable);
                Serial.println("TURNING LEFT with SPEED " + String(speed_variable));
                lcd.clear();
                nargesFACES();
                blueLED(Red, Green, Blue);
            }
            else if (remoteValue == assigned_turn_right + hash)
            {
                turn_right(speed_variable, turn_speed_variable);
                Serial.println("TURNING RIGHT with SPEED " + String(speed_variable));
                lcd.clear();
                nargesFACES();
                blueLED(Red, Green, Blue);
            }
            else if (remoteValue == assigned_stop + hash) 
            {
                stop();
                lcd.clear();
                sad();
                redLED(Red, Green, Blue);
            }
            else if (remoteValue == assigned_add_dist_tol + hash)
            {
                // increase dist 1
                treashold += vol_speed_increment;
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Dist Tol + " + String(treashold) + "cm");
                delay(700);
            }
            else if (remoteValue == assigned_reduce_dist_tol + hash)
            {
                // decrease dist tol
                treashold -= vol_speed_increment;
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Dist Tol - " + String(treashold) + "cm");
                delay(700);
            }
            else
            {
                Serial.println("Unasigned Key Value Stoping (" + String(remoteValue) + ")");
                lcd.clear();
                lcd.write(remoteValue);
            }
            // Serial.println(remoteValue);
            IrReceiver.resume();
        }
    }
    delay(100);
}