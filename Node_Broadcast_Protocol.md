Node broadcasted wenn Knopf gedrückt bei start:
UUID + 32 Bit Payload

Payload: 

Bit		Meaning

1		Role (0 master/bridge; 1 slave/node)
2-5		Number of services (0-16)
6		DMX Passthrough (64 channels, 8 bit per channel)
7		Infrared (Passthrough (RAW, binary, NEC, SONY, RC5), different devices (Z5500, p2770HD...))
8		Radio Frequency 433 MHz (RF-Sockets (passthrough (binary, length etc...)))
9		Controlled Device (accepts data to handle) 
10		Sensor (emits data)
11		
12
13
14
15
16

-------------------------------------------------------------------------------------------------------------
1	|	2	3	4	5	|	6	|	7	|	8	|	9	|	10	|	11		12		13		14		15	16
-------------------------------------------------------------------------------------------------------------
Role	|	# of Services	|	DMX	|	IR	|	RF	|	Con	|	Sen	|		
-------------------------------------------------------------------------------------------------------------


