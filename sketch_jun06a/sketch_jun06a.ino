#include <Ethernet.h>
#include <SPI.h>      
#include <MFRC522.h>
#include <Servo.h>
#define RST_PIN  9    //Pin 9 para el reset del RC522
#define SS_PIN  10   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522
// Configuracion del Ethernet Shield
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFF, 0xEE}; // Direccion MAC
 IPAddress ip(192,168,1,254); // Direccion IP del Arduino
char server = "127.0.0.1"; // Direccion IP del servidor
EthernetClient client; 
float temperatura;
int analog_pin = 0;

void setup(void) {
     Serial.begin(9600); //Iniciamos la comunicación  serial
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos  el MFRC522
  Ethernet.begin(mac,ip);
  Serial.print("IP: ");
  Serial.println(Ethernet.localIP());
  Serial.println("Lectura del UID");
  Ethernet.begin(mac, ip); // Inicializamos el Ethernet Shield
  delay(1000); // Esperamos 1 segundo de cortesia
}

void loop(void) {
  temperatura = analogRead(analog_pin);
  temperatura = 5.0*temperatura*100.0/1024.0;
  //Display in Serial Monitor
  Serial.print(temperatura); //Return temperature to Monitor
  Serial.println(" oC");
  // Proceso de envio de muestras al servidor
  Serial.println("Connecting...");
  if (client.connect(server, 80)) {  // Conexion con el servidor
    client.print("GET /tutoiot/iot.php?valor="); // Enviamos los datos por GET
    client.print(temperatura);
    client.println(" HTTP/1.0");
    client.println("User-Agent: Arduino 1.0");
    client.println();
    Serial.println("Conectado");
  } else {
    Serial.println("Fallo en la conexion");
  }
  if (!client.connected()) {
    Serial.println("Disconnected!");
  }
  client.stop();
  client.flush();
  delay(60000); // Espero un minuto antes de tomar otra muestra
}
