 #include <WiFi.h> 
#include <PubSubClient.h> 
#include <ArduinoJson.h> 
#include <WiFiUdp.h> 
#include <NTPClient.h> 

const char* ssid = "MQTT";
const char* password = "info@134"; 

const char* mqtt_server = "172.16.57.45";
const int mqtt_port = 1883; 
const char* mqtt_topic = "projetodificil"; 

const int buttonPin = 0; 
bool lastButtonState = false; 
bool botao = false; 

WiFiClient espClient; 
PubSubClient client(espClient); 
WiFiUDP ntpUDP; 
NTPClient timeClient(ntpUDP, "pool.ntp.org", -3 * 3600, 60000); 

void callback(char* topic, byte* payload, unsigned int length) {
  String message; 
  for (int i = 0; i < length; i++) {
    message += (char)payload[i]; 
  }

  JsonDocument doc; 
  DeserializationError error = deserializeJson(doc, message); 

  if (!error) { 
    if (doc.containsKey("BOTT")) { 
      bool buttonStatus = doc["BOTT"]; 
      if (buttonStatus) { 
        if (botao) { 
          Serial.println("Sistema Desligado"); 
        } else { 
          Serial.println("Sistema Ligado"); 
        }
        botao = !botao; 
      }
    }
  } else { 
    Serial.println("Erro ao deserializar o JSON"); 
  }
}

void setup_wifi() { 
  delay(10); 
  Serial.println(); 
  Serial.print("Conectando-se a "); 
  Serial.println(ssid); 

  WiFi.begin(ssid, password); 

  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
    Serial.print("."); 
  }

  Serial.println(""); 
  Serial.println("WiFi conectado"); 
  Serial.println("Endereço IP: "); 
  Serial.println(WiFi.localIP()); 
}

void reconnect() { 
  while (!client.connected()) { 
    Serial.print("Tentando conectar ao MQTT..."); 
    if (client.connect("ESP32Client")) { 
      Serial.println("conectado"); 
      client.subscribe(mqtt_topic); 
    } else { 
      Serial.print("falhou, rc="); 
      Serial.print(client.state()); 
      Serial.println(" tentando novamente em 5 segundos"); 
      delay(5000); 
    }
  }
}

String formatTimestamp() { 
  timeClient.update(); 
  String formattedTime = timeClient.getFormattedTime(); 
  return formattedTime; 
}

void loop() { 
  if (!client.connected()) { 
  }
  client.loop(); 

  bool buttonState = digitalRead(buttonPin); 
  if (buttonState != lastButtonState) { 
    if (buttonState == LOW) { 
      if (botao) { 
        Serial.println("Sistema Desligado"); 
      } else { 
        Serial.println("Sistema Ligado"); 
      }
      botao = !botao; 
    }
    lastButtonState = buttonState;
  }

  String timestampStr = formatTimestamp(); 
  Serial.print("Timestamp: "); 
  Serial.println(timestampStr); 

  JsonDocument jsonDoc; 
  jsonDoc["timestamp"] = timestampStr; 
  jsonDoc["button_state"] = (botao ? "Ligado" : "Desligado"); 
  String jsonString; 
  serializeJson(jsonDoc, jsonString); 
  client.publish(mqtt_topic, jsonString.c_str()); 

  delay(100); 
}

void setup() { 
  Serial.begin(115200); 

  pinMode(buttonPin, INPUT_PULLUP); 
  setup_wifi(); 
  client.setServer(mqtt_server, mqtt_port); 
  client.setCallback(callback); 

  timeClient.begin(); 
}