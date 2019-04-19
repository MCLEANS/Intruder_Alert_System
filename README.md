# INTRUDER ALARM SYSTEM

### COMPONENTS
	ARDUINO UNO
	16X2 LCD DISPLAY
	3X4 KEYPAD
	ULRASONIC SENSOR
	BUZZER

### PIN CONFIGURATION
	ARDUINO 	LCD
	VCC 		VCC
	GND			GND
	A5			SCL
	A4			SDA


	ARDUINO    KEYPAD
	ROWS->D6 TO D8
	COLUMNS->D2 TO D5

	ARDUINO		ULTRASONIC
	VCC			VCC
	GND			GND
	D10			TRIG
	D11			ECHO


	ARDUINO 	BUZZER
	D9			+ve
	GND			-ve

### OPERATION
The system is meant to detect intruders and sound an alarm.
The ultranonic sensor is used to detect for the prescence of an obstacle within the vicinity.When an object is detected the buzzer is turned on to sound an alarm. The alarm will stay on until a de-activation key is entered using the keypad. The LCD screen is used to display the current status of the  system.
