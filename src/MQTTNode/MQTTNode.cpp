#include "MQTTNode.h"

MQTTNode::MQTTNode(const char* broker, int port, const char* username, const char* password, const char* name) {
	this->broker = broker;
	this->port = port;
	this->username = username;
	this->password = password;
	this->name = name;
}

void MQTTNode::begin(void (*callback)(char*, byte*, unsigned int)) {
	client.setClient(espClient);
	client.setServer(broker, port);
	client.setCallback(callback);

	Serial.printf("Connecting to the MQTT broker with address %s \n", broker);

	while (!client.connected()) {
		if (client.connect(name, username, password)) {
			Serial.printf("Connected to the MQTT broker \n\n");
		} else {
			delay(500);
		}
	}
}

void MQTTNode::suscribe(const char* topic) {
	char* concat = (char*) malloc(strlen(topic) + strlen(name) + 1);
	
	strcpy(concat, name);
	strcat(concat, "/");
	strcat(concat, topic);
	
	client.subscribe(concat);

	Serial.printf("Subscribed to topic %s \n", concat);
}

bool MQTTNode::isConnected() {
	if (!client.connected()) {
		if (!client.connect(name, username, password)) {
			if (connection_lost == false) {
				Serial.printf("\nMQTT broker connection lost. Reconnecting...\n");
			}

			connection_lost = true;
		}

		return false;
	} else {
		if (connection_lost == true) {
			connection_lost = false;
			
			Serial.printf("Connected to the MQTT broker \n");
		}
	}

	return true;
}

void MQTTNode::publish(const char* topic, const char* payload) {
	Serial.printf("Message sent: %s %s \n", topic, payload);
	
	client.publish(topic, payload);
}

void MQTTNode::loop() {
	client.loop();
}

struct Payload MQTTNode::getPayload(char* topic, byte* payload, unsigned int length) {
	struct Payload message;

	message.topic = (char *) malloc(sizeof(char) * (strlen(topic) + 1));
	message.payload = (char *) malloc(sizeof(char) * (length + 1));

	strcpy(message.topic, topic);
	memcpy(message.payload, (char *) payload, length);
	message.payload[length] = '\0';

	Serial.printf("\nNew message received \n");
	Serial.printf("- Topic: %s \n", message.topic);
	Serial.printf("- Payload: %s \n", message.payload);

	return message;
}
