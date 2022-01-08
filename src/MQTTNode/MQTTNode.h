#ifndef MQTTNode_h
#define MQTTNode_h

#include "ESP8266WiFi.h"
#include "PubSubClient.h"

struct Payload {
	char* topic;
	char* payload;
};

class MQTTNode {
	public:
		MQTTNode(const char* broker, int port, const char* username, const char* password, const char* name);

		void begin(void (*callback)(char*, byte*, unsigned int));
		void addTopic(const char* topic);
		void suscribe();
		bool isConnected();
		void publish(const char* topic, const char* payload);
		void loop();
		struct Payload getPayload(char* topic, byte* payload, unsigned int length);

	private:
		WiFiClient espClient;
		PubSubClient client;
		
		const char* broker;
		int port;
		const char* username;
		const char* password;
		const char* name;

		char** topics;
		int topics_length = 0;

		bool is_connected = false;
};

#endif
