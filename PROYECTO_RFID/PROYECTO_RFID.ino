
#include <SPI.h>      
#include <MFRC522.h>
#include <Servo.h>
#define RST_PIN  9    //Pin 9 para el reset del RC522
#define SS_PIN  10   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522
Servo servoMotor;
char server[]= {127,0,0,1};
void setup() {
  Serial.begin(9600); //Iniciamos la comunicación  serial
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos  el MFRC522
  Serial.println("Lectura del UID");
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);     
 servoMotor.attach(7);
}
 void moverServo(Servo servoMotor){
    for (int i = 0; i <= 90; i++)
  {
    // Desplazamos al ángulo correspondiente
    servoMotor.write(i);
    // Hacemos una pausa de 25ms
    delay(25);
  }
 }


//Función para comparar dos vectores
 boolean compareArray(byte array1[],byte array2[])
{
  if(array1[0] != array2[0])return(false);
  if(array1[1] != array2[1])return(false);
  if(array1[2] != array2[2])return(false);
  if(array1[3] != array2[3])return(false);
  return(true);
}

void loop() {

byte estudiante[] = { 155, 67, 29, 187};
byte discapacitado[] = {144, 254, 00, 116};
byte  insen[] = {144, 234, 146, 165};
byte datoLeido[4];

  // Revisamos si hay nuevas tarjetas  presentes
  if ( mfrc522.PICC_IsNewCardPresent()) 
        {  
      //Seleccionamos una tarjeta
            if ( mfrc522.PICC_ReadCardSerial()) 
            {
                  // Enviamos serialemente su UID
                  Serial.print("Card UID:");
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          Serial.print(mfrc522.uid.uidByte[i], DEC);
                          datoLeido[i]=  mfrc522.uid.uidByte[i];
                  } 
                  if(compareArray(datoLeido,estudiante)){
                    
                    digitalWrite(2,HIGH);
                     delay(500);
                     digitalWrite(2,LOW);
                     moverServo(servoMotor);
                  }  else if(compareArray(datoLeido,discapacitado)){
                      digitalWrite(3,HIGH);
                       delay(500);
                       digitalWrite(3,LOW);
                       moverServo(servoMotor);
                  } else if(compareArray(datoLeido,insen)){
                      digitalWrite(4,HIGH);
                       delay(500);
                       digitalWrite(4,LOW);
                       moverServo(servoMotor);
                  }
                  Serial.println();

                  // Terminamos la lectura de la tarjeta  actual
                  mfrc522.PICC_HaltA();    
            }      
  } 
}
