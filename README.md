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

<hr>

### Section 2: Conditions 

Conditions are ment to compare multitple values and returns 1 meaning true or false meaning 0.
