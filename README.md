# G11 ROBOTICS CODE NOTES

### Section 1 : Conditional Statements
examples: conditional statements
> syntax 
>
> if (*condition*) {**do this...**} <br>
> else if (*condition*) {**do this...**} <br>
> else {**do this...**}

***Example***
```
void setup() {
    Serial.begin(9600);
}

void loop() {
    if (true) {
        Serial.println("1st condition is true");
    }
    else if (false) {
        Serial.println("2nd condition is false")
    }
    else {
        Serial.println("This is your last resort");
    }
}
```
in this example, the first condition is **true** therefore whatever code was placed in the opening and closing parenthesesa are executed.

if the statement is **false** , then it will go over all the other ***else if*** statements until it reaches the ***else*** statement.

---

### Section 2: Conditions 

Conditions are ment to compare multitple values and returns 1 meaning true or false meaning 0.

> Syntax
>
> == (*Equal-Equal* in English ***Equal to?***) <br> 
> && (*And-And* in English ***AND***)<br>
> != (*NOT Equal* Like the name implies)<br>
> || (*OR-OR* in English ***OR***)<br>
>

```
1. ( 1 == 1 ) // true
2. ( 0 == 1 ) // false

3. (false == false) // true
4. (True == true) // false
```

In the Example above, 1 returns true if both values from left and right of the "Equal-Equal" is the same.

if the values from left and right of the "Equal-Equal" are not the same then the result is false.

---

### Section 3 : Callable Functions

Callable functions or Custom Functions are used to organize code and create partitions from the other parts of your code, this helps isolate problems and create structural integrity of your code. among other things you can use callable functions to make your code easy to understand very short.

***Always Remember that the readable your code this the more likely it is for you to understand the code, and for others to understand as well.***

> syntax
>
> void name_of_my_function () { ... }
>

Example <br>
this is how you create a function
```
void my_function() {
    Serial.println("Something Here");
}

```
and this is how you call it.
```
my_function();
```

---

### Section 4 : Overwrite GPIO to GND or 5V

Overwriting the GPIO pins is possible. Been able to relocate or place the ***(+5V)*** and ***(GND)*** line in anywhere in the pins is very help full when you are trying to acheive ***ZERO-JUMPER-WIRE*** build.

Let's firts define the pins;
Example lets have the PIN 13 as your Negative (GND) and the PIN 12 as your Positive (+5V). 
```
#define POSITIVE 12
#define NEGATIVE 13
```

Next in the `void setup ()` we need to Identify its **pinMode()**
Since both of these pins are acting as a constant power source we need to set them both into OUTPUT. So that this will provide power to the device we are tryin to power, here is the example.

```
void setup() {
    pinMode(POSITIVE, OUTPUT);
    pinMode(NEGATIVE, OUTPUT);
}
```
at this point we still do not have power through them yet. To enable power to flow through them, we need to define its ***digitalWrite()*** current flow.

**ALWAYS REMEMBER THAT (GND) ALWAYS SUCKS IN ELECTRONS AND (+5V) ALWAYS GIVES OFF ELECTRONS THAT ALLOWS THE ELECTRONS TO FLOW THROUGH THE COMPONENTS AND GENERATING ACTIONS**

Finally to make the pin 12 to act like a +5V, lets set it to HIGH in the digitalWrite(); and, set the pin 13 as LOW.

Like this

```
digitalWrite(POSITIVE, HIGH);
digitalWrite(NEGTAIVE, LOW);
```
HIGH gives off electrons and LOW sucks in electrons completing the circuit in between.

---

### Section 5 : Local VS Global Variables

Local variable - is define inside any of the following;
* functions
* loops
* coditionals
* inner loops and conditionals

meaning their values are only used within the space of the constructors they placed in

Global Variables - are used in the all parts of the code. meaning the values within that variable are accessible even if you have loops within loops

Example
```
#include <Arduino.h>

int imGlobal = 10; // This variable is accessible in setup and loop

void setup() {
    int imOnlyInSetup = 11; // This is only accessible within setup
}
void loop() {
    int imOnlyInLoop = 12; // This is only accessible within loop
}
```
---
### Section 6 : Obtaining Values from Universal and Non-universial Remotes

In this example, we will explore how IrRemote library features can help you use all kinds of Infrared remotes and use it in your robots.

First things first, each remote emits a signal (Infrared) to be more specific. the light will flash according to the bits it's assigned to. 
on the other end the receiver interprets these messages and convert it to human readable text or display.

Here are some examples:
We need to import the library first. to do that just type.
```
#inlucde <IrRemote.h>
```
next we need to start the communication for our Ir Receiver that is connected to my pin number 11.
```
void setup() {
    Serial.begin(9600); //started the serial communication, allowing us to display the values
    IrReceiver.begin(11); // this will allow us to initialize our communication from the Ir Receiver.
}
```
next step is we need to have a value catcher. to do that here are some snippet of code.
```
void loop() {
    if (IrReceiver.decode()) { // STARTS LISTENING
        IrReceiver.resume(); // ALLOWS THE CODE TO MOVE FORWARD
    }
}
```
Next step will be to define the data type of the message that we'll receive.
then have a way to consistently read that data
here's what we have to do.
```
    if (IrReceiver.decode()) { // STARTS LISTENING

        auto message = IrReceiver.decodedIRData.decodedRawData; // Since we need a way to store the values, we assinged it to an auto Datatype
        String command = String(message, HEX); // This command enables us to properly catch the values consistently.

        IrReceiver.resume(); // ALLOWS THE CODE TO MOVE FORWARD
    }
```
After that you'll be able to compare values from the command variable. Since its a datatype String, you are free to use the single or double quotation marks.
```
        if (command == "bc43ff00") { // this now is your remote value.
            Serial.println("THIS BUTTON IS PRESSED");
        }
```
**Note that some remote gives off their values no problem some may or may not are harder to obtain, at this moment these are the few ways to use it.**