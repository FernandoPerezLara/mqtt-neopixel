#include "MQTTNode.h"

MQTTNode::MQTTNode(const char* broker, int port, const char* username, const char* password, const char* name) {
	this->broker = broker;
	this->port = port;
	this->username = username;
	this->password = password;
	this->name = name;

	this->topics = (char **) malloc(sizeof(char *));
}

void MQTTNode::begin(void (*callback)(char*, byte*, unsigned int)) {
	client.setClient(espClient);
	client.setServer(broker, port);
	client.setCallback(callback);

	Serial.printf("Connecting to the MQTT broker with address %s \n", broker);
	client.connect(name, username, password);
}

void MQTTNode::addTopic(const char* topic) {
	topics = (char **) realloc(topics, sizeof(char *) * (topics_length + 1));
	topics[topics_length] = (char *) malloc(sizeof(char) * strlen(topic));
	
	strcpy(topics[topics_length], topic);

	topics_length += 1;
}

void MQTTNode::suscribe() {
	char* concat = (char*) malloc(sizeof(char));

	for (int i = 0; i < topics_length; i++) {
		concat = (char *) realloc(concat, sizeof(char) * (strlen(topics[i]) + strlen(name) + 1));
		
		strcpy(concat, name);
		strcat(concat, "/");
		strcat(concat, topics[i]);
		
		client.subscribe(concat);

		Serial.printf("Subscribed to topic %s \n", concat);
	}
}

bool MQTTNode::isConnected() {
	if (client.connected()) {
		if (is_connected == false) {
			Serial.printf("Connected to the MQTT broker \n");

			suscribe();

			is_connected = true;
		}
	} else {
		if (!client.connect(name, username, password)) {
			if (is_connected == true) {
				Serial.printf("MQTT broker connection lost. Reconnecting...\n");
				
				is_connected = false;
			}
			
			return false;
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
