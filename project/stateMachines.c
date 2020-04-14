#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "off.h"

//the following are the global variables used
char delay = 150, reps = 0, siren_enable = 0, s_letter = 1, changed;

int music_score[54][2] =
  {
  {2145, 3}, {2145, 0}, {2273, 0}, {2145, 2}, {1911, 0}, {1911, 2}, {1607, 0}, {1607, 3},
  {1703, 0}, {2145, 0}, {1911, 2}, {2273, 0}, {2863, 1}, {1703, 0}, {2145, 0}, {1911, 3},
  {1432, 0}, {2145, 0}, {1607, 2}, {1703, 0}, {1703, 2}, {1911, 0}, {1911, 4},
  {1073, 0}, {1136, 0}, {1073, 1}, {1432, 1}, {1607, 1},
  {1073, 0}, {1136, 0}, {1073, 2}, {1432, 1}, {2145, 1}, {1204, 4},
  {1073, 0}, {1136, 0}, {1073, 1}, {1432, 0}, {1517, 0}, {1432, 1}, {1607, 0}, {1703, 0},
  {1607, 1}, {1911, 0}, {2145, 0}, {1911, 1},
  {1073, 0}, {1136, 0}, {1073, 1}, {1432, 0}, {1517, 0}, {1432, 2}, {1136, 4}, {1073,4}
  }; 

/*  The following funtion toggles the s which is comprimised of three short 'beeps'*/
char toggle_SOS()	   
{
  delay = (reps < 3) ? 10 : 80;
  green_led = 1; 
  reps++;
  buzzer_set_period(1000);
  return 1;		      
}

/* The following toggles the o which is coprimised of three long 'beeps'*/
char toggle_O()
{
  delay = 80;
  green_led = 1;
  buzzer_set_period(1000);
  reps++; 
  return 1;
}

/* the following sets the conditions for when the siren is on its low state */
char siren_low()
{
  delay = 2;
  reps++;
  green_led = 1; 
  buzzer_set_period(3500);
  return 1; 
}

/* The follwing sets the conditions for when the siren is on its high state */
char siren_high()
{
  delay = 100;
  reps = 0;
  green_led = 1;
  buzzer_set_period(2500);
  return 1; 
}

char toggle_off()
{
  char changed = 0; 
  if(reps <3 && count_on)
  {
   changed = toggle_leds_off(50);
  }
  else if (reps >= 3 && count_on)
  {
    if(reps == 6)
    {
      reps = 0;
    }
    changed = toggle_leds_off(100);
  }
  else if (siren_enable)
  {
    changed = toggle_leds_off(2); 
  }
  return changed;
}

/* The following function instructs on how to play the specifies not and its delay (total time) */
void play_note(int note, int delay)
{
  green_led = 0; 
  for(int i =0; i < 500; i++)
  {
    buzzer_set_period(note);

    //the following switch statemant determinse on how long the note will play
    switch(delay)
    {
    case 0:  __delay_cycles(4000); break;  // eigth note
    case 1:  __delay_cycles(8000); break;  // quarter note
    case 2: __delay_cycles(16000); break;  // half note
    case 3: __delay_cycles(24000); break;  // three quarter note length
    case 4: __delay_cycles(32000); break;  // full note
    case 5: __delay_cycles(500);   break;  // gap between each note 
    }
  }
}
/* The following function controls the state of the msp430 which is directed by which buttons
   are pressed. It has three differenct sections. Button 0 corresponds to the S.O.S message. 
   Button 1 corresponds to the siren. Button 2 corresponds to the Jurrasic Park theme song. 
   Button 4 is not includes here. Its purose is to stop all current functions. */
void state_advance()
{
  //state machine sections
  switch(section)
  { 
  case 0:
    delay = 20;
    play_note(music_score[playing_note][0], music_score[playing_note][1]);
    section = 0; 
    break;
  case 1:     changed = toggle_SOS(); section = 4;       break;
  case 2:
    changed = siren_low();
    //the following switches between off and high for the siren if it is enable
    section = (reps <25) ? 4 : 3;
    break;  
  case 3:
    changed = siren_high();
    //the following swtiches between the off and low for the siren if it is enabled
    section = 2;
    break;
  case 4:
    //the following two sections toggles the s and o letters for the first button
    if(count_on){ section = 1;}
    if(siren_enable){ section = 2;}
    changed = toggle_off(); 
    break;
  }
    led_changed = changed;
    led_update();
}
