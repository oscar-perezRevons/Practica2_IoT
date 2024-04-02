#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
int DISTANCIA = 0;
int pinEco = 18;
int pinLed=1;
int pinGatillo = 19;
class LED
{
  private:
    int numero;
  public:
    int getnumero()
    {
      return numero;
    }
    void setnumero(int n)
    {
      numero=n;
    }
    LED(int n)
    {
      numero=n;
    }
    void encender(){
      digitalWrite(numero, HIGH);
    }

    void apagar() {
      digitalWrite(numero, LOW);
    }
};
const char* ssid = "Galaxy A34 5G 9EFF"; // Nombre de tu red WiFi
const char* password = "10000000"; // Contraseña de tu red WiFi
const int serverPort = 8888; // Puerto en el que el servidor estará escuchando
WiFiServer server(serverPort);

void setup() {
  Serial.begin(115200);
  delay(1000);
pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  // Conectar a la red WiFi
  Serial.println();
  Serial.println("Conectando a la red WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado a la red WiFi");
  Serial.println("Dirección IP: " + WiFi.localIP().toString());

  // Iniciar el servidor
  server.begin();
  Serial.println("Servidor escuchando en el puerto " + String(serverPort));
}
LED L1(1);



void loop() {
  
  // Esperar una conexión entrante
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Leer la distancia enviada por el cliente
  while (client.connected()) {
    if (client.available()) {
      String distanciaStr = client.readStringUntil('\n');
      float DISTANCIA = distanciaStr.toFloat();
      Serial.println("Distancia recibida: " + String(DISTANCIA));
      L1.setnumero(0);
      while(L1.getnumero()!=3)
      {
        L1.setnumero(L1.getnumero()+1);
        if (DISTANCIA > 0 && DISTANCIA <= 10 && L1.getnumero() == 3) { continue; }
        if (DISTANCIA > 10 && DISTANCIA <= 20 && L1.getnumero() == 2) { continue; }
        if (DISTANCIA > 20 && DISTANCIA <= 30 && L1.getnumero() == 1) { continue; }
        L1.encender();
        //digitalWrite(i, HIGH);
        delay(230);
        //digitalWrite(i, LOW);
        L1.apagar();
      }
      delay(100);
      
  //Si la distancia es menor a 20 encendemos el led
   

      break; // Salir del bucle para esperar una nueva conexión
    }
  }

  // Cerrar la conexión
  client.stop();
}
