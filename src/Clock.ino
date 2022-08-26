#include <TM1637.h>

/* SETUP VARIABLES */

//GPIO Setup:
int CLK = A5;
int DIO = A4;
int POT = A6;
int BUT = 3;
int ENA = 4;
int PHA = 5;

//Object Setup:
TM1637 tm(CLK, DIO);

//Time Setup:
int counts = 0;
int timer = 0;

/* SETUP METHODS */

//Init Method:
void setup() {
  //Setup:
  tm.init();
  tm.set(2);

  //Motor Setup:
  pinMode(ENA, INPUT);
  pinMode(PHA, OUTPUT);
}

//Loop Method:
void loop() {
  //Sets the Timer:
  setTimer();
  
  //Checks the Case
  if (digitalRead(BUT) == HIGH) {
    //Runs Clock:
    runClock();
  }
}

/* TIMER METHODS */

//Set Timer Method:
void setTimer() {
  //Gets the Value:
  float value = analogRead(POT);
  timer = (int)((1439.0 / 1023.0) * value);
  displayNumber(timer);
}

//Run Clock Method:
void runClock() {
  //Loops:
  while (counts < timer) {
    //Counts Down:
    delay(1000);
    counts++;
  }

  //Vibrates:
  vibrate();
  delay(5000);
  stopVibrate();

  //Resets:
  counts = 0;
  timer = 0;
}

/* DISPLAY METHODS */

//Display Time Method:
void displayTime() {
  //Sets the Display:
  counts++;
  int minutes = counts/60;
  tm.display(3, minutes % 10);
  tm.display(2, minutes / 10 % 10);
  tm.display(1, minutes / 100 % 10);
  tm.display(0, minutes / 1000 % 10);
}

//Display Number Method;
void displayNumber(int num) {
  //Displays Number:
  tm.display(3, num % 10);
  tm.display(2, num / 10 % 10);
  tm.display(1, num / 100 % 10);
  tm.display(0, num / 1000 % 10);
}

/* VIBRATION METHODS */

//Vibrate Method:
void vibrate() {
  //Runs the Motor:
  digitalWrite(ENA, HIGH);
  digitalWrite(PHA, HIGH);
}

//Stop Vibrate Method:
void stopVibrate() {
  //Stops the Motor:
  digitalWrite(ENA, LOW);
  digitalWrite(PHA, LOW);
}