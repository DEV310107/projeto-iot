#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "iot"; // Coloque o nome da sua rede Wi-Fi
const char* password = "iotsenai502"; // Coloque a senha da sua rede

WebServer server(80);

// Definição dos pinos dos LEDs
#define RED  33
#define YELLOW 25
#define GREEN 26

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi conectado!");
  Serial.println(WiFi.localIP());
  
  server.on("/", []() {
    server.send(200, "text/html", R"rawliteral(
      <html>
        <head><title>Semáforo</title></head>
        <body>
          <h1>Controle do Semáforo</h1>
          <button onclick="fetch('/red')">Vermelho</button>
          <button onclick="fetch('/yellow')">Amarelo</button>
          <button onclick="fetch('/green')">Verde</button>
        </body>
      </html>
    )rawliteral");
  });

  server.on("/red", []() {
    digitalWrite(RED, HIGH);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, LOW);
    server.send(200, "text/plain", "Vermelho ligado");
  });

  server.on("/yellow", []() {
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(GREEN, LOW);
    server.send(200, "text/plain", "Amarelo ligado");
  });

  server.on("/green", []() {
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, HIGH);
    server.send(200, "text/plain", "Verde ligado");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
