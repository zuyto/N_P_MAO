
/*********** LIBRERIAS **************/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>


/*********** MQTT CONFIG **************/


IPAddress mqttServer("IP del Broker");
const int mqttPort = 1883 ;
const char *topicSubscribe = "Topic con el que se subscribe en el broker";
const char *topicPublish = "Topic a donde va a publicar";

/*********** WIFICONFIG ***************/

const char* ssid = "Usuario Red WIFI";
const char* password =  "contraseña WIFI";

/*********** GLOBALES   ***************/

WiFiClient espClient;
PubSubClient client(espClient);
char msg[50];
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;




/** F U N C I O N E S ***/

void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void setup_wifi();


/** SETUP ARDUINO ***/

void setup() {
  Serial.begin(115200);

  setup_wifi();
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}


/** LOOP ***/

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  /*** CLIENTE MQTT A LA ESCUCHA ***/
  client.loop();
}




/***    CONEXION WIFI      ***/
void setup_wifi() {
  delay(10);
  // Nos conectamos a nuestra red Wifi
  Serial.println();
  Serial.print("Conectando a red WIFI!: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("..CONECTANDO..");
  }

  Serial.println("");
  Serial.println("Conexión exitosa a su red WiFi!");
  Serial.println("Dirección IP asignada: ");
  Serial.println(WiFi.localIP());
}




/***    CONEXION MQTT      ***/

void reconnect() {

  while (!client.connected()) {
    Serial.print("Intentando conexión Mqtt...");
    /* Creamos un cliente ID */
    String clientId = "poner nombre del cliente";
    clientId += String(random(0xffff), HEX);
    // Intentamos conectar
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado!");
      /* Nos suscribimos */
      if (client.subscribe(topicSubscribe)) {
        Serial.println("Suscripcion ok");
      } else {
        Serial.println("fallo Suscripciión");
      }
    } else {
      Serial.print("falló :( con error -> ");
      Serial.print(client.state());
      Serial.println(" Intentamos de nuevo en 5 segundos");
      delay(5000);
    }
  }
}


/***       CALLBACK        ***/
/*******ESCUCHA LO QUE SE ENVIA POR EL TOPIC*******/

void callback(char* topic, byte* payload, unsigned int length) {
  String incoming = "";
  Serial.print("Mensaje recibido desde -> ");
  Serial.print(topic);
  Serial.println("");
  for (int i = 0; i < length; i++) {
    incoming += (char)payload[i];
  }
  incoming.trim();
  Serial.println("Mensaje -> " + incoming);
  
}
