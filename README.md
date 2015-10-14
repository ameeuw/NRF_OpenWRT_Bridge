# NRF OpenWRT Bridge
Connect an openWRT powererd router to a NRF 2.4 GHz mesh network with this adapter.

Included are files for the printed circuit board (PCB) and software for forwarding messages and sending specific commands.
Additionally a 433 MHz RF-sender and 38 kHz IR-leds can be connected to enable the device to control TV- and stereo-sets and RF controlled outlets.

<img src="https://raw.githubusercontent.com/ameeuw/NRF_OpenWRT_Bridge/master/hardware/board.png" alt="NRF Node PCB" width=200></img><img src="https://github.com/ameeuw/NRF_OpenWRT_Bridge/blob/master/hardware/pcb_frame.png" alt="PCB holding frame" width=200></img>

----------------------------------------

Node broadcasts if button is pressed at boottime:
UUID + 32 Bit Payload

Payload: 

| Bit | Meaning |
|:---:|:--------|
| 1 | Role (0 master/bridge; 1 slave/node) |
| 2-5 | Number of services (0-16) |
| 6  | DMX Passthrough (64 channels, 8 bit per channel) |
| 7  | Infrared (Passthrough (RAW, binary, NEC, SONY, RC5), different devices (Z5500, p2770HD...)) |
| 8  | Radio Frequency 433 MHz (RF-Sockets (passthrough (binary, length etc...))) |
| 9  | Controlled Device (accepts data to handle) |
| 10 | Sensor (emits data) |
| 11 | - |
| 12 | - |
| 13 | - |
| 14 | - |
| 15 | - |
| 16 | - |


| 1 | 2 3 4 5 | 6 | 7 | 8 | 9 | 10 | 11 12 13 14 15 16 |
|:-:|:-------:|:-:|:-:|:-:|:-:|:--:|:-----------------:|
|Role	|	# of Services	|	DMX	|	IR	|	RF	|	Con	|	Sen	|


