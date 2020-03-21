#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"

unsigned char s_letter = 1, o_letter = 0, siren_led = 0;
unsigned char led_changed = 0, count_on = 0, disable_all = 0;
char siren_enable; 

static char greenVal[] = {0, LED_GREEN};


void led_init()
{
  P1DIR |= LEDS;
  switch_state_changed = 1;
  led_update(); 
}

void led_update()
{

  if(disable_all)
  {
    P1OUT &= (0xff^LED_GREEN) | 0; 
  }
  
  //below is the segment where the led lights will count when button 0 is pressed
  if ((led_changed && count_on) || (led_changed && siren_enable))
    {
      unsigned char green_on = (s_letter || o_letter || siren_led); 
      char ledFlags = greenVal[green_on];

      P1OUT &= (0xff^LEDS) | ledFlags; //clear bit for off leds
      P1OUT |= ledFlags;
      led_changed = 0; 
  }
  
  switch_state_changed = 0; 
}
