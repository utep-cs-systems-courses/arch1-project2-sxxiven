#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "off.h"

//the following are the global variables used
char delay = 150, reps = 0, siren_enable = 0;

/*  The following funtion toggles the s which is comprimised of three short 'beeps'*/
char toggle_S()	   
{
  delay = 10;
  s_letter = 1; 
  reps++;
  buzzer_set_period(1000);
  return 1;		      
}

/* The following toggles the o which is coprimised of three long 'beeps'*/
char toggle_O()
{
  delay = 80;
  o_letter = 1;
  buzzer_set_period(1000);
  reps++; 
  return 1;
}

/* the following sets the conditions for when the siren is on its low state */
char siren_low()
{
  delay = 2;
  reps++;
  siren_led = 1; 
  buzzer_set_period(3500);
  return 1; 
}

/* The follwing sets the conditions for when the siren is on its high state */
char siren_high()
{
  delay = 100;
  reps = 0;
  siren_led = 1;
  buzzer_set_period(2500);
  return 1; 
}

/* The following function instructs on how to play the specifies not and its delay (total time) */
void play_note(int note, int delay)
{
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

/* First sectoin of the Jurrasic Park theme song */
void section_1()
{
  delay = 5; 
  for(int i = 0; i < 2; i++)
  {
    play_note(2145, 3);
    play_note(0, 1);
    play_note(2145, 0);
    play_note(0, 5);
    play_note(2273, 0);
    play_note(0, 5);
  }
}

/* Second section of the Jurrasic Park theme song */
void section_2()
{
  delay = 5; 
  play_note(2145, 2);
  play_note(0, 5);
  play_note(1911, 0);
  play_note(0, 5);
  play_note(1911, 2);
  play_note(0, 5);
  play_note(1607, 0);
  play_note(0, 5);
  play_note(1607, 3);
  play_note(0, 5); 
}

/* Third section of the Jurrasic Park theme song */
void section_3()
{
  play_note(1703, 0);
  play_note(0, 5);
  play_note(2145, 0);
  play_note(0, 5);
  play_note(1911, 2);
  play_note(0, 5);
  play_note(2273, 0);
  play_note(0, 5);
  play_note(2863, 1);
  play_note(5,0);
  play_note(1703, 0);
  play_note(0,5);
  play_note(2145,0);
  play_note(0,5);
  play_note(1911, 3); 
}

/* Fourth section of the Jurrasic Park theme song */
void section_4()
{
  reps++; 
  play_note(1432, 0);
  play_note(0, 5);
  play_note(2145, 0);
  play_note(0, 5);
  play_note(1607, 2);
  play_note(0,5);
  play_note(1703, 0);
  play_note(0,5);
  play_note(1703, 2);
  play_note(0,5);
  play_note(1911, 0);
  play_note(0, 5);
  play_note(1911, 4);
  play_note(0, 5);
}

/* Firth section of the Jurrasic park theme song */
void section_5()
{
  reps = 0; 
  for(int i =0; i< 2; i++)
  {
    play_note(1073, 0);
    play_note(0, 5);
    play_note(1136, 0);
    play_note(0, 5);
    play_note(1073, 1);
    play_note(0, 5);
    play_note(1432, 1);
    play_note(0, 5);
    play_note(1607, 1); 
  }
}

/* Sixth section of the Jurrasic Park theme song */
void section_6()
{
  play_note(1073, 0);
  play_note(0, 5);
  play_note(1136, 0);
  play_note(0, 5);
  play_note(1073, 2);
  play_note(0, 5);
  play_note(1432, 1);
  play_note(0, 5);
  play_note(2145, 1);
  play_note(0, 5);
  play_note(1204, 4);
  play_note(0, 5); 
}

/*Seventh section of the Jurrasic Park theme song */
void section_7()
{
  play_note(1073, 0);
  play_note(0, 5);
  play_note(1136, 0);
  play_note(0, 5);
  play_note(1073, 1);
  play_note(0, 5);
  play_note(1432, 0);
  play_note(0, 5);
  play_note(1517, 0);
  play_note(0, 5); 
  play_note(1432, 1);
  play_note(0, 5);
  play_note(1607, 0);
  play_note(0, 5);
  play_note(1703, 0);
  play_note(0, 5);
  play_note(1607, 1);
  play_note(1911, 0);
  play_note(0, 5);
  play_note(2145, 0);
  play_note(0, 5);
  play_note(1911, 1);
  play_note(0, 5); 
  
}

/* Eight section of the Jurrasic Park theme song */
void section_8()
{
  delay = 250; 
  play_note(1073, 0);
  play_note(0, 5);
  play_note(1136, 0);
  play_note(0, 5);
  play_note(1073, 1);
  play_note(0, 5); 
  play_note(1432, 0);
  play_note(0, 5);
  play_note(1517, 0);
  play_note(0, 5);
  play_note(1432, 2);
  play_note(0, 5);
  play_note(1136, 4);
  play_note(0, 5);
  play_note(1073, 4);
  play_note(0, 5); 
}

/* The following function controls the state of the msp430 which is directed by which buttons
   are pressed. It has three differenct sections. Button 0 corresponds to the S.O.S message. 
   Button 1 corresponds to the siren. Button 2 corresponds to the Jurrasic Park theme song. 
   Button 4 is not includes here. Its purose is to stop all current functions. */
void state_advance()
{
  char changed = 0; 

  //the state names of the machine is listed here
  static enum {
    sec1 = 0, sec2 = 1, sec3 = 2, sec4 = 3, sec5 = 4, sec6 = 5, sec7 = 6, sec8 = 7, sec9 = 8,
    S = 9, O = 10, low = 11, high = 12, off = 13, direct = 14
  }section = direct; 

  //if a button is being pressed, the state switches to the directory which is then passed along
  //to the porper section
  if(switch_state_down0 || switch_state_down || switch_state_down2)
  {
    section = direct; 
  }

  //state machine sections
  switch(section)
  { 
  case sec1:  section_1(); section = sec2;               break; 
  case sec2:  section_2(); section = sec3;               break;
  case sec3:  section_3(); section = sec4;               break;
  case sec4:  section_4(); section = (reps <2) ? sec1 : sec5; break;
  case sec5:  section_5(); section = sec6;               break;
  case sec6:  section_6(); section = sec7;               break;
  case sec7:  section_5(); section = sec8;               break;
  case sec8:  section_7(); section = sec9;               break;
  case sec9:  section_8(); section = sec1;               break;
  case S:     changed = toggle_S(); section = off;       break;
  case O:     changed = toggle_O(); section = off;       break;
  case low:
    changed = siren_low();
    //the following switches between off and high for the siren if it is enabled
    if(siren_enable)
    {
      section = (reps < 25) ? off : high;
    }
    //it swtiches back to the drectory if the siren is not enabled
    else
    {
      section = direct; 
    }
    break;  
  case high:
    changed = siren_high();
    //the following swtiches between the off and low for the siren if it is enabled
    section = (siren_enable) ? low : direct;
    break;
  case off:
    //the following two sections toggles the s and o letters for the first button
    if(reps < 3 && count_on)
    {
      section = (s_letter) ? S : O;
      changed = toggle_leds_off(50); 
    }
    else if (reps == 3 && count_on)
    {
      section = (s_letter) ? O : S;
      changed = toggle_leds_off(100);
      reps = 0; 
    }
    //this toggles the siren led makeing it "glow" with the low siren 
    else if(reps< 25 && siren_enable)
    {
      changed = toggle_leds_off(2); 
      section = low; 
    }
    break;

    //the following direct case switches the section according to which button is being pressed
  case direct:
    reps = 0; 
    if(switch_state_down2)
    {
      section = sec1;
      siren_enable = 0;
    }
    else if(switch_state_down0)
    {
      section = S;
      siren_enable = 0; 
    }
    else if(switch_state_down)
    {
      siren_enable = 1;
      section = low; 
    }

    break;
  }
  //updates the led if first or second buttong was pressed
  if(count_on || siren_enable)
  {
    led_changed = changed;
    led_update();
  }
}
