# makfile configuration
CFLAGS          = -mmcu=msp430g2553 -I h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS		= msp430-elf-as

all: lab2.elf 

#additional rules for files
lab2.elf: p2_interrupt_handler.o led.o switches.o stateMachines.o wdInterruptHandler.o buzzer.o off.o main.o lib/libTimer.a 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: lab2.elf
	msp430loader.sh lab2.elf

clean:
	rm -f *.o *.elf
