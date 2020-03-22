        	.arch msp430g2553
		.p2align 1,0
		.text

		;; the following toggles all leds off, sets the delay, and determiens if the
		;; buzzer is set to 0 (buzzer is turned off)

		 .global toggle_leds_off
toggle_leds_off: nop
		 mov.b r12, &delay  ; sets the delay
	         mov #0, &siren_led ; the following three instructions turns off all LEDS 
	         mov #0, &s_letter
		 mov #0, &o_letter

		 cmp #0, &count_on  ; checks if count_on is enables 
		 jz out
	
		 mov #0, r12	    ; buzzer is turned off if counter is enabled
		 call #buzzer_set_period
out:	
		 mov #1, r12
		 pop r0		    ; returns 1 meaning that leds has changed
	
	     
