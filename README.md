
# Arduino Test Sketches

Hi there, I just wanted to brush up my skills in C and arduino tinkering. 
I'll try to summarize each of these sketches a bit. 



- Blinkenlights:

	PINS 4,5,6 are S(elect)0, S1, S2 (in that order!) of a CD4051, which in turn triggers the LEDS. 
    
- Blinkenlights2:
	Arduino only sends a CLOCK signal now, to a CD4024 which is a 7-stage binary ripple-carry adder that in turn sends the Selects for the 4051.
    