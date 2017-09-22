// Sketch de ejemplo para testear el famoso sensor DHT de humedad y temperatura
// Escrito por ladyada, de dominio público
// Modificado por Regata para www.tallerarduino.wordpress.com

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"  //Añadimos la libreria con la cual trabaja nuestro sensor
#define DHTPIN 7     // Indicamos el pin donde conectaremos la patilla data de nuestro sensor
 
// Descomenta el tipo de sensor que vas a emplear. En este caso usamos el DHT11
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
 
// Conecta el pin 1 (el de la izquierda) del sensor a +5V
// Conecta el pin 2 del sensor al pin que has elegido para DHTPIN
// Conecta el pin 4 (el de la derecha) del sensor a GROUND
// Conecta una resistencia de 10K del pin 2 (data) al pin 1 (+5V) del sensor
//Crear el objeto lcd  dirección  0x27 y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,16,2);  //

DHT dht(DHTPIN, DHTTYPE);  //Indica el pin con el que trabajamos y el tipo de sensor
int maxh=0, minh=100, maxt=0, mint=100;  //Variables para ir comprobando maximos y minimos
int t,h;

const int sensorPin0 = A0;
const int sensorPin1 = A1;

void setup() 
{
  //Inicio comunicacion serie para ver los datos en el ordenador
  Serial.begin(9600); 
  //Mensaje de inicio
  Serial.println("Comprobacion sensor DHTxx:");
  //Iniciamos el sensor
  dht.begin();
  lcd.init();
}
 
void loop() 
{
  // La lectura de la temperatura o de la humedad lleva sobre 250 milisegundos  
  // La lectura del sensor tambien puede estar sobre los 2 segundos (es un sensor muy lento)
  h = dht.readHumidity();  //Guarda la lectura de la humedad en la variable float h
  t = dht.readTemperature();  //Guarda la lectura de la temperatura en la variable float t
 comprobar(); //max y minimos de sensor dth11
 humedadtierra();

  delay(1000);
}



void comprobar(){
   // Comprobamos si lo que devuelve el sensor es valido, si no son numeros algo esta fallando
  if (isnan(t) || isnan(h)) // funcion que comprueba si son numeros las variables indicadas 
  {
    Serial.println("Fallo al leer del sensor DHT"); //Mostramos mensaje de fallo si no son numeros
  } else {
    //Mostramos mensaje con valores actuales de humedad y temperatura, asi como maximos y minimos de cada uno de ellos
    Serial.print("Humedad relativa: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperatura: "); 
    Serial.print(t);
    Serial.println(" *C");
    //Comprobacion de maximos y minimos de humedad y temperatura
    if (maxh<h)
      maxh=h;
    if (h<minh)
      minh=h;
    if (maxt<t)
      maxt=t;
    if (t<mint)
      mint=t;
    Serial.print("Max: ");
    Serial.print(maxh);
    Serial.print(" % ");
    Serial.print("Min: ");
    Serial.print(minh);
    Serial.print(" %\t");
    Serial.print("Max: ");
    Serial.print(maxt);
    Serial.print(" *C ");
    Serial.print("Min: ");
    Serial.print(mint);
    Serial.println(" *C\n");
  }
}

void humedadtierra(){
  int humedad0 = analogRead(sensorPin0);
  int humedad1 = analogRead(sensorPin1);
  
   float porcentaje_sin_calcular0=map(humedad0, 0, 1023, 0, 100);
   float porcentaje_sin_calcular1=map(humedad1, 0, 1023, 0, 100);
   float porcentaje_calculado0=100-porcentaje_sin_calcular0;
   float porcentaje_calculado1=100-porcentaje_sin_calcular1;
   //Serial.print("Sensor Analogo : ");
   //Serial.println(humedad);
   //Serial.print("Porcentaje Sin Calcular ");
   //Serial.println(porcentaje_sin_calcular);
   Serial.print("Porcentaje Calculado 0: ");
   Serial.println(porcentaje_calculado0);
   Serial.print("Porcentaje Calculado 1: ");
   Serial.println(porcentaje_calculado1);
   Serial.println(" ");
  
   
}

