# Embedded_Linux_Homework

What are the frequencies, amplitues and shapes you see on the server outputs?

	Amplitude: 
	- The amplitude represents the maximum value of the signal. 
	- Server output range spans from -5.0 to 5.0. 
	- maximum value is 5.0 and minimum value is -5.0.
	
	Frequency: 
	-The number of oscilations(cycles) that occurs within in time interval.
	- The client recives data from the server every 100ms (0.1 seconds).
	- The frequency of the output is 
	  For 100milliseconds window is 3*100 = 300 HZ. 
	  For 20milliseconds window is  3*20 = 60HZ
			   
   - If we plot the server output against time (with time intervals of 0.1 seconds), 
     using the out1, out2, and out3 values on the y-axis, the resulting graph will resemble a sine wave.

			   
Design decisions,

 Task 1: Reading data from TCP ports
 1) Create 3 sockets to connect to TCP ports (4001,4002,4003).
 2) Once the connections are established read the latest value data from these ports within 100ms window.
 2) Print the retrieved data in the specified JSON format.
 
 Task 2: Modifying Server Behavior Based on out3 Value
 1) Retain Task 1 implementation.
 2) Additionally, implement Tas 2:
    - Create a UDP socket and connect it to UDP port 4000.
	- Read the latest value data from TCP ports (4001,4002,4003) in 20ms window.
	- Define a message structure following the control protocol specification to set frequency and amplitude properties.
    - After reading data from the port3, convert the string data to float data using atof().
	- Modify the server behavior based on the out3 value:
      a) if the out3 value is >= 3.0 set the server's out1 frequency to 1HZ and amplitude value to 8000.
	  b) if the out3 value is < 3.0 set the server's out1 frequency to 2HZ and amplitude value to 4000.
            	
solution Validation:
- Task 1 appears correct because the server data is received as expected and printed in the specified JSON format.
- However, Task 2 requires clarification, as the server does not output any information to the standard output.


