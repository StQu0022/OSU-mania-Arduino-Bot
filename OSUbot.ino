const int led = 13;
#include <Keyboard.h>

//millis vars
const unsigned long inputL= 105;
const unsigned long inputD= 110;
const unsigned long inputU= 115;
const unsigned long inputR= 100;
unsigned long prevTL=0;
unsigned long prevTD=0;
unsigned long prevTU=0;
unsigned long prevTR=0;

unsigned long pressStartR = 0;
unsigned long pressStartU = 0;
unsigned long pressStartD = 0;
unsigned long pressStartL = 0;

unsigned long sliderDuration = 100; // Adjust this for slider hold time (in milliseconds)


//Random color gen
int RC= random(125, 255);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("\n");
  Serial.println("/////////////////////");
  Serial.println("DEVICE ON");
  Serial.println("/////////////////////");

  pinMode(led,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(7,OUTPUT);
  
  pinMode(8, INPUT);

  for(int i=0;i<=3;i++){
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }
  //read lef to rihght on mcirocontroller
  pinMode(A0, INPUT); //4 Blue led
  pinMode(A1, INPUT); //3 yelow 
  pinMode(A2, INPUT); //2 green
  pinMode(A3, INPUT); //1 red
  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  float valueR = analogRead(A0);
  float valueU = analogRead(A1);
  float valueD = analogRead(A2);
  float valueL = analogRead(A3);
  
  //white led + purple RGB to check for light signal
  if (valueR+valueU+valueD+valueL>=15){
    
    digitalWrite(7, HIGH);
    
  }
  else
    {digitalWrite(7, LOW);
      analogWrite(9, 255);
      analogWrite(10, 0);
      analogWrite(11, 255);
  }

  const int buttonPin = 8;  // Pin connected to the button

  int reading = digitalRead(buttonPin); // Read the button state


  if (reading == 0){
    //Serial.println("on");
    //RGBcheck();
    //sensorCheck();
    //inputLogicMillis();
    
    inputLogicST2();
  }
  if (reading == 1){
    Serial.println("off");
    
    delay(500);
  }
  
 
}
  
  

void sensorCheck(){
  float valueR = analogRead(A0);
  float valueU = analogRead(A1);
  float valueD = analogRead(A2);
  float valueL = analogRead(A3);

  int delaySensors= 100;

  if (valueL>=1){
    Serial.print("L val: ");
    Serial.print(valueL);
    Serial.print("  ");
    digitalWrite(2, HIGH);
    analogWrite(9, 127);
    analogWrite(10, 0);
    analogWrite(11, 0);
    
    }
  else{
    digitalWrite(2, LOW);
    RGBoff();
    }


  if (valueD>=1){  
    Serial.print("D val: ");
    Serial.print(valueD);
    Serial.print("  ");
    digitalWrite(3, HIGH);
    analogWrite(9, 127);
    analogWrite(10, 0);
    analogWrite(11, 0);
  }  
  else{
    digitalWrite(3, LOW);
    RGBoff();
  }

  if (valueU>=3){
    Serial.print("U val: ");
    Serial.print(valueU);
    Serial.print("  ");
    digitalWrite(4, HIGH);
    analogWrite(9, 0);
    analogWrite(10, 0);
    analogWrite(11, 127);

  
  }
  else{
      digitalWrite(4, LOW);
      RGBoff();
  }

  if (valueR>=1){
    Serial.print("R val: ");
    Serial.print(valueR);
    Serial.print("  \n");
    digitalWrite(5, HIGH);
    analogWrite(9, 0);
    analogWrite(10, 0);
    analogWrite(11, 127);
    
  }
  else{
    digitalWrite(5, LOW);
    RGBoff();
  } 
  delay(delaySensors);

}
void inputLogicMillis(){
  float valueR = analogRead(A0);
  float valueU = analogRead(A1);
  float valueD = analogRead(A2);
  float valueL = analogRead(A3);

  float thresholdR = 20; //Blue
  float thresholdU = 14.5; //yellow
  float thresholdD = 19.5; //green
  float thresholdL = 23; //red

  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);

  unsigned long currentT = millis();
  int delayt = 30;
  if (valueR>=thresholdR){
    if ( currentT - prevTR>= inputR){ 
      
      Serial.println(" R Hit ");
      //Serial.print(valueR);
      //Serial.println("I");
      analogWrite(9, RC);
      analogWrite(10, 0);
      analogWrite(11, 0);
      digitalWrite(5, HIGH);

      delay(delayt);
      //digitalWrite(5, LOW);
      //RGBoff();
      prevTR = currentT;
      }

    }

  if (valueU>=thresholdU){
    if ( currentT - prevTU>= inputU){ 
      Serial.println(" Up Hit ");
      //Serial.print(valueU);
      //Serial.println("U");
      analogWrite(9, RC);
      analogWrite(10, RC);
      analogWrite(11, RC);
      digitalWrite(4, HIGH);
      delay(delayt);
      //digitalWrite(4, LOW);
      //RGBoff();
      prevTU = currentT;
    }
  }

  if (valueD>=thresholdD){
    if ( currentT - prevTD>= inputD){ 
      Serial.println(" D Hit ");
      //Serial.print(valueD);
      //Serial.println("Y");
      analogWrite(9, 0);
      analogWrite(10, RC);
      analogWrite(11, 0);
      digitalWrite(3, HIGH);
      delay(delayt);
      //digitalWrite(3, LOW);
      //RGBoff();
      prevTD = currentT;
      }
    }

  if (valueL>=thresholdL){
    
    if ( currentT - prevTL>= inputL){ 
      //Serial.println(valueL);
      Serial.println(" L Hit ");
      //Serial.print(valueL);
      //Serial.println("T");
      analogWrite(9, 0);
      analogWrite(10, 0);
      analogWrite(11, RC);
      digitalWrite(2, HIGH);
      delay(delayt);
      //digitalWrite(2, LOW);
      //RGBoff();
      prevTL = currentT;
      }
  }
}

