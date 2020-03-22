#ifndef led_included
#define led_included

#include <msp430.h>

#define LED_GREEN BIT6              // P1.6
#define LEDS BITS

extern unsigned char s_letter, o_letter,siren_led; 
extern unsigned char led_changed, count_on, disable_all;
extern char delay, reps; 


void led_init();             // initialize LEDs
void led_update();           // updates leds

//these are boolean flags
extern unsigned char leds_changed;

#endif
