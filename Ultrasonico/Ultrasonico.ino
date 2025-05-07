//Declaramos las variables donde van insertados los pines
int trigger = 12; //Este será el pin que mandará el sonido y lo conectaremos al pin 12 del arduino
int eco = 11; //Este será el pin que recibirá el sonido y lo conectaremos al pin 11 del arduino
int pingTravelTime; // Variable para saber el tiempo de viaje del sonido

void setup() {
  pinMode(trigger, OUTPUT); //Inicializamos el pin trigger como salida de datos
  pinMode(eco, INPUT); //Inicializamos el pin Eco como entrada de datos
  Serial.begin(9600); // Inicializamos el monitor serial a 9600 baudios (puede ser otro) para ver los datos del sensor.
}

void loop() {
  //Enviamos un pulso ultrasónico de 10 microsegundos
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  //Medimos el tiempo que tarda en recibir el eco
  pingTravelTime = pulseIn(eco, HIGH); 
  delay(25);
  
  //Mostramos el tiempo medido en el monitor serial
  Serial.println(pingTravelTime);
}
