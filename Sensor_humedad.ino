// YL-39 + YL-69 humidity sensor
byte humidity_sensor_pin = A0;
byte humidity_sensor_vcc = 6;

void setup() {
  // Init the humidity sensor board
  pinMode(humidity_sensor_vcc, OUTPUT);
  digitalWrite(humidity_sensor_vcc, LOW);

  // Setup Serial
  while (!Serial);
  delay(1000);
  Serial.begin(9600);
}




void Mostrar_humedad()
{
    int humedad_actual=map(analogRead(0),0,1024,255,0);
    float porcentaje= 100*humedad_actual/1024;
     Serial.print("Humedad:");
     Serial.println(humedad_actual);
     Serial.print(" Porcentaje: ");
     Serial.println(porcentaje);
     Serial.println();
}

void loop() {
  Serial.print("Humidity Level (0-1023): ");
  Mostrar_humedad(); 
  delay(1000);
}

