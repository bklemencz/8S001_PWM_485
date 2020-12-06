EESchema Schematic File Version 4
LIBS:STM8_001_PWM_485-cache
EELAYER 26 0
EELAYER END
$Descr User 8268 5827
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
L Interface_UART:SP3485EN U3
U 1 1 5FB3C76C
P 5250 3200
F 0 "U3" H 5000 3550 50  0000 C CNN
F 1 "SP3485EN" H 5500 3550 50  0000 C CNN
F 2 "KiCad/kicad-footprints/Package_SO.pretty:SOIC-8_3.9x4.9mm_P1.27mm" H 6300 2850 50  0001 C CIN
F 3 "http://www.icbase.com/pdf/SPX/SPX00480106.pdf" H 5250 3200 50  0001 C CNN
	1    5250 3200
	1    0    0    -1  
$EndComp
$Comp
L STM8_001_PWM_485-rescue:STM8S001J3M-BK_Common U2
U 1 1 5FB3C773
P 3200 2475
F 0 "U2" H 2950 2825 50  0000 C CNN
F 1 "STM8S001J3M" H 3500 2825 50  0000 C CNN
F 2 "KiCad/kicad-footprints/Package_SO.pretty:SOIC-8_3.9x4.9mm_P1.27mm" H 3250 3025 50  0001 L CNN
F 3 "https://www.st.com/resource/en/datasheet/stm8s001j3.pdf" H 3100 2575 50  0001 C CNN
	1    3200 2475
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C3
U 1 1 5FB3C77A
P 2700 2875
F 0 "C3" H 2792 2921 50  0000 L CNN
F 1 "1u" H 2792 2830 50  0000 L CNN
F 2 "KiCad/kicad-footprints/Capacitor_SMD.pretty:C_0805_2012Metric" H 2700 2875 50  0001 C CNN
F 3 "~" H 2700 2875 50  0001 C CNN
	1    2700 2875
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 2675 2700 2675
Wire Wire Line
	2700 2675 2700 2775
Wire Wire Line
	2700 2975 2700 3025
Wire Wire Line
	3200 2875 3200 3025
Wire Wire Line
	3200 1925 3200 2075
Wire Wire Line
	5250 2700 5250 2800
$Comp
L power:GND #PWR0101
U 1 1 5FB3C78D
P 5250 3700
F 0 "#PWR0101" H 5250 3450 50  0001 C CNN
F 1 "GND" H 5255 3527 50  0000 C CNN
F 2 "" H 5250 3700 50  0001 C CNN
F 3 "" H 5250 3700 50  0001 C CNN
	1    5250 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3600 5250 3700
$Comp
L power:GND #PWR0102
U 1 1 5FB3C794
P 2950 3175
F 0 "#PWR0102" H 2950 2925 50  0001 C CNN
F 1 "GND" H 2955 3002 50  0000 C CNN
F 2 "" H 2950 3175 50  0001 C CNN
F 3 "" H 2950 3175 50  0001 C CNN
	1    2950 3175
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 3025 2950 3025
Wire Wire Line
	2950 3175 2950 3025
Connection ~ 2950 3025
Wire Wire Line
	2950 3025 3200 3025
Wire Wire Line
	4850 3100 4750 3100
Wire Wire Line
	4750 3300 4850 3300
Wire Wire Line
	3600 2375 3900 2375
Wire Wire Line
	3600 2475 3900 2475
Text Label 3700 2475 0    50   ~ 0
SWIM_PWM2
Wire Wire Line
	4750 3100 4750 3200
Connection ~ 4750 3200
Wire Wire Line
	4750 3200 4750 3300
Text Label 6250 3100 0    50   ~ 0
A
Text Label 6250 3300 0    50   ~ 0
B
Wire Wire Line
	1000 2750 1100 2750
Wire Wire Line
	1100 2750 1100 2650
$Comp
L power:GND #PWR0103
U 1 1 5FB3C7F1
P 1100 3400
F 0 "#PWR0103" H 1100 3150 50  0001 C CNN
F 1 "GND" H 1105 3227 50  0000 C CNN
F 2 "" H 1100 3400 50  0001 C CNN
F 3 "" H 1100 3400 50  0001 C CNN
	1    1100 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 3300 1100 3300
