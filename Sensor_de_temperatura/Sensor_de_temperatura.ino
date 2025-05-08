// Incluimos las librerías necesarias
#include <OneWire.h> // son las que instalaremos
#include <DallasTemperature.h>   

// Definimos el pin donde conectamos el cable de datos del sensor que es la señal
#define ONE_WIRE_BUS 2

// Configuramos la instancia para el bus 1-Wire
OneWire oneWire(ONE_WIRE_BUS);

// Pasamos la referencia del bus 1-Wire al sensor
// estas librerias hacen todo el proceso de conversion, y el codigo no es tan extenso
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);      // Iniciamos comunicación serial a 9600 baudios
  Serial.println("Iniciando sensor de temperatura KY-001 (DS18B20)");
  sensors.begin();         // Inicializamos el sensor de temperatura
}

void loop() {
  // Solicitamos una lectura de temperatura al sensor
  sensors.requestTemperatures(); 
  
  // Obtenemos la temperatura en grados Celsius del primer dispositivo (índice 0)
  // El DS18B20 puede medir de -55°C a +125°C con precisión de ±0.5°C
  float tempC = sensors.getTempCByIndex(0);
  
  // Mostramos los resultados por el monitor serial
  Serial.print("Temperatura: ");
  Serial.print(tempC);
  Serial.println(" °C");
  
  delay(1000);  // Esperamos 1 segundo entre lecturas
}
