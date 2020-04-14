#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

char playing_note = 0, song_length = 54; 

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  //activates the states for all three buttons if they are enables
 
  if(blink_count == delay && (jurrasic_enable || count_on || siren_enable))
  {

    //the following make sure the song plays then next note
    if(jurrasic_enable)
    {
      playing_note++;
      playing_note = playing_note % song_length; 
    }
    //advances the states and rests the count
    state_advance();
    blink_count = 0; 
  }
  if( jurrasic_enable == 0 ){ 
    playing_note = 0;
  }
   blink_count++; 
}
