#ifndef Controller_h
#define Controller_h

#include "Adafruit_NeoPixel.h"

// TODO: Implementar panic
class Controller {
	public:
		Controller(int pin, int strip_length, int brightness);

		void begin();
		void setBrightness(int brightness);
		void setPixelColor(int pixel, int color[3]);
		void show();

	private:
		int pin;
		int strip_length;
		int brightness;
		Adafruit_NeoPixel* strip;
};

#endif
