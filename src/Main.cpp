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
	Serial.printf("\nSerial port connection established \n");

	wifiNode.begin();
	mqttNode.begin(callback);

	mqttNode.addTopic("kallax/#");

	profile.begin();
}

void callback(char* topic, byte* payload, unsigned int length) {
	struct Payload message = mqttNode.getPayload(topic, payload, length);

	if (strcmp(message.topic, "node1/kallax/reset") == 0) {
		Serial.printf("Resetting the node \n");
		ESP.restart();
	}
}

// unsigned long previousTime = 0;

void loop() {
	// if (millis() - previousTime >= 5000) {
	// 	previousTime = millis();

	// 	Serial.printf("\nPrueba\n");
	// }

	bool wifi_connected = wifiNode.isConnected();
	bool mqtt_connected = mqttNode.isConnected();

	if (wifi_connected == false || mqtt_connected == false) {
		
	}

	mqttNode.loop();
}
