#include <msp430.h>
#include "led.h"
#include "switches.h"

unsigned char green_led = 0, led_changed = 0, count_on = 0, disable_all = 0;
char siren_enable; 

static char greenVal[] = {0, LED_GREEN};

//initializes the led
void led_init()
{
  P1DIR |= LEDS;
  switch_state_changed = 1;
  led_update(); 
}

void led_update()
{

  //clears all bits from the green led when all is disabled (last button)
  if(disable_all)
  {
    P1OUT &= (0xff^LED_GREEN) | 0;
    P1OUT &= 0;
    disable_all = 0; 
  }
  
  //below updates the led by turning it on or off according to the currenst state
  else
    {
      //the green_on determines if the led will be on accrding to the led flags 
      char ledFlags = greenVal[green_led];

      P1OUT &= (0xff^LED_GREEN) | ledFlags; //clear bit for off leds
      P1OUT |= ledFlags;
      led_changed = 0; 
    }
  switch_state_changed = 0; 
}
