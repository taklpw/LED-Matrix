/**
 * @file globalVars.h
 * @author Kelly Lynch
 * @date 07 Jan 2018
 * @brief Defines names and sizes of global variables
 */

#ifndef H_globalVars
#define H_globalVars

/* Includes */
#include <Arduino.h>

/* -- Pin Declarations -- */
/* 4017 Pins */
extern int counterClockPin;
extern int counterResetPin;
extern int counterClockPinPORTB;
extern int counterResetPinPORTB;

/* 74HC595 Pins */
extern int latchPin;
extern int dataPin;
extern int clockPin;
extern int latchPinPORTB;
extern int dataPinPORTB;
extern int clockPinPORTB;

#endif

