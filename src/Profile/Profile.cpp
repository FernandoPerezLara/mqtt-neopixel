#include "Profile.h"

void Profile::begin() {
	for (unsigned int i = 0; i < controllers.size(); i++) {
		controllers[i + 1]->begin();
	}

	defaultEffect();
}

void Profile::setBrightness(int brightness) {
	for (unsigned int i = 0; i < controllers.size(); i++) {
		controllers[i + 1]->setBrightness(brightness);
	}
}

void Profile::setPixelColor(int x, int y, int color[3]) {
	int controller = position_map[y][x][0];
	int position = position_map[y][x][1];

	if (controller != 0) {
		controllers[controller]->setPixelColor(position, color);
	}
}

void Profile::show() {
	for (unsigned int i = 0; i < controllers.size(); i++) {
		controllers[i + 1]->show();
	}
}

void Profile::defaultEffect() {
	int color[3] = {0, 0, 0};

	for (int i = 0; i < 87; i++) {
		for (int j = 0; j < 80; j++) {
			color[0] = i * 255 / 87;
			color[1] = j * 255 / 80;
			color[2] = (i + j) * 255 / (87 + 80);

			setPixelColor(i, j, color);
		}
	}

	show();
}

void Profile::onWiFiDisconnect() {
	int red[3] = {255, 0, 0};
	int black[3] = {0, 0, 0};

	setPixelColor(0, 0, red);
	delay(2000);
	setPixelColor(0, 0, black);
	delay(1000);
}

void Profile::onMQTTDisconnect() {
	int orange[3] = {255, 127, 0};
	int black[3] = {0, 0, 0};

	setPixelColor(0, 0, orange);
	delay(2000);
	setPixelColor(0, 0, black);
	delay(1000);
}