void inputLogicST() {
  Keyboard.begin(KeyboardLayout_en_US);
  float valueR = analogRead(A0);
  float valueU = analogRead(A1);
  float valueD = analogRead(A2);
  float valueL = analogRead(A3);
  int reldel = 0;
  // Threshold values for sensors
  float thresholdR = 13; // Blue
  float thresholdU = 11; // Yellow
  float thresholdD = 13; // Green
  float thresholdL = 13; // Red

  // Static state variables to track whether each input is active
  static bool isRActive = false;
  static bool isUActive = false;
  static bool isDActive = false;
  static bool isLActive = false;

  // Right sensor logic
  if (valueR >= thresholdR) {
    if (!isRActive) { // Only send "R Hit" once
      Serial.println("Right");
      digitalWrite(5, HIGH);
      analogWrite(9, RC);
      analogWrite(10, RC);
      analogWrite(11, 0);
      Keyboard.press(0xD7);
      isRActive = true;
    }
  } else {
    if (isRActive) { // Only send "R Released" once
      delay(reldel);
      Serial.println("RR");
      digitalWrite(5, LOW);
      Keyboard.release(0xD7);
      isRActive = false;
    }
  }

  // Up sensor logic
  if (valueU >= thresholdU) {
    if (!isUActive) {
      Serial.println("Up");
      digitalWrite(4, HIGH);
      analogWrite(9, 0);
      analogWrite(10, RC);
      analogWrite(11, RC);
      Keyboard.press(0xDA);
      isUActive = true;
    }
  } else {
    if (isUActive) {
      delay(reldel);
      Serial.println("UR");
      digitalWrite(4, LOW);
      Keyboard.release(0xDA);
      isUActive = false;
    }
  }

  // Down sensor logic
  if (valueD >= thresholdD) {
    if (!isDActive) {
      
      Serial.println("Down");
      digitalWrite(3, HIGH);
      analogWrite(9, RC);
      analogWrite(10, 0);
      analogWrite(11, RC);
      Keyboard.press(0xD9);
      isDActive = true;
    }
  } else {
    if (isDActive) {
      delay(reldel);
      Serial.println("DR");
      digitalWrite(3, LOW);
      Keyboard.release(0xD9);
      isDActive = false;
    }
  }

  // Left sensor logic
  if (valueL >= thresholdL) {
    if (!isLActive) {
      Serial.println("Left");
      digitalWrite(2, HIGH);
      analogWrite(9, RC);
      analogWrite(10, random(0,125));
      analogWrite(11, 0);
      Keyboard.press(0xD8);
      isLActive = true;
    }
  } else {
    if (isLActive) {
      delay(reldel);
      Serial.println("LR");
      digitalWrite(2, LOW);
      Keyboard.release(0xD8);
      isLActive = false;
    }
  }
}

