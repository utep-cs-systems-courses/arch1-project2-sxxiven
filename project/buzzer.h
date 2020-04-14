#ifndef buzzer_included
#define buzzer_included

void buzzer_init();
void buzzer_set_period(short cycles);

extern char jurrasic_enable, siren_enable, playing_note; 

#endif // included
