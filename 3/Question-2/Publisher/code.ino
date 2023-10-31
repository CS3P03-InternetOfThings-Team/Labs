#include <WiFi.h>
#include <PubSubClient.h>

const int MOTION_SENSOR_PIN = 17;
const char* ssid = "CHURRO";
const char* password = "12345678";
const char* mqtt_broker = "192.168.1.40"; // MacBook Pro de Gabriel
const char* topic = "sensors/motion";
const char* mqttClientId = "ESP32-S";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void connectToWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.print("Connected. My IP is: ");
  Serial.println(WiFi.localIP());
}

void connectToBroker() {
  client.setServer(mqtt_broker, mqtt_port);
  while (!client.connected()) {
    Serial.printf("The client %s connects to the public mqtt broker\n", mqttClientId);
    if (client.connect(mqttClientId)) {
        Serial.println("Public emqx mqtt broker connected");
    } else {
        Serial.print("failed with state ");
        Serial.println(client.state());
        delay(2000);
    }
  }
  client.publish(topic, "{\"type\":\"setup\",\"msg\":\"movement sensor connected\"}");
}

void reconnectToBroker() {
  while (!client.connected()) {
    Serial.println("Reconnecting to broker...");
    if (client.connect(mqttClientId)) {
      Serial.println("Connected!");
      client.publish(topic, "{\"type\":\"recovery\",\"description\":\"movement sensor reconnected\"}");
    } else {
      Serial.print("Reconnection failed, rc=");
      Serial.println(client.state());
      Serial.println("Trying again in 5 seconds");
      delay(5000);
    }
  }
}

void publishMessage(String type, String description) {
  String m1 = "{\"type\":\"";
  String m2 = "\",\"description\":\"";
  String m3 = "\"}";
  String message = m1 + type + m2 + description + m3;
  client.publish(topic, message.c_str());
}

void setup() {
  Serial.begin(115200);
  pinMode(MOTION_SENSOR_PIN, INPUT_PULLUP);
  connectToWiFi();
  connectToBroker();
}

bool moving = false;

void loop() {
  if (!client.connected()) {
    reconnectToBroker();
  }
  int val = digitalRead(MOTION_SENSOR_PIN);
  if (moving == false && val == HIGH) {
    moving = true;
    Serial.println("Motion started");
    String s1 = "movement at ";
    String s2 = " seconds";
    publishMessage(String("reading"), s1 + (millis() / 1000) + s2);
  } else if (val == LOW) {
    moving = false;
  }
}
