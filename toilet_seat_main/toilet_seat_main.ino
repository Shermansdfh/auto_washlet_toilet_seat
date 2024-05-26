#include "seat_opener.h"
#include "water_pump.h"
#include "tube_control.h"
#include <Arduino_APDS9960.h>
#include <ezButton.h>

#define VRX_PIN  A13 
#define VRY_PIN  A14
#define SW_PIN   A15

int x_val = 0, y_val = 0, b_val = 0;
ezButton button(SW_PIN);

void setup() {
	Serial.begin(9600);

	seat_opener.init();
	water_pump.init();
	tube_controller.init();
	button.setDebounceTime(50);
	
    if (!APDS.begin()) {
		Serial.println("failed to initialize device! Please check your wiring.");
	}
	else {
		Serial.println("Detecting gestures ...");
	}
}

void loop() {
	button.loop();

	x_val = analogRead(VRX_PIN);
	y_val = analogRead(VRY_PIN);
	b_val = button.getState();

	if (button.isPressed()) {
		Serial.println("BUTTON: The button is pressed");
		// TODO do something here
	}

	if (button.isReleased()) {
		Serial.println("BUTTON: The button is released");
		// TODO do something here
	}

	if (APDS.gestureAvailable()) {
		int gesture = APDS.readGesture();

		switch (gesture) {
		case GESTURE_UP:
			Serial.println("GESTURE: Detected UP gesture");
			break;
		case GESTURE_DOWN:
			Serial.println("GESTURE: Detected DOWN gesture");
			break;
		case GESTURE_LEFT:
			Serial.println("GESTURE: Detected LEFT gesture");
			break;
		case GESTURE_RIGHT:
			Serial.println("GESTURE: Detected RIGHT gesture");
			break;
		default:
			// ignore
			break;
		}
  	}

	if (APDS.proximityAvailable()) {
		// - 0   => close
		// - 255 => far
		// - -1  => error
		int proximity = APDS.readProximity();

		// print value to the Serial Monitor
		Serial.println(proximity);
	}
}
