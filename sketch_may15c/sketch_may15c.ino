/* Programa para leer Tarjetas RFID y verificar si es un usuario Valido.
  Hecho por Claudio Alberto Ibañez Garduño en colaboración con
  La Asociación de Robótica Aplicada y Ciencias de la Tecnología.
  Ocupando la biblioteca elaborada por Miguel BaÇ¨lboa.
*/


//Incluimos bibliotecas para utilizar el RC522
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN  9    //Pin 9 para el reset del RC522
#define SS_PIN  10   //Pin 10 para el SS (SDA) del RC522
MFRC522 Lector1(SS_PIN, RST_PIN); ///Creamos el objeto para el RC522 al cual llamamos Lector1



void setup() {
  Serial.begin(9600); //Iniciamos La comunicacion serial
  SPI.begin();        //Iniciamos el Bus SPI
  Lector1.PCD_Init(); // Iniciamos el MFRC522
  Serial.println("Bienvenido al Sistema Lector de Tarjetas RFID\n    Por Favor Acerca tu Tarjeta al Lector\n");
}


void loop() {
 
 if ( Lector1.PICC_IsNewCardPresent())   // Revisamos si hay nuevas tarjetas  presentes.

        { 
            if ( Lector1.PICC_ReadCardSerial())  //Leemos la tarjeta presente.

            {
                 
                  Serial.print("El ID de tu tarjeta es: "); // Imprimimos el ID de la tarjeta
                  for (byte i = 0; i < Lector1.uid.size; i++) {
                          Serial.print(Lector1.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          Serial.print(Lector1.uid.uidByte[i], DEC);          
                  }
                  Serial.println(" ");                

            
                  Lector1.PICC_HaltA(); // Terminamos la lectura de la tarjeta tarjeta para ahorrar energía.
                  Lector1.PCD_StopCrypto1(); //Detenemos la encriptacion.
                 
         
            }
     
 }
 
}
