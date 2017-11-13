
#include "tiny_buttons.h"

#include <Arduino.h>


/*  if (buttonValue < 100) {
    return BUTTON_RIGHT;  
  }
  else if (buttonValue < 200) {
    return BUTTON_UP;
  }
  else if (buttonValue < 400){
    return BUTTON_DOWN;
  }
  else if (buttonValue < 600){
    return BUTTON_LEFT;
  }
  else if (buttonValue < 800){
    return BUTTON_SELECT;
  } */


const int16_t buttons[5]    =  { 0,   143,  327,  504, 740 };

TinyAnalogButtons g_buttons(A3, buttons, sizeof(buttons)/sizeof(buttons[0]) );

void plcInitButtons()
{
   pinMode(A3, INPUT);
}