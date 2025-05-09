#include <WiFi.h> // Descargamos y incluimos la librería para conectarse a redes WiFi en la ESP-32
// esta libreria no es externa, la trae por defecto el programa

// Vamos a añadir la red en la que queremos conectar usando las credenciales
// Esto con una constante ya que el valor no cambie y es buena práctica
const char* ssid = "hola"; // Nombre de tu red WiFi
const char* password = "120912091209"; // Contraseña de tu red WiFi

const int ledPin = 2; // Pin donde está conectado el LED GPIO2 del ESP32 que está integrado en la placa

WiFiServer server(80); // Crea un servidor gracias a la libreria en el puerto HTTP por defecto (80) 


String header; // Para almacenar la petición HTTP del cliente
String ledState = "off"; // Estado actual del LED sera apagado (off)


void setup() {
  Serial.begin(9600); // Inicia la comunicación por el monitor serial como lo hicimos anteriormente

  // Configura el pin del LED como salida y lo apaga inicialmente
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Conexión a la red WiFi
  Serial.println("Conectando a WiFi..."); // damos el mensaje de ejecució del programa y mandamos el nombre y contraseña con el uso de la libreria
  WiFi.begin(ssid, password); // Aquí inicia la conexión con los datos de las variables
  while (WiFi.status() != WL_CONNECTED) //Creamos un ciclo para verificar la conexion, ya que puede demorarse un poco
  { 
    delay(500);
    Serial.print("."); // Imprime puntos mientras intenta conectarse
  }

  // Si nos da error probablemente estamos colocando mal la contraseña o el nombre
  Serial.println(""); // damos un salto de línea para organizar la informacion
  Serial.println("Conectado a WiFi"); //mensaje de confirmacion
  Serial.println(WiFi.localIP()); //el localIP manda la IP donde se alojo nuestro programa o servidor Web
  server.begin(); //Luego de conectar y mostar la Ip, iniciamos el servidor
}

void loop() {
  WiFiClient client = server.available(); //verifica si un usuario se conectó e interactuó con el servidor

  if (client) { // Si hay un usuario conectado se inicia la siguiente secuencia, solo si hay un navegador conectado
    Serial.println("Nuevo usuario."); // damos un aviso de que entro el usuario
    String currentLine = ""; // Línea actual de datos recibidos del usuario

    while (client.connected()) { // Mientras el usuario esté conectado, seguira leyendo datos

      if (client.available()) { // Si hay datos disponibles en la web
        char c = client.read(); // se Lee carácter a carácter luego
        Serial.write(c); // los mprimimos por el monitor serie para luego
        header += c; // Acumularlo en la variable 'header' que  almacenar la petición HTTP del usuario

        // Si se detecta el fin de línea en el servidor
        if (c == '\n') {
          // Si la línea actual está vacía, es el fin del header HTTP
          if (currentLine.length() == 0) {
            // Enviar cabecera de respuesta HTTP al navegador
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Acciones según la petición del cliente
            if (header.indexOf("GET /led/on") >= 0) {
              Serial.println("LED ON");
              ledState = "on";
              digitalWrite(ledPin, HIGH); // Enciende el LED
            } else if (header.indexOf("GET /led/off") >= 0) {
              Serial.println("LED OFF");
              ledState = "off";
              digitalWrite(ledPin, LOW); // Apaga el LED
            }

            // Página web HTML enviada al cliente
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<style>body{font-family:Arial;text-align:center;}button{padding:20px 40px;margin:20px;font-size:24px;}</style></head>");
            client.println("<body><h1>Control LED ESP32</h1>");

            // Muestra el estado del LED
            client.println("<p>Estado LED: " + ledState + "</p>");

            // Muestra botón según el estado actual
            if (ledState == "off") {
              client.println("<a href=\"/led/on\"><button>ENCENDER</button></a>");
            } else {
              client.println("<a href=\"/led/off\"><button>APAGAR</button></a>");
            }

            client.println("</body></html>"); // Cierra el HTML

            client.println(); // Línea en blanco final de la respuesta
            break; // Sale del bucle porque ya terminó la respuesta
          } else {
            currentLine = ""; // Reinicia la línea actual
          }
        } else if (c != '\r') {
          currentLine += c; // Acumula caracteres que no sean retorno de carro
        }
      }
    }

    // Limpia y desconecta al cliente después de atenderlo
    header = "";
    client.stop();
    Serial.println("Cliente desconectado.");
  }
}
