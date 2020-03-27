Project 2 : MSP430 Toy

The following project is for lab 2 which is only intended to create simple
functionality for the msp430. In order to demo, you need acces to all four
buttons. The functionality of each button is explained below.

Button 0:
       Button 0 is the first button from the left. It's functionality is to
       play the message S.O.S by lighting the green LED and sounding the
       buzzer simontanously. Note: the rest of the projects will only utlilize
       the green LED since the red LED of this msp430 is not functional.

Button 1:
       Button 1 is the second from the lft. It's functionality is to play a
       siren. The siren is sounded with to frequencies; one low and one
       high. On the hihg freqeuncy, the green LED is brightly lit. On the low
       frequency, the LED is set to 'glow' and become dimly lit.

Button 2:
       Button 2 is the third from the left. It's functionality is to play the
       Jurrassc Park Theme Song. The song is broken up into eight different
       states within the state machine. This means that in order to disrupt
       the song, one must hold down the last button (which is set to stop all
       state) until the state machine is finished witht that paticular state
       since it plays groups of notes in loops.

Button 3:
       Button 3 is the last from the left. It's functionality is to stop any
       state and make the msp430 silent and dark.

When transitioning between state from buttons 0 - 2, make sure you stop all
before proceeding to the next state by pressing button 3 for the best
preformance and experience. 

The assembly file located with the rest of the files serves as a function. It
is supposed to turn off all of the LED flags, set the delay to the desired
specific value, and sets the buzzer period to 0 when needed.

How to use:

    To load the program onto to the msp430, run 'make load'. In order to clean
    the files run 'make clean'. 

