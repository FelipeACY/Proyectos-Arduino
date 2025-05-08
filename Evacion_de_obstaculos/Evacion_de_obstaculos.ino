// Declaramos las variables con sus espectivos pines;
int led = 13 // Vamos a conectar un led en el pin 13, tambien se usa el integrado en la placa
int output = 3; // Conectamos el OUT en el pin 3 del arduino
int value; // Declaramos una Variable para almacenar el valor del sensor

void setup() {
  pinMode(led, OUTPUT);     // Configuramos el LED como salida
  pinMode(output, INPUT);   // Configuramos el pin del sensor como entrada
  // el sensor tiene un potenciómetro para ajustar la distancia de detección
}

void loop() {
  value = digitalRead(output);  // Leemos el estado del sensor
  
  // - LOW (0) cuando detecta un obstáculo
  // - HIGH (1) cuando no detecta nada
  if (value == HIGH) {
    digitalWrite(led, LOW);   // Apagamos LED si no hay obstáculo
  }
  else {
    digitalWrite(led, HIGH);  // Encendemos LED cuando detecta obstáculo
  }
  // Pequeña pausa
  delay(50);
}
