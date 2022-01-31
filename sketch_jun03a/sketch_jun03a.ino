#include <SPI.h>;
#include <MFRC522.h>;
MFRC522 rfid(10,5); 
void setup() { 
Serial.begin(9600); //Inicializa la velocidad de Serial 
SPI.begin(); //Función que inicializa SPI 
rfid.PCD_Init(); //Función que inicializa RFID 
} 
void loop() { 
if (rfid.PICC_IsNewCardPresent()) { //Verifica si hay una tarjeta 
if (rfid.PICC_ReadCardSerial()) { //Funcion que lee la tarjeta 
Serial.println(" "); 
Serial.println(" "); 
Serial.println("El numero de serie de la tarjeta es : "); 
for(int i=0;i<=4; i++){ 
if(i!=4){ 
Serial.print(rfid.serNum[i],HEX); //rfid.serNum lee el número de serie unico de la tarjeta 
Serial.print(" "); 
} 
else{ 
Serial.print(rfid.serNum[i],HEX); 
Serial.print(" "); 
} 
} 
delay(1000); 
} 
} 
rfid.halt(); 
}
