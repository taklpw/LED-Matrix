/**
 * @file functions.h
 * @author Kelly Lynch
 * @date 07 Jan 2018
 * @brief Contains prototypes for functions used in the program.
 */

#ifndef H_functions
#define H_functions

/* Includes */
#include <Arduino.h>

/* -- Functions Prototypes -- */
void dispScreen(byte[8][3]);
void flashScreen(byte[8][3], float);
void scrollScreen(char[], int);
void createScreen(const byte[8], const byte[8], const byte[8]);
void createScreenFromText(char*);
void shiftOutQuick(int, int, byte);


#endif
