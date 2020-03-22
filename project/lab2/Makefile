#makefile configuration
COMMON_OBJECTS	=
CPU		= msp430g2553
CFLAGS		= -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the complier (for the internal make rules)
CC 		= msp430-elf-gcc
AS		= msp430-elf-as

all: button.elf

#additonal rules for files
button.elf: ${COMMON_OBJECTS} p2_interrupt_handler.o led.o switches.o stateMachines.o wdInterruptHandler.o buzzer.o  off.o main.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: button.elf
	msp430loader.sh button.elf

clean:
	rm -f *.o *.elf
