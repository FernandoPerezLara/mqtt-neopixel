#include "Controller.h"

Controller::Controller(int pin, int strip_length, int brightness) {
	this->pin = pin;
	this->strip_length = strip_length;
	this->brightness = brightness;
}

void Controller::begin() {
	strip = new Adafruit_NeoPixel(strip_length, pin, NEO_GRB + NEO_KHZ800);
	
	strip->begin();

	setBrightness(brightness);
}

void Controller::setBrightness(int brightness) {
	strip->setBrightness(brightness);
	strip->show();
}

void Controller::setPixelColor(int pixel, int color[3]) {
	strip->setPixelColor(pixel, strip->Color(color[0], color[1], color[2]));
}

void Controller::show() {
	strip->show();
}