void inputLogicST2() {
  // Initialize the keyboard
  Keyboard.begin(KeyboardLayout_en_US);

  // Read analog sensor values
  float valueR = analogRead(A0);
  float valueU = analogRead(A1);
  float valueD = analogRead(A2);
  float valueL = analogRead(A3);

  // Threshold values for sensors
  float thresholdR = 13; // Blue
  float thresholdU = 15; // Yellow
  float thresholdD = 14; // Green
  float thresholdL = 15; // Red
  float hysteresis = 2.0; // To stabilize sensor inputs

  // Slider duration in milliseco50nds
  unsigned long sliderDuration = 0;

  // Static state variables for tracking
  static bool isRActive = false;
  static bool isUActive = false;
  static bool isDActive = false;
  static bool isLActive = false;

  // Time tracking for how long a key is pressed
  static unsigned long pressStartR = 0;
  static unsigned long pressStartU = 0;
  static unsigned long pressStartD = 0;
  static unsigned long pressStartL = 0;

  // Right sensor logic
  if (valueR >= thresholdR + hysteresis) { // Detect key press
    if (!isRActive) {
      Serial.println("Right Pressed");
      digitalWrite(5, HIGH);
      analogWrite(9, 255); // Adjust RC as needed
      analogWrite(10, 255);
      analogWrite(11, 0);
      Keyboard.press(0xD7);
      isRActive = true;
      pressStartR = millis(); // Record press start time
    }
  } else if (valueR < thresholdR - hysteresis) { // Detect key release
    if (isRActive && (millis() - pressStartR >= sliderDuration)) {
      Serial.println("Right Released");
      digitalWrite(5, LOW);
      Keyboard.release(0xD7);
      isRActive = false;
    }
  }

  // Up sensor logic
  if (valueU >= thresholdU + hysteresis) {
    if (!isUActive) {
      Serial.println("Up Pressed");
      digitalWrite(4, HIGH);
      analogWrite(9, 0);
      analogWrite(10, 255); // Adjust RC as needed
      analogWrite(11, 255);
      Keyboard.press(0xDA);
      isUActive = true;
      pressStartU = millis();
    }
  } else if (valueU < thresholdU - hysteresis) {
    if (isUActive && (millis() - pressStartU >= sliderDuration)) {
      Serial.println("Up Released");
      digitalWrite(4, LOW);
      Keyboard.release(0xDA);
      isUActive = false;
    }
  }

  // Down sensor logic
  if (valueD >= thresholdD + hysteresis) {
    if (!isDActive) {
      Serial.println("Down Pressed");
      digitalWrite(3, HIGH);
      analogWrite(9, 255);
      analogWrite(10, 0);
      analogWrite(11, 255); // Adjust RC as needed
      Keyboard.press(0xD9);
      isDActive = true;
      pressStartD = millis();
    }
  } else if (valueD < thresholdD - hysteresis) {
    if (isDActive && (millis() - pressStartD >= sliderDuration)) {
      Serial.println("Down Released");
      digitalWrite(3, LOW);
      Keyboard.release(0xD9);
      isDActive = false;
    }
  }

  // Left sensor logic
  if (valueL >= thresholdL + hysteresis) {
    if (!isLActive) {
      Serial.println("Left Pressed");
      digitalWrite(2, HIGH);
      analogWrite(9, 255); // Adjust RC as needed
      analogWrite(10, random(0, 125));
      analogWrite(11, 0);
      Keyboard.press(0xD8);
      isLActive = true;
      pressStartL = millis();
    }
  } else if (valueL < thresholdL - hysteresis) {
    if (isLActive && (millis() - pressStartL >= sliderDuration)) {
      Serial.println("Left Released");
      digitalWrite(2, LOW);
      Keyboard.release(0xD8);
      isLActive = false;
    }
  }

  /*/ Debugging information for fine-tuning thresholds
  Serial.print("Values - R: "); Serial.print(valueR);
  Serial.print(" U: "); Serial.print(valueU);
  Serial.print(" D: "); Serial.print(valueD);
  Serial.print(" L: "); Serial.println(valueL);*/
}

void RGBoff(){
  analogWrite(9, 0);
  analogWrite(10, 0);
  analogWrite(11, 0);
}
void RGBcheck(){
  static int pin = 9;

  analogWrite(pin, 255);
  Serial.println(pin);
  delay(1000);
  analogWrite(pin, 0);
  Serial.println(pin);
  pin++;
  if (pin>=12){
    pin=9;
  }

}
