#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "states.h"


char switch_state_down, switch_state_down0, switch_state_changed, section; /* effectively boolean */
char switch_state_down2, switch_state_down3, jurrasic_enable, siren_enable; 
unsigned char count_on;

static char
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);  /* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES); /* if switch down, sense up */
  return p2val; 
}

void
switch_init()                   /* setup switches */
{
  P2REN |= SWITCHES;            /* enables resistors for switches */
  P2IE = SWITCHES;              /* enable interrupts from switches */
  P2OUT |= SWITCHES;            /* pull-u[s for switches */
  P2DIR &= ~SWITCHES;           /* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update(); 
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switch_state_down = (p2val & SW1) ? 0 : 1; /* when SW1 is up */
  switch_state_down0 = (p2val & SW0) ? 0 : 1; /* when SW0 is up */
  switch_state_down2 = (p2val & SW2) ? 0 : 1; /* when SW2 is up */
  switch_state_down3 = (p2val & SW3) ? 0 : 1; /* when SW3 is up */
  switch_state_changed = 1;

  // Button 0 enables the count_on for the S.O.S message
  if(switch_state_down0)
  {
    section =1;
    reps = 0; 
    count_on = 1;
    jurrasic_enable = 0;
    siren_enable = 0;
  }

  // Button 1 enables the siren_enable for the siren
  if(switch_state_down)
  {
    section = 2;
    reps = 0;
    count_on = 0;
    siren_enable = 1;
    jurrasic_enable = 0; 
  }

  // Button 2 enables the jurrasic_enable to play the jurrasic theme song
  if(switch_state_down2)
  {
    section = 0;
    playing_note =0; 
    jurrasic_enable = 1;
    count_on = 0;
    siren_enable = 0; 
  }

  // Button 3 disables all to stop all current states
  if(switch_state_down3)
  {
    buzzer_set_period(0);
    green_led = 0; 
    count_on = 0;
    jurrasic_enable = 0;
    siren_enable = 0;
    disable_all = 1;
  }
  led_update();
}