Wire Wire Line
	1100 3300 1100 3400
Wire Wire Line
	1000 2850 1400 2850
Wire Wire Line
	1000 3200 1400 3200
Text Label 1350 3200 0    50   ~ 0
A
Text Label 1350 2850 0    50   ~ 0
B
Wire Wire Line
	3600 2575 3900 2575
Wire Wire Line
	2800 2475 2400 2475
Text Label 2400 2475 0    50   ~ 0
PWM3
Wire Wire Line
	2800 2375 2400 2375
Text Label 2400 2375 0    50   ~ 0
BTN
Text Label 3700 2575 0    50   ~ 0
PWM1
$Comp
L Device:C_Small C2
U 1 1 5FB3C81D
P 3525 1075
F 0 "C2" H 3617 1121 50  0000 L CNN
F 1 "10u" H 3617 1030 50  0000 L CNN
F 2 "KiCad/kicad-footprints/Capacitor_SMD.pretty:C_1206_3216Metric" H 3525 1075 50  0001 C CNN
F 3 "~" H 3525 1075 50  0001 C CNN
	1    3525 1075
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5FB3C824
P 2425 1075
F 0 "C1" H 2517 1121 50  0000 L CNN
F 1 "10u" H 2517 1030 50  0000 L CNN
F 2 "KiCad/kicad-footprints/Capacitor_SMD.pretty:C_1206_3216Metric" H 2425 1075 50  0001 C CNN
F 3 "~" H 2425 1075 50  0001 C CNN
	1    2425 1075
	1    0    0    -1  
$EndComp
Wire Wire Line
	2125 925  2425 925 
Wire Wire Line
	2425 975  2425 925 
Connection ~ 2425 925 
Wire Wire Line
	3525 975  3525 925 
Connection ~ 3525 925 
Wire Wire Line
	3525 925  3925 925 
Wire Wire Line
	2425 1175 2425 1375
Wire Wire Line
	2425 1375 3025 1375
Wire Wire Line
	3025 1375 3025 1225
Wire Wire Line
	3025 1375 3525 1375
Wire Wire Line
	3525 1375 3525 1175
Connection ~ 3025 1375
$Comp
L power:GND #PWR0104
U 1 1 5FB3C839
P 3025 1375
F 0 "#PWR0104" H 3025 1125 50  0001 C CNN
F 1 "GND" H 3030 1202 50  0000 C CNN
F 2 "" H 3025 1375 50  0001 C CNN
F 3 "" H 3025 1375 50  0001 C CNN
	1    3025 1375
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5FB3C84B
P 6825 1875
F 0 "SW1" V 6779 2023 50  0000 L CNN
F 1 "Sw" V 6870 2023 50  0000 L CNN
F 2 "KiCad/kicad-footprints/Button_Switch_SMD.pretty:SW_SPST_CK_RS282G05A3" H 6825 2075 50  0001 C CNN
F 3 "" H 6825 2075 50  0001 C CNN
	1    6825 1875
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R1
U 1 1 5FB3C852
P 6825 1375
F 0 "R1" H 6884 1421 50  0000 L CNN
F 1 "10K" H 6884 1330 50  0000 L CNN
F 2 "KiCad/kicad-footprints/Resistor_SMD.pretty:R_0805_2012Metric" H 6825 1375 50  0001 C CNN
F 3 "~" H 6825 1375 50  0001 C CNN
	1    6825 1375
	1    0    0    -1  
$EndComp
Wire Wire Line
	6825 1125 6825 1275
Wire Wire Line
	6825 1475 6825 1575
$Comp
L power:GND #PWR0105
U 1 1 5FB3C861
P 6825 2175
F 0 "#PWR0105" H 6825 1925 50  0001 C CNN
F 1 "GND" H 6830 2002 50  0000 C CNN
F 2 "" H 6825 2175 50  0001 C CNN
F 3 "" H 6825 2175 50  0001 C CNN
	1    6825 2175
	1    0    0    -1  
$EndComp
Wire Wire Line
	6825 2075 6825 2175
Wire Wire Line
	6825 1575 6225 1575
