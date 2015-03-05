Use the following website to generate code for bandpass filters:
http://www-users.cs.york.ac.uk/~fisher/mkfilter/trad.html
with input parameters:
1) Butterworth/Bandpass
2) N/A
3) 1
4) 8000
5) *Dependent on intended bandpass filter


Objective: produce configurable audio filter system.
Details:
*8-bit PCM audio at 8000Hz fed to virtual serial port (via UART)
*filtered with 4 different band-pass filter
*sent back over serial port
*switch between filters using capacitive buttons, indicated by the LEDs
*must be real-time
*modularize the code into different .c and .h files

***BE MINDFUL OF CODE SIZE, ENERGY USAGE, AND PERFORMANCE

Step 1: get the UART working
-enable clockrate/enable uart
	1885
	SIM_SCGC4 (p340)
-decide baudrate (p1904, 1980)
	UART baud rate = UART module clock / (16 × (SBR[12:0] + BRFD))
	115200 = 50MHz / (16 x (SBR[12:0] + 0)) --> SRB[12:0] ~= 27
-enable trasmitting (p1909)
-enable pin
	PORTx_PCRn field descriptions (p310)
	ALT3 (p275)

Step 2: get the capacitive buttons/LEDs cooperating
Step 3: implement band-pass filter code
Step 4: integrate systems and test


Address for port control module (port A): 0x0000_019C 
