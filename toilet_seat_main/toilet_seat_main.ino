#include "seat_opener.h"
#include "water_pump.h"
#include "tube_control.h"
#include <Arduino_APDS9960.h>
#include <ezButton.h>
#include <Arduino.h>
// #include <cmath>
// #include <map>

#define DEBUG

/******** Define Pin & Create Module Object ********/
#define VRX_PIN  A15
#define VRY_PIN  A14
#define SW_PIN   A13

ezButton button(SW_PIN);

void setup() {
	Serial.begin(9600);
	seat_opener.init();
	water_pump.init();
	tube_controller.init();
	button.setDebounceTime(50);
	
    if (!APDS.begin()) {
		Serial.println("Failed to initialize device! Please check your wiring.");
	} else {
		Serial.println("Detecting gestures ...");
	}
}
/******** End Define Pin & Create Module Object ********/

/******** Initialize Variable ********/
int prevJoystickValueX  = 0, prevJoystickValueY = 0;
bool isPumpingWater = false;
bool isJoystickMovingX = false, isJoystickMovingY = false;
int railServoAngle = 90, tubeServoAngle = 90;
/******** End Initialize Variable ********/

/******** Declare Function Prototype ********/
/******** End Declare Function Prototype ********/

void loop() {
	button.loop();
	int joystickValueX = analogRead(VRX_PIN);
	int joystickValueY = analogRead(VRY_PIN);
	int joystickValueB = button.getState();
	/******** Pump Control ********/
	/*
	 * This section handles the control and operations related to the pump.
     */
/*
    analogWrite(6, 200); 
    digitalWrite(7, LOW);
    digitalWrite(13, HIGH);
*/

	if (button.isPressed()) {
		Serial.println("BUTTON: The button is pressed");
		if (isPumpingWater) {
			water_pump.waterPumpOff();
            isPumpingWater = false;
		} else {
			water_pump.waterPumpOn();
            isPumpingWater = true;
		}
	}

	/******* End Pump Control *******/

	/******** Tube Control ********/
	/*
	 * This section handles the control and operations related to the tube.
     */

	// Check if the joystick is released on the X-axis
	if (abs(joystickValueX - 512) < 100) {
		isJoystickMovingX = false;  // Stop servo movement
		// Serial.println(joystickValueX);
	} else {
		isJoystickMovingX = true;   // Start servo movement
	}

	if (abs(joystickValueY - 512) < 100) {
		isJoystickMovingY = false;  // Stop servo movement
		// Serial.println(joystickValueY);
	} else {
		isJoystickMovingY = true;   // Start servo movement
	}

	// Update the servo position if the joystick is not in the middle position
    /*
    	if (isJoystickMovingX && joystickValueX > 512) {
        railServoAngle += 5;
		tube_controller.tubeForward(railServoAngle);                             // Set the servo position
	} else if (isJoystickMovingX && joystickValueX < 512) {
        railServoAngle -= 5;
		tube_controller.tubeForward(railServoAngle);
    }
    */

	if (isJoystickMovingX) {
		int servoAngle = map(joystickValueX, 0, 1023, 40, 140);  // Map joystick value to servo angle
		tube_controller.tubeForward(servoAngle);                             // Set the servo position
		prevJoystickValueX = joystickValueX;                     // Update the previous joystick value
	}

	if (isJoystickMovingY) {
		int servoAngle = 180 - map(joystickValueY, 0, 1023, 50, 150);  // Map joystick value to servo angle
		tube_controller.tubeRotate(servoAngle);                             // Set the servo position
		prevJoystickValueY = joystickValueY;                     // Update the previous joystick value
	}
    /*
    if (isJoystickMovingY && joystickValueY > 512) {
        tubeServoAngle -= 10;
		tube_controller.tubeRotate(tubeServoAngle);                             // Set the servo position
	} else if (isJoystickMovingY && joystickValueY < 512) {
        tubeServoAngle += 10;
		tube_controller.tubeRotate(tubeServoAngle);
    }
    */

	/******* End Tube Control *******/

	/******** Seat Control ********/
	/*
	 * This section handles the control and operations related to the seat.
     */
	
	if (APDS.gestureAvailable()) {
    	// a gesture was detected, read and print to Serial Monitor
		int gesture = APDS.readGesture();

		switch (gesture) {
			case GESTURE_UP:
				Serial.println("APDS: Up gesture detected");
				seat_opener.openSecondLayer();
				break;

			case GESTURE_DOWN:
				Serial.println("APDS: Down gesture detected");
				seat_opener.closeSecondLayer();
				break;

			case GESTURE_LEFT:
				Serial.println("APDS: Left gesture detected");
				seat_opener.openFirstLayer();
				break;

			case GESTURE_RIGHT:
				Serial.println("APDS: Right gesture detected");
				seat_opener.closeFirstLayer();
				break;

			default:
				// ignore
				break;
		}
	}

	/******* End Seat Control *******/
}
