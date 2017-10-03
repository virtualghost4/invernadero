/*invernadero stage 1*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"  //libreria adafruit dht
#define DHTPIN 7     //pin conectado al sensor de humedad del aire
 
// define el tipo de sensor a utilizar
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
LiquidCrystal_I2C lcd(0x3f,16,2);  //
DHT dht(DHTPIN, DHTTYPE);  //Indica el pin con el que trabajamos y el tipo de sensor
int maxh=0, minh=100, maxt=0, mint=100;  //Variables para ir comprobando maximos y minimos
int t,h;

const int sensorPin0 = A0;
const int sensorPin1 = A1;


void setup() 
{
  Serial.begin(9600); 
  Serial.println("Comprobacion sensor DHTxx:");
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.print("Invernadero");
  delay(3000);
}
 
void loop() 
{
  int humedad0 = analogRead(sensorPin0);
  int humedad1 = analogRead(sensorPin1);
    
  float porcentaje_sin_calcular0=map(humedad0, 0, 1023, 0, 100);
  float porcentaje_sin_calcular1=map(humedad1, 0, 1023, 0, 100);
  float porcentaje_calculado0=100-porcentaje_sin_calcular0;
  float porcentaje_calculado1=100-porcentaje_sin_calcular1;
  
  Serial.print("Porcentaje Calculado Sensor 0: ");
  Serial.println(porcentaje_calculado0);
  Serial.print("Porcentaje Calculado 1: ");
  Serial.println(porcentaje_calculado1);
  Serial.println(" ");
  h = dht.readHumidity();  //Guarda la lectura de la humedad en la variable float h
  t = dht.readTemperature();  //Guarda la lectura de la temperatura en la variable float t
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
 lcd.setCursor(0,0);
 lcd.print("Humedad tierra");
 lcd.setCursor(0,1);
 lcd.print(String(porcentaje_calculado0)+" %");
 delay(2000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("H. Relativa");
 lcd.setCursor(0,1);
 lcd.print(String(h)+" %");
 delay(2000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Temp Ambiental");
 lcd.setCursor(0,1);
 lcd.print(String(t)+" C");
 delay(2000);
 lcd.clear();
}

