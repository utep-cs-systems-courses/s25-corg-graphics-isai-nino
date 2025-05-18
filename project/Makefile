# makefile configuration
OBJS    = main.o switches.o stateMachine.o ball.o bricks.o buzzer.o platform.o set_boundaries_s.o
CPU     = msp430g2553
CFLAGS  = -mmcu=${CPU} -Os -I../h
LDFLAGS = -L../lib -L/opt/ti/msp430_gcc/include/

# switch the compiler
CC = msp430-elf-gcc
AS = msp430-elf-gcc -mmcu=${CPU} -c

all: game.elf

# additional rules for files
game.elf: ${OBJS}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load: game.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf *~
