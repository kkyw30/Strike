// C++ code

#include <Wire.h>

// define variables for the buttons (based on which pin it's connected to)
const int LEDHeelStrike = 13;
const int LEDFrontStrike = 12;
const int LEDMidStrike = 4;
const int BUTTONHeelStrike = 7;
const int BUTTONFrontStrike = 8;
const int BUTTONReset = 2;

int valButtonHeelStrike;
int valButtonFrontStrike;
int valButtonReset;

// initialize values to 0
int frontFootStrike = 0;
int heelStrike = 0;
int healthyStrike = 0;

float startMillis1 = 0.0;
float startMillis2 = 0.0;
float endMillis1 = 0.0;
float endMillis2 = 0.0;
unsigned long int state = 0;
//float currentMillis1 = 0.0;
//float currentMillis2 = 0.0;

int old_valButtonHeelStrike = LOW;
int old_valButtonFrontStrike = LOW;

float timeDifference = 0.0;
//float timeDifferences[1000];
unsigned long startMillis;


void setup()
{
  pinMode(LEDHeelStrike, OUTPUT);
  pinMode(LEDFrontStrike, OUTPUT);
  pinMode(LEDMidStrike, OUTPUT);
  pinMode(BUTTONHeelStrike, INPUT);
  pinMode(BUTTONFrontStrike, INPUT);
  pinMode(BUTTONReset, INPUT);
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onRequest(requestEvent);

  startMillis = millis(); // initial start time
  
}

// continously reads button data from the two pushbuttons
void loop()
{
  valButtonHeelStrike = digitalRead(BUTTONHeelStrike);
  valButtonFrontStrike = digitalRead(BUTTONFrontStrike);
  valButtonReset = digitalRead(BUTTONReset);
  
  // prints to Serial monitor
  Serial.println(state);

  // read in button values to decide serial monitor output and new button values
  if (valButtonHeelStrike == HIGH && old_valButtonHeelStrike == LOW) {
      startMillis1 = millis();
      state = 1 - state;
      Serial.println(state);
      Serial.println(startMillis1);
      old_valButtonHeelStrike = HIGH;
      old_valButtonFrontStrike = LOW;
   
  } 
  
  if (valButtonFrontStrike == HIGH && old_valButtonFrontStrike == LOW) {
  //  if (valButtonFrontStrike == LOW) {
    
    startMillis2 = millis();
    state = 1 - state;
    Serial.println(state);
    Serial.println(startMillis2);
    old_valButtonFrontStrike = HIGH;
    old_valButtonHeelStrike = LOW;
  } 
  Serial.println(state);
 
  if (valButtonReset == HIGH) {
    state = 0;
    old_valButtonHeelStrike = LOW;
  old_valButtonFrontStrike = LOW;
  }
  
  if (state == 0){
    // find difference and add value to array
    timeDifference = startMillis1 - startMillis2;
    Serial.println(startMillis1);
    Serial.println(startMillis2);
    Serial.println(timeDifference);
    if (timeDifference < 1000.0 && timeDifference > -1000.0 && timeDifference != 0.0) {
    Serial.println("Midfoot Strike");
    digitalWrite(LEDMidStrike, HIGH);
    digitalWrite(LEDFrontStrike, LOW);
    digitalWrite(LEDHeelStrike, LOW);
    
  } 
  // if statements help determine what kind of foot strike you just used
  //if (state == 1 && timeDifference > 1000) {
  if (timeDifference > 1000) {
    Serial.println("Front foot Strike");
    digitalWrite(LEDFrontStrike, HIGH);
    digitalWrite(LEDMidStrike, LOW);
    digitalWrite(LEDHeelStrike, LOW);
  } 
  //else if (state == 0) {
  else if (timeDifference < -1000) {
    Serial.println("Heel Strike");
    digitalWrite(LEDHeelStrike, HIGH);
    digitalWrite(LEDMidStrike, LOW);
    digitalWrite(LEDFrontStrike, LOW);
  }
  }

// sends the data to Adafruit IO 
  void requestEvent() {
    
    Wire.write(state);
    Wire.write((int)timeDifference);
    Serial.println((int)timeDifference, 1);
    
  }
        
        
        
        
        
        
