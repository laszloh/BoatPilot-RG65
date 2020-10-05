EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Transistor_FET:BUK7880-55A Q1
U 1 1 5F70AE46
P 3750 1850
F 0 "Q1" V 3999 1850 50  0000 C CNN
F 1 "BUK7880-55A" V 4090 1850 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-252-2" H 3950 1775 50  0001 L CIN
F 3 "https://assets.nexperia.com/documents/data-sheet/BUK7880-55A.pdf" H 3750 1850 50  0001 L CNN
	1    3750 1850
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R1
U 1 1 5F70BC28
P 3150 1350
F 0 "R1" H 3209 1396 50  0000 L CNN
F 1 "1M" H 3209 1305 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" H 3150 1350 50  0001 C CNN
F 3 "~" H 3150 1350 50  0001 C CNN
	1    3150 1350
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5F70D045
P 2450 1200
F 0 "J1" H 2368 1417 50  0000 C CNN
F 1 "Conn_01x02" H 2368 1326 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2450 1200 50  0001 C CNN
F 3 "~" H 2450 1200 50  0001 C CNN
	1    2450 1200
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 5F70E466
P 4600 1200
F 0 "J2" H 4680 1192 50  0000 L CNN
F 1 "Conn_01x02" H 4680 1101 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4600 1200 50  0001 C CNN
F 3 "~" H 4600 1200 50  0001 C CNN
	1    4600 1200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Reed SW1
U 1 1 5F710ACD
P 3150 1750
F 0 "SW1" V 3196 1665 50  0000 R CNN
F 1 "SW_Reed" V 3105 1665 50  0000 R CNN
F 2 "Button_Switch_SMD:SW_SPST_REED_CT10-XXXX-G2" H 3150 1750 50  0001 C CNN
F 3 "~" H 3150 1750 50  0001 C CNN
	1    3150 1750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2650 1200 3150 1200
Wire Wire Line
	3150 1200 3150 1250
Wire Wire Line
	3150 1450 3150 1550
Wire Wire Line
	3150 1550 3750 1550
Wire Wire Line
	3750 1550 3750 1650
Wire Wire Line
	3150 1200 4400 1200
Connection ~ 3150 1200
Connection ~ 3150 1550
Wire Wire Line
	2650 1300 2800 1300
Wire Wire Line
	2800 1300 2800 1950
Wire Wire Line
	2800 1950 3150 1950
Wire Wire Line
	3150 1950 3550 1950
Connection ~ 3150 1950
Wire Wire Line
	3950 1950 4200 1950
Wire Wire Line
	4200 1950 4200 1300
Wire Wire Line
	4200 1300 4400 1300
$EndSCHEMATC
