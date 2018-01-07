/**
 * @file globalVars.cpp
 * @author Kelly Lynch
 * @date 07 Jan 2018
 * @brief Contains values for global variables
 *
 * Things such as pin numbers go here.
 * 
 */
 
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
