/*
Por Roy Molina TW: @romodo0 FB: /romodo 
Like a https://www.facebook.com/robotistasMX :3

Con este programa se controla, desde una app para Android hecha en App Inventor,
(proyecto acá: https://github.com/robotistasMX/NeopixelsBluetooth/blob/master/ControlNeopixels.aia )
el encendido y apagado de dos matrices de LEDs Neopixels (unos LEDs RGB muy
coquetos que distribuye Adafruit a los cuales se les puede controlar el color usando 
únicamente un pin del microcontrolador). Para ello se usa un Arduino UNO al que se
le conecta un módulo Bluetooth HC05 para lograr la comunicación con el smartphone.

Las conexiones son muy simples:

Arduino         HC05
5V              VCC
GND             GND
Pin 7           TX
Pin 6           RX

Arduino         Matriz 1 (yo compré esta https://articulo.mercadolibre.com.mx/MLM-667744645-modulo-arduino-5v-matriz-8x8-64-led-rgb-neopixel-ws2812-_JM?quantity=1 )
Pin 8           DIN

Fuente
externa de 5V   Matriz 1 
Voltaje         +5V
Tierra          GND
ADVERTENCIA: (puedes intentar sin conectar una fuente externa y
mandando 5V de la matriz directo a 5V del Arduino, ¡pero cuidado!,
si requieres demasiada corriente y el Arduino la está tomando de
tu computadora, podría dañarse tu puerto USB)

Matriz 1        Matriz 2
+5V             +5V
GND             GND
DOUT            DIN

En pocas palabras, la app manda una cadena de texto de formato CCrCCgCCbNNay
en donde CC es el valor de R, G o B (entre 0 y 255) del que debe encender el neopixel, 
NN es el número de Neopixel que debe encenderse y 'r', 'g', 'b', "a" e "y"
son caracteres de control.
*/

#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h> //Librería, descargar de https://github.com/adafruit/Adafruit_NeoPixel

SoftwareSerial mySerial(7, 6); // RX, TX Pines para conectar el módulo Bluetooth
#define PIN        8 //pin de control de la matriz de neopixels (DIN)
#define NUMPIXELS 128 //cantidad de neopixels a controlar (código hecho para 2 matrices unidas, 128 NP en total)
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); //Dar de alta neopixels

//variables
String cadena;
int R=255,G=255,B=255,PIX,matriz;
int intensidad=30;
int dato;

void setup() {
  Serial.begin(9600); //iniciar comunicación serial para debbuging
  mySerial.begin(9600); //iniciar comunicación serial del Bluetooth
  pixels.begin(); //Iniciar neopixels
  pixels.clear(); //Apagar todos los neopixels
}

void loop() { 
  
  while(mySerial.available()!='y'){
      int dato=mySerial.read();
      //Serial.println(dato);
                    
                if (isDigit(dato)) {
                    cadena+=(char)dato;
                }        
                else if(dato=='d'){ //si el dato recibido fue "d" controlar los neopixels de la matriz 1
                    matriz=0;     
                    Serial.println("matriz 1");           
                }                        
                else if(dato=='i'){ //si el dato recibido fue "i" controlar los neopixels de la matriz 2
                    matriz=1;     
                    Serial.println("matriz 2");           
                }
                else if(dato=='z'){ //si el dato recibido fue "z" apagar todos los neopixels de la matriz elegida
                  if(matriz==0){
                  for(int i=0;i<64;i++){
                    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
                    pixels.show();
                    delay(5);
                  }
                  }
                  else{
                  for(int i=64;i<128;i++){
                    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
                    pixels.show();
                    delay(5);
                  }
                  }
                }
                else if(dato=='r'){     //obtener y guardar el dato de R
                    Serial.print("Red:");
                    R=cadena.toInt();
                    Serial.println(R);
                    // clear the string for new input:
                    cadena = "";     
                }                 
                
                else if(dato=='g'){     //obtener y guardar el dato de G
                    Serial.print("Green:");
                    G=cadena.toInt();
                    Serial.println(G);
                    // clear the string for new input:
                    cadena = "";     
                }                  
                
                else if(dato=='b'){     //obtener y guardar el dato de B
                    Serial.print("Blue:");
                    B=cadena.toInt();
                    Serial.println(B);
                    // clear the string for new input:
                    cadena = "";   
                }   

                else if(dato=='a'){     //llegó la orden de encender un neopixel en específico
                    Serial.print("LED:");
                    PIX=cadena.toInt();
                    Serial.println(PIX);
                    // clear the string for new input:
                    cadena = "";   
                    //pixels.clear();
                    if(matriz==0){
                      //encender el neopixel específico del color RGB que se pide
                    pixels.setPixelColor(PIX, pixels.Color(
                      R=map(R,0,255,0,intensidad), 
                      G=map(G,0,255,0,intensidad),
                      B=map(B,0,255,0,intensidad)));
                    }
                    else{
                    pixels.setPixelColor(PIX+64, pixels.Color(
                      R=map(R,0,255,0,intensidad), 
                      G=map(G,0,255,0,intensidad),
                      B=map(B,0,255,0,intensidad)));
                    }
                    pixels.show();
                }   
  }
}
