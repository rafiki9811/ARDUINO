//Configurar salidas de los leds
   void setup() {
  // put your setup code here, to run once:}

   pinMode (2, OUTPUT);
   pinMode (3, OUTPUT);
   pinMode (4, OUTPUT);
   pinMode (5, OUTPUT);
   pinMode (6, OUTPUT);
   pinMode (7, OUTPUT);
   pinMode (8, OUTPUT);  

   //Configurar el pin de entrada del pulsador
   pinMode (9, INPUT);
    
   //Inicializa el generador de numeros aleatorios
   randomSeed(analogRead(0));   
    
   //Apaga todos los leds
   digitalWrite (2, LOW);
   digitalWrite (3, LOW);
   digitalWrite (4, LOW);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW);
   digitalWrite (7, LOW);
   digitalWrite (8, LOW);
   }
 
void beep () {
 
    digitalWrite (10, HIGH);
    delay (20);
    digitalWrite (10, LOW);
 
}
 
 
void escribe_dado (unsigned char num) {
  //Escribe numero en el dado
  switch (num) {
            
    case 1: //Prender el numero 1
            digitalWrite (2, LOW);
            digitalWrite (3, LOW);
            digitalWrite (4, LOW);
            digitalWrite (5, HIGH);
            digitalWrite (6, LOW);
            digitalWrite (7, LOW);
            digitalWrite (8, LOW);           
            break;
            
    case 2: //Prender el numero 2
            digitalWrite (2, LOW);
            digitalWrite (3, HIGH);
            digitalWrite (4, LOW);
            digitalWrite (5, LOW);
            digitalWrite (6, LOW);
            digitalWrite (7, HIGH);
            digitalWrite (8, LOW);              
            break;
            
    case 3: //Prender el numero 3
            digitalWrite (2, HIGH);
            digitalWrite (3, LOW);
            digitalWrite (4, LOW);
            digitalWrite (5, HIGH);
            digitalWrite (6, LOW);
            digitalWrite (7, LOW);
            digitalWrite (8, HIGH);  
            break;
            
    case 4: //Prender el numero 4
            digitalWrite (2, HIGH);
            digitalWrite (3, LOW);
            digitalWrite (4, HIGH);
            digitalWrite (5, LOW);
            digitalWrite (6, HIGH);
            digitalWrite (7, LOW);
            digitalWrite (8, HIGH);  
            break;
            
    case 5: //Prender el numero 5
            digitalWrite (2, HIGH);
            digitalWrite (3, LOW);
            digitalWrite (4, HIGH);
            digitalWrite (5, HIGH);
            digitalWrite (6, HIGH);
            digitalWrite (7, LOW);
            digitalWrite (8, HIGH);  
            break;
            
    case 6: //Prender el numero 6
            digitalWrite (2, HIGH);
            digitalWrite (3, HIGH);
            digitalWrite (4, HIGH);
            digitalWrite (5, LOW);
            digitalWrite (6, HIGH);
            digitalWrite (7, HIGH);
            digitalWrite (8, HIGH); 
            break;
        
    default:
    case 0:  //Apagar todos los leds
            digitalWrite (2, LOW);
            digitalWrite (3, LOW);
            digitalWrite (4, LOW);
            digitalWrite (5, LOW);
            digitalWrite (6, LOW);
            digitalWrite (7, LOW);
            digitalWrite (8, LOW); 
            break;
            
  }
  
 
}
 
 
void loop () {
  
  unsigned int numero;
  
  while (!digitalRead (9));     //Espera a que aprieten pulsador
 
  escribe_dado (0);              //Apaga todos los leds
  
  while (digitalRead (9));      //Espera a que suelten pulsador
  
  beep ();
  
  numero = random(1, 7);        //Genera un numero al azar entre 1 y 6
  
  escribe_dado (numero);        //Mostrar el numero en el dado
 
 
}
