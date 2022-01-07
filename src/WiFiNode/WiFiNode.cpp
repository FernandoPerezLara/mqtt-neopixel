#include "WiFiNode.h"

WiFiNode::WiFiNode(const char* ssid, const char* password) {
	this->ssid = ssid;
	this->password = password;
}

void WiFiNode::begin() {
	WiFi.begin(ssid, password);
	
	Serial.printf("Connecting to %s \n", ssid);

	while (WiFi.status() != WL_CONNECTED) { delay(500); }
	Serial.printf("Connected to %s \n\n", ssid);

	WiFi.setAutoReconnect(true);
  	WiFi.persistent(true);
}

bool WiFiNode::isConnected() {
	if (WiFi.status() != WL_CONNECTED) {
		if (connection_lost == false) {
			Serial.printf("\nWiFi connection lost. Reconnecting... \n");
		}

		connection_lost = true;
		
		return false;
	} else {
		if (connection_lost == true) {
			connection_lost = false;
			
			Serial.printf("Connected to %s \n", ssid);
		}
	}

	return true;
}
