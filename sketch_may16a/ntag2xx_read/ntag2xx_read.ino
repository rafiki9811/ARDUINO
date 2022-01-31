#include <Wire.h>
#include <SPI.h>
//#include <Adafruit_PN532.h>
 #include <Adafruit_NFCShield_I2C.h>
/*#define PN532_SCK  (13)
#define PN532_MOSI (11)
#define PN532_SS   (10)
#define PN532_MISO (12)
*/
#define IRQ   (2)
#define RESET (3)

Adafruit_NFCShield_I2C nfc(IRQ,RESET);
 
//Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);
 
void setup(void) {
  Serial.begin(9600);
 
  nfc.begin();
 
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("PN53x no encontrado");
    while (1); // halt
  }
 
  // Mostrar datos del sensor
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  // Configurar para leer etiquetas RFID
  nfc.setPassiveActivationRetries(0xFF);
  nfc.SAMConfig();
  
  Serial.println("Esperando tarjeta ISO14443A");
  delay(1000);
}
 
// Funcion auxiliar para mostrar el buffer
void printArray(byte *buffer, byte bufferSize) {
   for (byte i = 0; i < bufferSize; i++) {
      Serial.print(buffer[i] < 0x10 ? " 0" : " ");
      Serial.print(buffer[i], HEX);
   }
}
 
 
void loop(void) {
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;
 
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
  delay(1000);
  if (success) {
    Serial.println("Tarjeta encontrada");
    Serial.print("UID Longitud: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("UID: "); printArray(uid, uidLength);
    Serial.println("");
  
    delay(1000);
  }
  else
  {    
    Serial.println("Tarjeta no encontrada");
     delay(1000);
  }
  
}
