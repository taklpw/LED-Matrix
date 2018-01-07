/**
 * @file LEDMatrix.ino
 * @author Kelly Lynch
 * @date 05 Jan 2018
 * @brief Driver and application of a multiplexed 24x8 LED Matrix.
 *
 * This file aims to drive a 24x8 LED display with functions for displaying
 * any applicable arbitrary text and animations.
 */

/* -- Includes -- */
/* Libraries */

/* Local Includes */
#include "presetScreens.h"
#include "chars.h"
#include "globalVars.h"
#include "functions.h"


/**
* @brief Setup function
* Setup function to determine pin directions and other
* setup tasks.
* 
* @return should not return
*/
void setup() {
  /* Setup 4017 Pins */
  pinMode(counterClockPin, OUTPUT);
  pinMode(counterResetPin, OUTPUT);
  digitalWrite(counterResetPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(counterResetPin, LOW);

  /* Setup 74HC595 Pins */
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  Serial.begin(9600);
}


/**
* @brief loop function
* Runs repeatedly forever, this is the main hub of the program.
* 
* @return should not return
*/
void loop() {  
  //dispScreen(all);
  //flashScreen(happy, 10);
  //createScreen(charLookupTable(':'),charLookupTable('\''),charLookupTable(')'));
  //createScreenFromText("ABC");
  scrollScreen("12adsfghetrg", 50);
}

