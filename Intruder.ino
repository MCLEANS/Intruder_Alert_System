#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include<EEPROM.h>
#include "ultrasonic.h"

#define buzzerpin 9
const byte ROWS = 4; 
const byte COLS = 3; 
bool armed=false;

char pass[3] = {};
String passH="";

char initial_password[4];
char new_password[4];

char TypedPassword[4];
char key_pressed = 0;



char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; 
byte colPins[COLS] = {6, 7, 8}; 

Ultrasonic ultrasonic(10,11);

LiquidCrystal_I2C lcd(0x3f, 16, 2);
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

const int analogInPin = A0;  // Analog input pin that the receiver is attached to
long int sensorValue = 0;        // value read from the receiver

void setup() {
  ultrasonic.initialize();
  //initialpassword();
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
   lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("ALARM SYSTEM");
  //initialize the indicator LED:
  pinMode(buzzerpin,OUTPUT);
  pinMode(13, OUTPUT);
  delay(2000);
  lcd.clear();
}

void loop() {
    sensorValue = ultrasonic.getDistance();
         lcd.print("ALARM SYSTEM");
         if(armed){
          lcd.setCursor(0,1);
          lcd.print("SYSTEM ARMED");
          
         }
        
 

  // print the results to the serial monitor:
  Serial.print("\nsensor = ");
  Serial.print(sensorValue);

  //the threshold found fron analog In Out program was when object is detected, the sensor value is below 100
  //set the threshold whihc you get
  //the threshold varies for different sets of emitter-receiver pairs
  if(sensorValue <14  ){ //checks if object is there or not
    digitalWrite(buzzerpin, HIGH);
    digitalWrite(13, HIGH);
    Serial.print("\nObject Detected");
    armed=true;
  
    }
  else{
   digitalWrite(13, LOW);
    Serial.print("\nNo object in Front");
    }
   //--------------------------------------------

  char customKey = customKeypad.getKey();
  // //---------------------------------------


    if (customKey){
     Serial.println(customKey);
    if (customKey == '0') {
      lcd.clear();
     lcd.print("ENTER PASSWORD");
      Serial.println("ENTER PASSWORD");
      int k = 0;
      while (k < 4) {
        customKey = customKeypad.getKey();
        if (customKey) {
          
          lcd.setCursor(5 + k, 1);
          lcd.print("*");
          Serial.println(customKey);
         pass[k] = customKey;
          k++;
        }
      }
      //-----------------------------------
      for (int j = 0; j < 4; j++) initial_password[j] = EEPROM.read(j);
  if (strncmp(pass, initial_password, 4)) {
    lcd.clear();
    lcd.print("Wrong password");
    lcd.setCursor(3, 1);
    lcd.print("Try Again!");
    delay(1000);
    lcd.clear();

  }
      //----------------------------------
   else{
        digitalWrite(buzzerpin,LOW);
        
        Serial.println("DISARMED");
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("SYSTEM DISARMED");
        armed=false;
        delay(3000);
      }
      
   
    
  }
  
  }
  if(customKey=='#') change();
  //--------------------------------------------------

   
   //-------------------------------------------------
  delay(200);
  lcd.clear();
}

void change() {
  lcd.clear();
  int j = 0;
  lcd.print("Current Password");
  lcd.setCursor(5, 1);
  while (j <= 3) {
    char key = customKeypad.getKey();
    if (key) {
      if (key == '*') {
        if (j > 0) {
          j--;
          lcd.setCursor(5 + j, 1);
          lcd.print(" ");
          lcd.setCursor(5 + j, 1);
        }
        else {}
      }
      else if (key == '#') {
        lcd.clear();
        lcd.print("Current password");
        lcd.setCursor(5, 1);
        j = 0;
      }
      else {
        TypedPassword[j++] = key;
        lcd.print('*');
      }
    }
    key = 0;
  }
  j = 0;
  delay(100);
  for (j = 0; j < 4; j++) initial_password[j] = EEPROM.read(j);
  if ((strncmp(TypedPassword, initial_password, 4))) {
    lcd.clear();
    lcd.print("Wrong Password");
    lcd.setCursor(3, 1);
    lcd.print("Try Again");
    delay(1000);
  }
  else {
    j = 0;
    lcd.clear();
    lcd.print("New Password:");
    lcd.setCursor(5, 1);
    while (j < 4) {
      char key = customKeypad.getKey();
      if (key) {
        if (key == '*') {
          if (j > 0) {
            j--;
            lcd.setCursor(5 + j, 1);
            lcd.print(" ");
            lcd.setCursor(5 + j, 1);
          }
          else {}
        }
        else if (key == '#') {
          lcd.clear();
          lcd.print("New Password:");
          lcd.setCursor(5, 1);
          j = 0;
        }
        else {
          initial_password[j] = key;
          lcd.print('*');
          EEPROM.write(j, key);
          j++;
        }
      }
      key = 0;
    }
    lcd.clear();
    lcd.print("Password Changed");
    lcd.setCursor(2, 1);
    lcd.print("Successfully");
    delay(2000);
  }
  key_pressed = 0;
  lcd.clear();
}
void initialpassword() { //setting initial password
  for (int j = 0; j < 4; j++)
    EEPROM.write(j, 48); //address ,value to b stored in byte location
  for (int j = 0; j < 4; j++)
    initial_password[j] = EEPROM.read(j); //read from the Eeprom
}
