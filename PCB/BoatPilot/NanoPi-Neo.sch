EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_02x12_Odd_Even J201
U 1 1 5C639A40
P 5800 2500
F 0 "J201" H 5850 3217 50  0000 C CNN
F 1 "GPIO" H 5850 3126 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x12_P2.54mm_Vertical" H 5800 2500 50  0001 C CNN
F 3 "~" H 5800 2500 50  0001 C CNN
	1    5800 2500
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x12 J202
U 1 1 5C639ADD
P 5850 4450
F 0 "J202" H 5800 5050 50  0000 L CNN
F 1 "USB-Audio-IR" V 4550 4150 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x12_P2.54mm_Vertical" H 5850 4450 50  0001 C CNN
F 3 "~" H 5850 4450 50  0001 C CNN
	1    5850 4450
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J203
U 1 1 5C639D5C
P 5950 4750
F 0 "J203" H 5900 4250 50  0000 L CNN
F 1 "Audio-UART" V 5200 4400 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 5950 4750 50  0001 C CNN
F 3 "~" H 5950 4750 50  0001 C CNN
	1    5950 4750
	-1   0    0    1   
$EndComp
$Comp
L Mechanical:MountingHole H201
U 1 1 5C639F41
P 700 7400
F 0 "H201" H 800 7446 50  0000 L CNN
F 1 "MountingHole" H 800 7355 50  0000 L CNN
F 2 "MountingHole:MountingHole_3mm" H 700 7400 50  0001 C CNN
F 3 "~" H 700 7400 50  0001 C CNN
	1    700  7400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H202
U 1 1 5C639F7D
P 700 7600
F 0 "H202" H 800 7646 50  0000 L CNN
F 1 "MountingHole" H 800 7555 50  0000 L CNN
F 2 "MountingHole:MountingHole_3mm" H 700 7600 50  0001 C CNN
F 3 "~" H 700 7600 50  0001 C CNN
	1    700  7600
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H203
U 1 1 5C639FB1
P 1500 7400
F 0 "H203" H 1600 7446 50  0000 L CNN
F 1 "MountingHole" H 1600 7355 50  0000 L CNN
F 2 "MountingHole:MountingHole_3mm" H 1500 7400 50  0001 C CNN
F 3 "~" H 1500 7400 50  0001 C CNN
	1    1500 7400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H204
U 1 1 5C639FE5
P 1500 7600
F 0 "H204" H 1600 7646 50  0000 L CNN
F 1 "MountingHole" H 1600 7555 50  0000 L CNN
F 2 "MountingHole:MountingHole_3mm" H 1500 7600 50  0001 C CNN
F 3 "~" H 1500 7600 50  0001 C CNN
	1    1500 7600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2100 6100 2100
Wire Wire Line
	6100 2000 6200 2000
Wire Wire Line
	6200 2000 6200 2100
Wire Wire Line
	5650 3950 5500 3950
Wire Wire Line
	6200 5050 6150 5050
Wire Wire Line
	5650 5050 5600 5050
Wire Wire Line
	6100 2200 6150 2200
Wire Wire Line
	6150 2200 6150 2600
Wire Wire Line
	6100 2600 6150 2600
Connection ~ 6150 2600
Wire Wire Line
	6150 2600 6150 2900
Wire Wire Line
	6100 2900 6150 2900
Wire Wire Line
	5600 2400 5550 2400
Wire Wire Line
	6350 2300 6100 2300
Wire Wire Line
	6350 2400 6100 2400
Wire Wire Line
	6350 2500 6100 2500
Wire Wire Line
	6350 2700 6100 2700
Wire Wire Line
	6350 2800 6100 2800
Wire Wire Line
	6350 3000 6100 3000
Wire Wire Line
	6350 3100 6100 3100
Wire Wire Line
	5600 2000 5500 2000
Wire Wire Line
	5500 2000 5500 2800
Wire Wire Line
	5500 2800 5600 2800
Connection ~ 5500 2000
Wire Wire Line
	5600 2100 5200 2100
Wire Wire Line
	5600 2200 5200 2200
Wire Wire Line
	5200 2300 5600 2300
Wire Wire Line
	5600 2500 5200 2500
Wire Wire Line
	5600 2600 5200 2600
Wire Wire Line
	5600 2700 5200 2700
Wire Wire Line
	5600 2900 5200 2900
Wire Wire Line
	5600 3000 5200 3000
Wire Wire Line
	5600 3100 5200 3100
Wire Wire Line
	5150 4050 5650 4050
Wire Wire Line
	5150 4150 5650 4150
Wire Wire Line
	5150 4250 5650 4250
Wire Wire Line
	5150 4350 5650 4350
