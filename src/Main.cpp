#include "Arduino.h"

#include "environment.h"

#include "WiFiNode/WiFiNode.h"
#include "MQTTNode/MQTTNode.h"
#include "Profile/Profile.h"

void callback(char* topic, byte* payload, unsigned int length);

WiFiNode wifiNode(WIFI_SSID, WIFI_PASSWORD);
MQTTNode mqttNode(MQTT_BROKER, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD, MQTT_CLIENT_ID);

Profile profile;

void setup() {
	Serial.begin(115200);
	while (!Serial);
	Serial.printf("\nSerial port connection established \n\n");

	wifiNode.begin();
	mqttNode.begin(callback);

	mqttNode.suscribe("kallax/#");

	profile.begin();
}

void callback(char* topic, byte* payload, unsigned int length) {
	struct Payload message = mqttNode.getPayload(topic, payload, length);

	if (strcmp(message.topic, "node1/kallax/reset") == 0) {
		Serial.printf("\nResetting the node \n");
		ESP.restart();
	} else {
		// if (strcmp(message.topic, "node1/kallax/brightness") == 0) {
		// 	if (misc.isNumber(message.payload) && atoi(message.payload) >= 0 && atoi(message.payload) <= 255) {
		// 		Serial.printf("\nBrightness set to to %d \n", atoi(message.payload));
		// 		profile.setBrightness(atoi(message.payload));
		// 	}
	 	// } else if (strcmp(message.topic, "node1/kallax/pixel_color") == 0) {

		// }
	}
}

// unsigned long previousTime = 0;

void loop() {
	// if (millis() - previousTime >= 5000) {
	// 	previousTime = millis();

	// 	Serial.printf("\nPrueba\n");
	// }

	if (wifiNode.isConnected() == false or mqttNode.isConnected() == false) {
		delay(5000);
		
		return;
	}

	mqttNode.loop();
}
