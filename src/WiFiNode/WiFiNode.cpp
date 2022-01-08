#include "WiFiNode.h"

WiFiNode::WiFiNode(const char* ssid, const char* password) {
	this->ssid = ssid;
	this->password = password;
}

void WiFiNode::begin() {
	Serial.printf("Connecting to %s \n", ssid);
	WiFi.begin(ssid, password);

	WiFi.setAutoReconnect(true);
  	WiFi.persistent(true);
}

bool WiFiNode::isConnected() {
	if (WiFi.status() == WL_CONNECTED) {
		if (is_connected == false) {
			Serial.printf("Connected to %s \n", ssid);

			is_connected = true;
		}
	} else {
		if (is_connected == true) {
			Serial.printf("WiFi connection lost. Reconnecting... \n");

			is_connected = false;
		}

		return false;
	}

	return true;
}