Wire Wire Line
	5150 4450 5650 4450
Wire Wire Line
	5150 4550 5650 4550
Wire Wire Line
	5150 4650 5650 4650
Wire Wire Line
	5150 4750 5650 4750
Wire Wire Line
	5150 4850 5650 4850
Wire Wire Line
	5150 4950 5650 4950
Wire Wire Line
	6200 4950 6150 4950
Wire Wire Line
	6450 4350 6150 4350
Wire Wire Line
	6450 4450 6150 4450
Wire Wire Line
	6450 4550 6150 4550
Wire Wire Line
	6450 4650 6150 4650
Wire Wire Line
	6450 4750 6150 4750
Wire Wire Line
	6450 4850 6150 4850
Text HLabel 5200 2000 0    50   Input ~ 0
3,3V
Text HLabel 7150 2000 2    50   Input ~ 0
5V
Text HLabel 6350 2200 2    50   Input ~ 0
GND
Text HLabel 5200 2100 0    50   Input ~ 0
SDA0
Text HLabel 5200 2200 0    50   Input ~ 0
SCL0
Text HLabel 5200 2300 0    50   Input ~ 0
PG11
Text HLabel 5200 2500 0    50   Input ~ 0
TX2_PA0
Text HLabel 5200 2600 0    50   Input ~ 0
RTS2_PA2
Text HLabel 5200 2700 0    50   Input ~ 0
CTS2_PA3
Text HLabel 6350 2300 2    50   Input ~ 0
TX1
Text HLabel 6350 2400 2    50   Input ~ 0
RX1
Text HLabel 6350 2500 2    50   Input ~ 0
PA6
Text HLabel 6350 2700 2    50   Input ~ 0
RTS1
Text HLabel 6350 2800 2    50   Input ~ 0
CTS1
Text HLabel 5200 2900 0    50   Input ~ 0
MOSI0
Text HLabel 5200 3000 0    50   Input ~ 0
MISO0
Text HLabel 5200 3100 0    50   Input ~ 0
CLK0
Text HLabel 6350 3000 2    50   Input ~ 0
RX2_PA1
Text HLabel 6350 3100 2    50   Input ~ 0
CS0
Wire Wire Line
	5200 2000 5500 2000
Wire Wire Line
	6200 2000 7050 2000
Connection ~ 6200 2000
Wire Wire Line
	6150 2200 6350 2200
Connection ~ 6150 2200
Wire Wire Line
	5550 3250 6150 3250
Wire Wire Line
	6150 3250 6150 2900
Wire Wire Line
	5550 2400 5550 3250
Connection ~ 6150 2900
Wire Wire Line
	5500 3950 5500 3800
Wire Wire Line
	5500 3800 6200 3800
Wire Wire Line
	6200 3800 6200 4950
Wire Wire Line
	6200 3800 7050 3800
Wire Wire Line
	7050 3800 7050 2000
Connection ~ 6200 3800
Connection ~ 7050 2000
Wire Wire Line
	7050 2000 7150 2000
Wire Wire Line
	6150 3250 6850 3250
Wire Wire Line
	6850 3250 6850 5250
Wire Wire Line
	6850 5250 6200 5250
Wire Wire Line
	5600 5250 5600 5050
Connection ~ 6150 3250
Wire Wire Line
	6200 5050 6200 5250
Connection ~ 6200 5250
Wire Wire Line
	6200 5250 5600 5250
Text HLabel 5150 4050 0    50   Input ~ 0
D1P
Text HLabel 5150 4150 0    50   Input ~ 0
D1N
Text HLabel 5150 4250 0    50   Input ~ 0
D2P
Text HLabel 5150 4350 0    50   Input ~ 0
D2N
Text HLabel 5150 4450 0    50   Input ~ 0
PL11_IR
Text HLabel 5150 4550 0    50   Input ~ 0
PA17_SPDIF
Text HLabel 5150 4650 0    50   Input ~ 0
I2S_LRCK
Text HLabel 5150 4750 0    50   Input ~ 0
I2S_BCK
Text HLabel 5150 4850 0    50   Input ~ 0
I2S_DOUT
Text HLabel 5150 4950 0    50   Input ~ 0
I2S_DIN
Text HLabel 6450 4350 2    50   Input ~ 0
MP
Text HLabel 6450 4450 2    50   Input ~ 0
MN
Text HLabel 6450 4550 2    50   Input ~ 0
LR
Text HLabel 6450 4650 2    50   Input ~ 0
LL
Text HLabel 6450 4750 2    50   Input ~ 0
RX0
Text HLabel 6450 4850 2    50   Input ~ 0
TX0
$EndSCHEMATC
