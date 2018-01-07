/**
 * @file functions.cpp
 * @author Kelly Lynch
 * @date 07 Jan 2018
 * @brief Functions for the program
 *
 * Contains all functions contained in the program.
 * 
 */

/* -- Includes -- */
#include "functions.h"
#include "presetScreens.h"
#include "chars.h"
#include "globalVars.h"


/* -- Functions -- */
/**
* @brief Scroll Screen Function
* Scrolls any array of 8 columns.
* 
* @return Does not reutrn in code, but should produce a scrolling effect on the LED Matrix
* @bugs Not working yet
*/
void scrollScreen(char inText[], int scrollSpeed){
  /* Reverse String, I don't know why but it must be done */
  int len = strlen(inText);
  char inputString[len+1];
  for(int i=0, k=len-1; i<=len; i++, k--){
    inputString[k] = inText[i]; 
  }
  /* Append Null Terminator */
  inputString[len] = '\0';

  
  /* Setup display array with size depending on string length */
  int dispLength = strlen(inText)*8; 
  int strLength = strlen(inText);
  byte dispArray[8][strLength];
  byte dispArrayTest[8][3];
  
  /* Populate the display array */
  //for(int i=0; i<strlen(inText); i++){
  for(int i=strLength-1; i>=0; i--){
    /* Place display character into temporary array */
    //byte tempDispChar[8];
    char charToPlace = inputString[i];
    for(int j=0; j<=7; j++){
      //tempDispChar[j] = charLookupTable(inText[i])[j];    
      dispArray[j][i] = charLookupTable(charToPlace)[j];
      dispArrayTest[j][i] = charLookupTable(charToPlace)[j];
    } 
    //Serial.println(inText[i]);   
  }

  int offset = 0;
  /* Create a Screen from the display array */
  byte screen[8][3];
  for(int i=0; i<=7; i++){
    for(int j=0; j<=2; j++){
      if(j==0){
        screen[i][j] = dispArray[i][0];
      }else if(j==1){
        screen[i][j] = dispArray[i][1];
      }else if(j==2){
        screen[i][j] = dispArray[i][2];
      }
       
    }  
  //Serial.println(i);
  }
  
  dispScreen(dispArrayTest);
  //delay(scrollSpeed);
  //Serial.println(inText);
  //Serial.print("sizeof inText: ");
  //Serial.println(strlen(inText));
  //Serial.print('\n');
  //Serial.println(sizeof(dispArray[1]));
}


/**
* @brief Create Screen Function
* Combines 3 chars as defined in chars.h and chars.cpp to produce a full screen made
* up the 3 chars in sequence.
* 
* @return should not return, but produces a screen made up of the three characters passed
*/
void createScreen(const byte char1[8], const byte char2[8], const byte char3[8]){
  byte screen[8][3];
  /* Create the 8x3 matrix of bytes */
  for(int i=0; i<=7; i++){
    for(int j=0; j<=2; j++){
      if(j==0){
        screen[i][j] = char3[i]; 
      }else if(j==1){
        screen[i][j] = char2[i]; 
      }else if(j==2){
        screen[i][j] = char1[i];
      }
    }
  }
  /* Display end product */
  dispScreen(screen);
}


/**
* @brief Create Screen From Text Function
* Gets the first 3 (at least) characters from a string and displays them
* 
* @return should not return, but produces a screen made up of the first three characters 
* passed of the string
*/
void createScreenFromText(char* inText){
  byte screen[8][3];
  /* Initialise characters to blank */
  byte char1[8];
  byte char2[8];
  byte char3[8];
  for(int i=0; i<=7; i++){
    char1[i] = 0b11111111;
    char2[i] = 0b11111111;
    char3[i] = 0b11111111;  
  }

  /* Fill Char characters with first 3 characters in string */
  for(int i=0; i<=sizeof(inText); i++){
    for(int j=0; j<=7; j++){
      if(i==0){
        char1[j] = charLookupTable(inText[i])[j];
      }else if(i==1){
        char2[j] = charLookupTable(inText[i])[j];
      }else if(i==2){
        char3[j] = charLookupTable(inText[i])[j];
      }
    }
    /* Don't waste time on the rest of the string */
    if(i>2){
      break;
    }  
  }
  
  /* Create the 8x3 matrix of bytes */
  for(int i=0; i<=7; i++){
    for(int j=0; j<=2; j++){
      if(j==0){
        screen[i][j] = char3[i]; 
      }else if(j==1){
        screen[i][j] = char2[i]; 
      }else if(j==2){
        screen[i][j] = char1[i];
      }
    }
  }

  /* Display end product */
  dispScreen(screen);
}


/**
* @brief Flash Screen function
* Pulses an image on the LED matrix at a user specified frequency in Hz.
* 
* @return Does not reutrn in code, but should produce a flashing result on LED Matrix
* @bugs Accuracy of input is lost above 30Hz
*/
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
* @brief Quick Shift Out function
* Optimised version of shiftout, loses general cases but is much quicker (~100uS for 3 bytes
* compared to ~470uS in shiftOut()).
* 
* This function assumes all pins are on PORTB (pins 8 to 13) and that the LSB will be passed first.
* 
* @return should not return, but shifts values into shift registers.
*/
void shiftOutQuick(int dataPinVal, int clockPinVal, byte val){
  /* Clear Data Pin*/
  bitClear(PORTB, dataPinPORTB);
  
  for(int i=0; i <= 7; i++){
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



