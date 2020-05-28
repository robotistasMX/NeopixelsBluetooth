# NeopixelsBluetooth
Por Roy Molina TW: @romodo0 FB: /romodo 
Like a https://www.facebook.com/robotistasMX :3

Con este programa se controla, desde una app para Android hecha en App Inventor,
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

Se adjunta código de Arduino y el proyecto de App Inventor 

IMPORTANTE: Para que pueda funcionar
la conexión Bluetooth, se debe cambiar el valor de la Address en el programa de su valor actual: 20:18:08:34:EA:FB
a la dirección correspondiente del módulo HC05 que estén usando (eso puede mejorarse creando un picker de
dispositivos Bluetooth, si alguien lo desarrolla se agradece el aporte)
