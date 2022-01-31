
#include <SPI.h>
#include <MFRC522.h>
#include<SoftwareSerial.h>
#include <Ethernet.h>
#define SS_PIN 53
#define RST_PIN 49
byte UID[21];
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
char server[] = "169.254.0.34";   //YOUR SERVER
IPAddress ip(169, 254, 0 ,35);
EthernetClient client;                 //subnet mask
//EthernetServer server(80);                             //server port 
   
String readString;

//SoftwareSerial mySerial(8,9);  
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
MFRC522::MIFARE_Key key;

//================LOOOOOOOOOPPP=======================>
void loop() 
{  

}


//=================SETUP===============================>
void setup() {
    Serial.begin(9600); // Initialize serial communications with the PC
    SPI.begin();            // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card
    for (byte i = 0; i < 6; i++) 
        {
           key.keyByte[i] = 0xFF;//keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
        }
         while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
//      if (Ethernet.begin(mac) == 0) {
//          Serial.println("Failed to configure Ethernet using DHCP");
//          Ethernet.begin(mac, ip);
//          Serial.println("Conecting...");
//        }
  //Ethernet.begin(mac, ip, gateway, subnet);
  //server.begin();
  Ethernet.begin(mac, ip);
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  Serial.print("\n");
  GetUID();
  Serial.print("\nSatu");
  autentikasi();
  Serial.print("\nDua");    
}

void GetUID(){
  Serial.println("scan");

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
                          
                  } 




                 
                  Serial.println();
                                
                




                  
                  // Terminamos la lectura de la tarjeta  actual
                  mfrc522.PICC_HaltA();
                         
                  
            }      
  } 
}


    

void autentikasi(){
  
 
    if (client.connect(server, 80)) {
    Serial.print("\nthera konek");
    
        char c = client.read();
        Serial.print("\nrasya konek\n");
        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
          Serial.print(c);
          Serial.print("\nmana hasil aut\n");
         }
         
    // Make a HTTP request:
    Serial.println("GET /autentikasi/autentikasi.php?hash=");
    client.print("GET /autentikasi/autentikasi.php?hash=");     //YOUR URL
    client.print("&id=");
    for(int i=0; i<4; i++)
                  {
                    Serial.print(UID[i]);
                    client.print(UID[i]);
                                  
                  }
    
    client.println();
    client.println("Host: 169.254.0.34");
    client.println("Connection: close");
    client.println();
    
    delay(1);
    Serial.print("\ndibawah delay");
        
             
        if (readString.indexOf("?B") >0){
               //digitalWrite(led, HIGH);
               Serial.print("\nLAMPU MENYALA : 1 \n");
           }
        if (readString.indexOf("?A") >0){
               //digitalWrite(led, LOW);
               Serial.print("\nLAMPU MATI : 0 \n");
           }
         
           
            //clearing string for next read
            readString=""; 
            Serial.print("\ndibawah readstring");
    }else{
      
    Serial.println("connection failed");
    }
         
          // if you didn't get a connection to the server:
            //Serial.println("connection failed");
           
         //}
         //stopping client
         client.stop();
        
         
   
}
 
