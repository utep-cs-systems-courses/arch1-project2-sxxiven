		.arch msp430g2553
		.p2align 1,0
	
		.text
;;; the followin is the switch statements that directs the state machine where to proceed next.
jt:
		.word song	;jt[0] plays song
		.word sos 	;jt[1] plays s.o.s message in morse code
		.word low	;jt[2] plays the low siren
		.word high 	;jt[3] plays the high siren
		.word off	;jt[4] directs to turn off the led and buzzer temporarily as needed
		


		.global states_advance
states_advance:	nop
		cmp #5, &section ;takes the current section and applies it to jt
		jc end
		mov.b &section, r12
		add r12, r12
		mov jt(r12), r0

song:		nop
		call #play_note ;plays note 
		mov #0, &section ;sets gap between each note
		jmp end
	
sos:		nop
		call #toggle_SOS
		mov.b r12, &changed ;moves 1 into changed meaning that the state has changed
		mov #4, &section
		jmp end
	
low:		nop
		call #siren_low 	;calls to activate low siren sound and led glow
		mov.b r12, &changed
		cmp #3, &reps		;makes sure that the siren low is called 25 times
		jn set_high		;sets the next state to be the high siren
		mov #4,  &section	;if reps < 25, next state is set to off then to low siren
		jmp end
		
high:		nop
		call #siren_high 	; calls for the high sirend activation
		mov.b r12, &changed
		mov #2, &section 	; sets the low siren for the next state
		jmp end

off:		nop
		call #toggle_off 	;toggles to set the led and buzzer off as needed
		mov.b r12, &changed
		cmp #1, &count_on 	;checks if the sos is enabled
		jz set_count_on		;jumps to set the next section to sos if enabled

		mov #2, &section ;sets next section to low
		jmp end
	
set_high:	nop
		mov #3, &section	;sets to high siren
		jmp end
	
set_count_on:	nop
		mov #1, &section 	;sets the next state to sos
		jmp end
	
	
end:		nop
		mov.b &changed, &led_changed
		call #led_update
		pop r0
	
