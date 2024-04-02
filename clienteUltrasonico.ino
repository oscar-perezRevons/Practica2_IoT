#include <WiFi.h>
#include <WiFiClient.h>

int DISTANCIA = 0;
int pinEco = 18;
int pinLed=1;
int pinGatillo = 19;
const char* ssid = "Galaxy A34 5G 9EFF"; // Nombre de tu red WiFi
const char* password = "10000000"; // Contraseña de tu red WiFi
const char* host = "192.168.160.91"; // Dirección IP de la PC que actúa como servidor
const int port = 8888; // Puerto para la comunicación TCP/IP

WiFiClient client;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  //Iniciamos el pin del emisor de reuido en salida
  pinMode(triggerPin, OUTPUT);
  //Apagamos el emisor de sonido
  digitalWrite(triggerPin, LOW);
  //Retrasamos la emision de sonido por 2 milesismas de segundo
  delayMicroseconds(2);
  // Comenzamos a emitir sonido
  digitalWrite(triggerPin, HIGH);
  //Retrasamos la emision de sonido por 2 milesismas de segundo
  delayMicroseconds(10);
  //Apagamos el emisor de sonido
  digitalWrite(triggerPin, LOW);
  //Comenzamos a escuchar el sonido
  pinMode(echoPin, INPUT);
  // Calculamos el tiempo que tardo en regresar el sonido
  return pulseIn(echoPin, HIGH);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando...");
  }

  Serial.println("Conectado a la red WiFi");
}

void loop() {
  // Simula la lectura de una distancia (puedes sustituir esta parte por tu sensor)
  DISTANCIA = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);

  if (client.connect(host, port)) {
    Serial.println("Conectado al servidor");
    client.print(DISTANCIA); // Envía la distancia al servidor
    client.stop(); // Cierra la conexión
    Serial.println("Distancia enviadaQAAAA");
  } else {
    Serial.println("Error al conectar al servidor");
  }

  delay(5000); // Espera 5 segundos antes de enviar la próxima lectura
}
