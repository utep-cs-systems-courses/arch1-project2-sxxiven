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
  {Bb5, Three}, {Bb5, Eigth}, {A5, Eigth}, {Bb5, Half}, {C6, Eigth}, {C6, Half}, {Eb6, Eigth},
  {Eb6, Three},

  {D6, Eigth}, {Bb5, Eigth}, {C6, Half}, {A5, Eigth}, {F5, Quarter}, {D6, Eigth}, {Bb5, Eigth},
  {C6, Three},

  {F6, Eigth}, {Bb5, Eigth}, {Eb6, Half}, {D6, Eigth}, {D6, Half}, {C6, Eigth}, {C6, Full},
  {Bb6, Eigth}, {A6, Eigth}, {Bb6, Quarter}, {F6, Quarter}, {Eb6, Quarter},
  {Bb6, Eigth}, {A6, Eigth}, {Bb6, Half}, {F6, Quarter}, {Bb5, Quarter}, {Ab6, Full},
  
  {Bb6, Eigth}, {A6, Eigth}, {Bb6, Quarter}, {F6, Eigth}, {E6, Eigth}, {F6, Quarter},
  {Eb6, Eigth},{D6, Eigth},

  {Eb6, Quarter}, {C6, Eigth}, {Bb5, Eigth}, {C6, Quarter},

  {Bb6, Eigth}, {A6, Eigth}, {Bb6, Quarter}, {F6, Eigth}, {E6, Eigth}, {F6, Half},
  {A6, Full}, {Bb6, Full}
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

/* the following sets the conditions for when the siren is on its low state */
char siren_low()
{
  delay = 1;
  reps++;
  green_led = 1; 
  buzzer_set_period(3500);
  return 1; 
}

char siren_high()
{
  delay = 250;
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
void play_note()
{
  green_led = 0;
  delay = music_score[playing_note][1];
  buzzer_set_period(music_score[playing_note][0]);
  /* for(int i =0; i < 500; i++)
  {
    //buzzer_set_period(music_score[playing_note][0]);

    //the following switch statemant determinse on how long the note will play
    switch(music_score[playing_note][1])
    {
    case 0: delay = 25;  break; 
    case 1: delay = 50; break;
    case 2: delay = 100; break;
    case 3: delay = 150; break;
    case 4: delay = 200; break; 
      /* case 0:  __delay_cycles(4000); break;  // eigth note
    case 1:  __delay_cycles(8000); break;  // quarter note
    case 2: __delay_cycles(16000); break;  // half note
    case 3: __delay_cycles(24000); break;  // three quarter note length
    case 4: __delay_cycles(32000); break;  // full note
    case 5: __delay_cycles(500);   break;  // gap between each note 
          
    }
  }*/
}
