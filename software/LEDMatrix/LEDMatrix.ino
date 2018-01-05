/**
 * @file LEDMatrix.ino
 * @author Kelly Lynch
 * @date 05 Jan 2018
 * @brief Driver and application of a multiplexed 24x8 LED Matrix.
 *
 * This file aims to drive a 24x8 LED display with functions for displaying
 * any applicable arbitrary text and animations.
 */


/* Includes */
#include "presetScreens.h"
#include "chars.h"

/* -- Pin Declarations -- */
/* 4017 Pins */
int counterClockPin = 9;
int counterResetPin = 8;
int counterClockPinPORTB = counterClockPin - 8;
int counterResetPinPORTB = counterResetPin - 8;

/* 74HC595 Pins */
int latchPin = 10;
int dataPin = 11;
int clockPin = 13;
int latchPinPORTB = latchPin - 8;
int dataPinPORTB = dataPin - 8;
int clockPinPORTB = clockPin - 8;


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
}

/**
* @brief loop function
* Runs repeatedly forever, this is the main hub of the program.
* 
* @return should not return
*/
void loop() {  
  dispScreen(happy);
  //flashScreen(OwO, 120);
}

/**
* @brief Display Screen Function
* When passed an 8x3 array of bytes (corrosponding to 8 rows and 24 (8bits*3)
* columns in the LED array) this function displays this to the LED matrix.
* 
* @return Does not return in code, but should produce result on LED matrix.
*/
void dispScreen(byte dispArray[8][3]){
  /* Reset 4017 Counter */
  bitSet(PORTB, counterResetPinPORTB);   // Pin 8 High
  bitClear(PORTB, counterResetPinPORTB); // Pin 8 Low

  /* Write Data for all 8 rows */
  for(int i=0; i<=7; i++){
    /* Write 24bits to the shift Registers */
    bitClear(PORTB, latchPinPORTB); // Pin 10 Low
    for(int j=0; j<=2; j++){
      shiftOutQuick(dataPinPORTB, clockPinPORTB, dispArray[i][j]);
    }
    bitSet(PORTB, latchPinPORTB); // Pin 10 High

    /* Clear Shift Registers to avoid ghosting */
    bitClear(PORTB, latchPinPORTB); // Pin 10 Low
    for(int j=0; j<=2; j++){
      shiftOutQuick(dataPinPORTB, clockPinPORTB, 0b11111111);
    }
    bitSet(PORTB, latchPinPORTB); // Pin 10 High
    
    /* Create Rising Edge to go to next pin */
    bitClear(PORTB, counterClockPinPORTB); // Pin 9 Low
    bitSet(PORTB, counterClockPinPORTB);   // Pin 9 High
  }

}

/**
* @brief Flash Screen function
* Pulses an image on the LED matrix at a user specified frequency in Hz.
* 
* @return Does not reutrn in code, but should produce a flashing result on LED Matrix
* @bugs Accuracy of input is lost above 30Hz
*/
/* Loses accuracy above about 30Hz */
void flashScreen(byte dispArray[8][3], float delayFreq){
  /* Calculate the required delay time in milliseconds */
  int delayTime = (1/delayFreq)*1000/2;
  int startTime = millis();
  int endTime = startTime;

  /* Loop until the required amount of time has elapsed */
  while(endTime - startTime <= delayTime){
    dispScreen(dispArray);
    endTime = millis();
  }
  
  /* Off for same amount of time */
  delay(delayTime);
}


/**
* @brief Quick Shift Out function
* Optimised version of shiftout, loses general cases but is much quicker (~100uS for 3 bytes
* compared to ~470uS in shiftOut()).
* 
* This function assumes all pins are on PORTB (pins 8 to 13) and that the MSB will be passed first.
* 
* @return should not return, but shifts values into shift registers.
*/
void shiftOutQuick(int dataPinVal, int clockPinVal, byte val){
  /* Clear Data Pin*/
  bitClear(PORTB, dataPinPORTB);
  
  for(int i=7; i >= 0; i--){
    /* Set bits based on input value */
    if(bitRead(val, i) == 1){
      bitSet(PORTB, dataPinVal);   // Write 1
    }else{
      bitClear(PORTB, dataPinVal); // Write 0
    }
      
    /* Clock Shift Registers */
    bitClear(PORTB, clockPinVal);
    bitSet(PORTB, clockPinVal);
  }
}
