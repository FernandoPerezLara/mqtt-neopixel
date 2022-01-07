#ifndef WiFiNode_h
#define WiFiNode_h

#include "ESP8266WiFi.h"

class WiFiNode {
	public:
		WiFiNode(const char* ssid, const char* password);

		void begin();
		bool isConnected();

	private:
		const char* ssid;
		const char* password;
		
		bool connection_lost = false;
};

#endif
