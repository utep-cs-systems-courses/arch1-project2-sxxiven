# makfile configuration
CFLAGS          = -mmcu=msp430g2553 -I h		#links file to the h directory (timer.h)
LDFLAGS		= -L/opt/ti/msp430_gcc/include		#direct link

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc 			#gcc for the msp430
AS		= msp430-elf-as				#assembly for msp430

all: lab2.elf 	#file that executes all the executionables together

#additional rules for files
lab2.elf: p2_interrupt_handler.o led.o switches.o stateMachines.o wdInterruptHandler.o buzzer.o off.o states.o main.o lib/libTimer.a 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: lab2.elf
	msp430loader.sh lab2.elf 			#loader loads .elf onto addresses in msp430

clean:
	rm -f *.o *.elf					#cleans the directory
