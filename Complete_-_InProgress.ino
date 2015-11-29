/*********************************************************************
 * Capstone Project - Automated Drink Dispenser 
 * 
 * Members: Steven Rohoman & Milan Jovanovic
 * 
 * Date: September 28, 2015
 * 
 * Purpose:
 *  Will control Arduino microcontroller to pour specified drink into 
 *  cup along a moving platform.
 * 
 * Details:
 *  Contains main loop that will call 1 of 6 call functions designed to:
 *    1. Move platform to required spot.
 *    2. Release servo linkage to pour alcoholic liquid
 *    3. Enable Pump to pour chase liquid
 *    4. Move platform to returning location
 *    5. Setup LCD Displays
 *    6. Live display of drink status
 *    
 *  Revision 1.0
 *  Copyright (c) 2015 Steven Rohoman. All rights reservered.
 **********************************************************************/
#include <LiquidCrystal.h>
#include <Stepper.h>
#include <Servo.h>

//Constant Position Declaration
#define pos1 1875
#define pos2 3750
#define pos3 5625
#define pos4 7500

#define shot1 2000
#define shot2 4000
#define shot3 6000
#define shot4 8000

#define drink1 " RUM - Eldorado "
#define drink2 "VODKA - Smirnoff"
#define drink3 "WHISKEY - Jack D"
#define drink4 "TEQUILA - Patron"

//Object Declaration
Stepper stepper(200, 12, 13);

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

LiquidCrystal lcdDrink1(30, 31, 32, 33, 34, 35);
LiquidCrystal lcdDrink2(36, 37, 38, 39, 40, 41);
LiquidCrystal lcdDrink3(42, 43, 44, 45, 46, 47);
LiquidCrystal lcdDrink4(48, 49, 50, 51, 52, 53);

//Initalization of Objects
void setup() {
  stepper.setSpeed(1000);
  
  servo1.attach(8);
  servo2.attach(9);
  servo3.attach(10);
  servo4.attach(11);

  lcdDrink1.begin(16, 2);
  lcdDrink2.begin(16, 2);
  lcdDrink3.begin(16, 2);
  lcdDrink4.begin(16, 2);

//  pinMode(14, OUTPUT);
//  pinMode(15, OUTPUT);

  lcdOutput();
}

//Main Running Loop
void loop() {
  
  drinkPos(pos1);
  lcdChange(1, shot1);
  servoAlc(2000, 1);
  returnPos(pos1);
  pumpChase(1, 1000);
  lcdOutput();

  delay(1000);
}

/**********************************************************************************
 * Function 1 - drinkPos 
 * 
 * used to determine distance platform should go before stopping. This location will
 * be directly underneath servo. Using preset constants to stop perfectly at area.
 * This location can also be refered to as the "drink position".
 * 
 **********************************************************************************/
void drinkPos (int position) {
  int location = position;
  stepper.step(-location);
  delay(1000);

}

/**********************************************************************************
 * Function 2 - servoAlc 
 * 
 * Will activate Servo controlling linkage to pouring mechanism; dispensing alcohol
 * into cup (sitting on platform). Delay will be used to determine quantity of 
 * liquid released. 
 * 
 **********************************************************************************/
void servoAlc(int timeDelay, int drinkNum) {
  int holdTime = timeDelay;
  int servoNum = drinkNum;
  int pos = 0;

  if(servoNum == 1) {                         //Condition for first drink selection
        for(pos = 180; pos >= 0; pos--) {     //move servo up to dispense
          servo1.write(pos);
          delay(5); 
        }   

        delay(holdTime);                      //Hold for drink duration
  
        for(pos = 0; pos <= 180; pos++) {     //Move servo down to stop dispense
          servo1.write(pos);
          delay(5);
        }        
  }else if (servoNum == 2) {
        for(pos = 180; pos >= 0; pos--) {
          servo2.write(pos);
          delay(5); 
        }

        delay(holdTime);
  
        for(pos = 0; pos <= 180; pos++) {
          servo2.write(pos);
          delay(5);
        } 
  }else if (servoNum == 3) {
        for(pos = 180; pos >= 0; pos--) {
          servo3.write(pos);
          delay(5); 
        }

        delay(holdTime);
  
        for(pos = 0; pos <= 180; pos++) {
          servo3.write(pos);
          delay(5);
        }
  }else if (servoNum == 4) {
        for(pos = 180; pos >= 0; pos--) {
          servo4.write(pos);
          delay(5); 
        }

        delay(holdTime);
  
        for(pos = 0; pos <= 180; pos++) {
          servo4.write(pos);
          delay(5);
        }
  }

}

