#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0; 
  if(blink_count == delay && (jurrasic_enable || count_on || siren_enable))
  {
    state_advance();
    blink_count = 0; 
  }
   blink_count++; 
}