Connection ~ 6825 1575
Wire Wire Line
	6825 1575 6825 1675
Text Label 6225 1575 0    50   ~ 0
BTN
Wire Wire Line
	5650 3100 6300 3100
Wire Wire Line
	5650 3300 6300 3300
$Comp
L power:+5V #PWR0106
U 1 1 5FB3C887
P 5250 2700
F 0 "#PWR0106" H 5250 2550 50  0001 C CNN
F 1 "+5V" H 5265 2873 50  0000 C CNN
F 2 "" H 5250 2700 50  0001 C CNN
F 3 "" H 5250 2700 50  0001 C CNN
	1    5250 2700
	1    0    0    -1  
$EndComp
NoConn ~ 4850 3400
Wire Wire Line
	4850 3000 4450 3000
Text Label 4450 3000 0    50   ~ 0
485_Rx
$Comp
L power:GND #PWR0107
U 1 1 5FB3E4CC
P 4550 3300
F 0 "#PWR0107" H 4550 3050 50  0001 C CNN
F 1 "GND" H 4555 3127 50  0000 C CNN
F 2 "" H 4550 3300 50  0001 C CNN
F 3 "" H 4550 3300 50  0001 C CNN
	1    4550 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 3200 4550 3300
Wire Wire Line
	4550 3200 4750 3200
Text Label 3650 2375 0    50   ~ 0
485_Rx
$Comp
L Regulator_Linear:L78L05_SOT89 U1
U 1 1 5FB410FB
P 3025 925
F 0 "U1" H 3025 1167 50  0000 C CNN
F 1 "L78L05_SOT89" H 3025 1076 50  0000 C CNN
F 2 "KiCad/kicad-footprints/Package_TO_SOT_SMD.pretty:SOT-89-3_Handsoldering" H 3025 1125 50  0001 C CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/15/55/e5/aa/23/5b/43/fd/CD00000446.pdf/files/CD00000446.pdf/jcr:content/translations/en.CD00000446.pdf" H 3025 875 50  0001 C CNN
	1    3025 925 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2425 925  2725 925 
Wire Wire Line
	3325 925  3525 925 
$Comp
L power:VCC #PWR0108
U 1 1 5FB4562A
P 1100 2650
F 0 "#PWR0108" H 1100 2500 50  0001 C CNN
F 1 "VCC" H 1117 2823 50  0000 C CNN
F 2 "" H 1100 2650 50  0001 C CNN
F 3 "" H 1100 2650 50  0001 C CNN
	1    1100 2650
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0109
U 1 1 5FB456E6
P 2125 875
F 0 "#PWR0109" H 2125 725 50  0001 C CNN
F 1 "VCC" H 2142 1048 50  0000 C CNN
F 2 "" H 2125 875 50  0001 C CNN
F 3 "" H 2125 875 50  0001 C CNN
	1    2125 875 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2125 925  2125 875 
$Comp
L power:+5V #PWR0110
U 1 1 5FB46098
P 3925 875
F 0 "#PWR0110" H 3925 725 50  0001 C CNN
F 1 "+5V" H 3940 1048 50  0000 C CNN
F 2 "" H 3925 875 50  0001 C CNN
F 3 "" H 3925 875 50  0001 C CNN
	1    3925 875 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3925 875  3925 925 