/********************************************************************************
* Function 3 - pumpChase
*
* Function will recieve length of drink to be dispensed and activate pump to 
* dispense non-alcoholic liquid.
*
********************************************************************************/
void pumpChase(int pumpNum, int holdTime) {

  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  
  if(pumpNum == 1) {
    digitalWrite(14, HIGH);
    delay(holdTime);
    digitalWrite(14, LOW);
  }else if (pumpNum == 2) {
    digitalWrite(15, HIGH);
    delay(holdTime);
    digitalWrite(15, LOW);
  }
}

/********************************************************************************
* Function 4 - returnPos
*
* Will return to the origin position for the drink platform. This function will
* only be called once drink has been poured. 
*
********************************************************************************/
void returnPos(int position){
  int location = position;
  stepper.step(location);
  delay(1000);
}

/********************************************************************************
* Function 5 - lcdOutput
*
* Will set the LCDs to the corresponding drink that will be served from specific 
* alcohol dispenser. Information can only be modified by machine controller.
*
********************************************************************************/
//maybe show amount of drink being dispensed
void lcdOutput() {
  lcdDrink1.setCursor(0,0);             //sets the cursor at row 0 column 0
  lcdDrink1.print("***Drink Type***");  
  lcdDrink1.setCursor(1,1);             //sets the cursor at row 1 coloumn 1
  lcdDrink1.print("RUM - Eldorado");    
  
  lcdDrink2.setCursor(0,0);             
  lcdDrink2.print("***Drink Type***");  
  lcdDrink2.setCursor(0,1);             
  lcdDrink2.print("VODKA - Smirnoff"); 
  
  lcdDrink3.setCursor(0,0);             
  lcdDrink3.print("***Drink Type***");  
  lcdDrink3.setCursor(0,1);             
  lcdDrink3.print("WHISKEY - Jack D");  
  
//  lcdDrink4.setCursor(0,0);             
//  lcdDrink4.print("***Drink Type***");  
//  lcdDrink4.setCursor(0,1);             
//  lcdDrink4.print("TEQUILA - Patron"); 
}

/********************************************************************************
* Function 6 - lcdChange
*
* Will display the amount of alcoholic being dispensed into cup.
*
********************************************************************************/
void lcdChange(int drinkNum, int length) {
  length = length / 2000;

  if(drinkNum == 1) {
    lcdDrink1.clear();
    lcdDrink1.setCursor(0,0);
    lcdDrink1.print(drink1);
    lcdDrink1.setCursor(0,1);
    lcdDrink1.print("Pouring ");
    lcdDrink1.print(length);
    lcdDrink1.print(" oz(s)");
  } else if (drinkNum == 2) {
    lcdDrink2.clear();
    lcdDrink2.setCursor(0,0);
    lcdDrink2.print(drink2);
    lcdDrink2.setCursor(0,1);
    lcdDrink2.print("Pouring ");
    lcdDrink2.print(length);
    lcdDrink2.print(" oz(s)");
  }else if (drinkNum == 3) {
    lcdDrink3.clear();
    lcdDrink3.setCursor(0,0);
    lcdDrink3.print(drink3);
    lcdDrink3.setCursor(0,1);
    lcdDrink3.print("Pouring ");
    lcdDrink3.print(length);
    lcdDrink3.print(" oz(s)");
  }else if (drinkNum == 4) {
    lcdDrink4.clear();
    lcdDrink4.setCursor(0,0);
    lcdDrink4.print(drink4);
    lcdDrink4.setCursor(0,1);
    lcdDrink4.print("Pouring ");
    lcdDrink4.print(length);
    lcdDrink4.print(" oz(s)");
  }
}
