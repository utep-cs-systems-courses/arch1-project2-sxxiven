#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

char delay = 150, reps = 0, siren_enable = 0;  
char toggle_S()		/* always toggle! */
{
  delay = 10;
  s_letter = 1; 
  reps++;
  buzzer_set_period(1000);
  return 1;			/* always changes an led */
}

char toggle_O()	/* only toggle green if red is on!  */
{
  char changed = 0;
  delay = 80;
  o_letter = 1;
  buzzer_set_period(1000);
  reps++; 
  return 1;
}

char toggle_off(char off_delay) /* change the green led off */
{
  s_letter = 0;
  o_letter = 0;
  siren_led = 0; 
  delay = off_delay;
  if(count_on)
  {
    buzzer_set_period(0); 
  }
  return 1; 
}

char siren_low()
{
  delay = 2;
  reps++;
  siren_led = 1; 
  buzzer_set_period(3500);
  return 1; 
}

char siren_high()
{
  delay = 100;
  reps = 0;
  siren_led = 1;
  buzzer_set_period(2500);
  return 1; 
}

void play_note(int note, int delay)
{
  for(int i =0; i < 500; i++)
  {
    buzzer_set_period(note);
    switch(delay)
    {
    case 0:  __delay_cycles(4000); break; 
    case 1:  __delay_cycles(8000); break;
    case 2: __delay_cycles(16000); break;
    case 3: __delay_cycles(24000); break;
    case 4: __delay_cycles(32000); break;
    case 5: __delay_cycles(500);   break; 
    }
  }
}

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

void state_advance()
{
  char changed = 0;
    
  static enum {
    sec1 = 0, sec2 = 1, sec3 = 2, sec4 = 3, sec5 = 4, sec6 = 5, sec7 = 6, sec8 = 7, sec9 = 8,
    S = 9, O = 10, low = 11, high = 12, off = 13, direct = 14
  }section = direct; 

  if(switch_state_down0 || switch_state_down || switch_state_down2)
  {
    section = direct; 
  }
  
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
    if(siren_enable)
    {
      section = (reps < 25) ? off : high;
    }
    else
    {
      section = direct; 
    }
    break;  
  case high:
    changed = siren_high();
    if(siren_enable)
    {
      section = low; 
    }
    else
    {
      section = direct; 
    }

      break;
  case off:
    if(reps < 3 && count_on)
    {
      section = (s_letter) ? S : O;
      changed = toggle_off(50); 
    }
    else if (reps == 3 && count_on)
    {
      section = (s_letter) ? O : S;
      changed = toggle_off(100);
      reps = 0; 
    }
    else if(reps<25 && siren_enable)
    {
      changed = toggle_off(2); 
      section = low; 
    }
    break;
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
  if(count_on || siren_enable)
  {
    led_changed = changed;
    led_update();
  }
}