$Comp
L power:+5V #PWR0111
U 1 1 5FB46A97
P 6825 1125
F 0 "#PWR0111" H 6825 975 50  0001 C CNN
F 1 "+5V" H 6840 1298 50  0000 C CNN
F 2 "" H 6825 1125 50  0001 C CNN
F 3 "" H 6825 1125 50  0001 C CNN
	1    6825 1125
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0112
U 1 1 5FB46B4D
P 3200 1925
F 0 "#PWR0112" H 3200 1775 50  0001 C CNN
F 1 "+5V" H 3215 2098 50  0000 C CNN
F 2 "" H 3200 1925 50  0001 C CNN
F 3 "" H 3200 1925 50  0001 C CNN
	1    3200 1925
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 5FB47751
P 800 2750
F 0 "J3" H 720 2967 50  0000 C CNN
F 1 "In1" H 720 2876 50  0000 C CNN
F 2 "KiCad/kicad-footprints/TerminalBlock_Phoenix.pretty:TerminalBlock_Phoenix_PT-1,5-2-3.5-H_1x02_P3.50mm_Horizontal" H 800 2750 50  0001 C CNN
F 3 "~" H 800 2750 50  0001 C CNN
	1    800  2750
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 5FB48142
P 800 3200
F 0 "J4" H 720 3417 50  0000 C CNN
F 1 "In2" H 720 3326 50  0000 C CNN
F 2 "KiCad/kicad-footprints/TerminalBlock_Phoenix.pretty:TerminalBlock_Phoenix_PT-1,5-2-3.5-H_1x02_P3.50mm_Horizontal" H 800 3200 50  0001 C CNN
F 3 "~" H 800 3200 50  0001 C CNN
	1    800  3200
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5FB482CA
P 800 1200
F 0 "J1" H 720 1417 50  0000 C CNN
F 1 "PWM1" H 720 1326 50  0000 C CNN
F 2 "KiCad/kicad-footprints/TerminalBlock_Phoenix.pretty:TerminalBlock_Phoenix_PT-1,5-2-3.5-H_1x02_P3.50mm_Horizontal" H 800 1200 50  0001 C CNN
F 3 "~" H 800 1200 50  0001 C CNN
	1    800  1200
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 5FB48374
P 800 1700
F 0 "J2" H 720 1917 50  0000 C CNN
F 1 "PWM2" H 720 1826 50  0000 C CNN
F 2 "KiCad/kicad-footprints/TerminalBlock_Phoenix.pretty:TerminalBlock_Phoenix_PT-1,5-2-3.5-H_1x02_P3.50mm_Horizontal" H 800 1700 50  0001 C CNN
F 3 "~" H 800 1700 50  0001 C CNN
	1    800  1700
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5FB485AE
P 1150 1850
F 0 "#PWR0113" H 1150 1600 50  0001 C CNN
F 1 "GND" H 1155 1677 50  0000 C CNN
F 2 "" H 1150 1850 50  0001 C CNN
F 3 "" H 1150 1850 50  0001 C CNN
	1    1150 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 1800 1150 1800
Wire Wire Line
	1150 1800 1150 1850
Wire Wire Line
	1000 1700 1350 1700
Wire Wire Line
	1000 1300 1350 1300
Wire Wire Line
	1000 1200 1350 1200
Text Label 1150 1300 0    50   ~ 0
PWM1
Text Label 1150 1200 0    50   ~ 0
SWIM_PWM2
Text Label 1150 1700 0    50   ~ 0
PWM3
$Comp
L Connector_Generic:Conn_01x03 J5
U 1 1 5FB4B627
P 800 4200
F 0 "J5" H 720 4517 50  0000 C CNN
F 1 "SWIM" H 720 4426 50  0000 C CNN
F 2 "KiCad/kicad-footprints/Connector_PinHeader_2.54mm.pretty:PinHeader_1x03_P2.54mm_Vertical" H 800 4200 50  0001 C CNN
F 3 "~" H 800 4200 50  0001 C CNN
	1    800  4200
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0114
U 1 1 5FB4C3C8
P 1150 4050
F 0 "#PWR0114" H 1150 3900 50  0001 C CNN
F 1 "+5V" H 1165 4223 50  0000 C CNN
F 2 "" H 1150 4050 50  0001 C CNN
F 3 "" H 1150 4050 50  0001 C CNN
	1    1150 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 4100 1150 4100
Wire Wire Line
	1150 4100 1150 4050
$Comp
L power:GND #PWR0115
U 1 1 5FB4D14E
P 1150 4350
F 0 "#PWR0115" H 1150 4100 50  0001 C CNN
F 1 "GND" H 1155 4177 50  0000 C CNN
F 2 "" H 1150 4350 50  0001 C CNN
F 3 "" H 1150 4350 50  0001 C CNN
	1    1150 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 4300 1150 4350
Wire Wire Line
	1000 4300 1150 4300
Wire Wire Line
	1000 4200 1650 4200
Text Label 1200 4200 0    50   ~ 0
SWIM_PWM2
$EndSCHEMATC
