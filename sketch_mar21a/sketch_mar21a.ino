void setup#include <WiFi.h>  // Inclui a biblioteca para conexão WiFi no ESP32
#include <WebServer.h>  // Inclui a biblioteca para criar um servidor web

// Definição das credenciais da rede WiFi
const char* ssid = "iot";  // Nome da rede WiFi
const char* password = "iotsenai502";  // Senha da rede WiFi

// Criação do servidor web na porta 80
WebServer server(80);  // Instancia um servidor web na porta 80

// Definição dos pinos dos LEDs dos semáforos
const int semaforo1Verde = 14;  // Pino do LED verde do semáforo 1
const int semaforo1Amarelo = 12;  // Pino do LED amarelo do semáforo 1
const int semaforo1Vermelho = 27;  // Pino do LED vermelho do semáforo 1

const int semaforo2Verde = 26;  // Pino do LED verde do semáforo 2
const int semaforo2Amarelo = 25;  // Pino do LED amarelo do semáforo 2
const int semaforo2Vermelho = 36;  // Pino do LED vermelho do semáforo 2

const int semaforo3Verde = 35;  // Pino do LED verde do semáforo 3
const int semaforo3Amarelo = 32;  // Pino do LED amarelo do semáforo 3
const int semaforo3Vermelho = 34;  // Pino do LED vermelho do semáforo 3

// Variável para controlar o estado dos semáforos
bool semaforosAtivos = true;  // Indica se os semáforos estão ativos ou não

// Função para configurar os pinos dos semáforos como saída
void configurarSemaforos() {
  pinMode(semaforo1Verde, OUTPUT);  // Configura o pino do LED verde do semáforo 1 como saída
  pinMode(semaforo1Amarelo, OUTPUT);  // Configura o pino do LED amarelo do semáforo 1 como saída
  pinMode(semaforo1Vermelho, OUTPUT);  // Configura o pino do LED vermelho do semáforo 1 como saída
  pinMode(semaforo2Verde, OUTPUT);  // Configura o pino do LED verde do semáforo 2 como saída
  pinMode(semaforo2Amarelo, OUTPUT);  // Configura o pino do LED amarelo do semáforo 2 como saída
  pinMode(semaforo2Vermelho, OUTPUT);  // Configura o pino do LED vermelho do semáforo 2 como saída
  pinMode(semaforo3Verde, OUTPUT);  // Configura o pino do LED verde do semáforo 3 como saída
  pinMode(semaforo3Amarelo, OUTPUT);  // Configura o pino do LED amarelo do semáforo 3 como saída
  pinMode(semaforo3Vermelho, OUTPUT);  // Configura o pino do LED vermelho do semáforo 3 como saída
}

// Função para desligar todos os LEDs dos semáforos
void desligarSemaforos() {
  digitalWrite(semaforo1Verde, LOW);  // Desliga o LED verde do semáforo 1
  digitalWrite(semaforo1Amarelo, LOW);  // Desliga o LED amarelo do semáforo 1
  digitalWrite(semaforo1Vermelho, LOW);  // Desliga o LED vermelho do semáforo 1
  digitalWrite(semaforo2Verde, LOW);  // Desliga o LED verde do semáforo 2
  digitalWrite(semaforo2Amarelo, LOW);  // Desliga o LED amarelo do semáforo 2
  digitalWrite(semaforo2Vermelho, LOW);  // Desliga o LED vermelho do semáforo 2
  digitalWrite(semaforo3Verde, LOW);  // Desliga o LED verde do semáforo 3
  digitalWrite(semaforo3Amarelo, LOW);  // Desliga o LED amarelo do semáforo 3
  digitalWrite(semaforo3Vermelho, LOW);  // Desliga o LED vermelho do semáforo 3
}

// Função para controlar o ciclo dos semáforos
void loopSemaforo() {
  if (!semaforosAtivos) return;  // Se os semáforos estiverem desligados, sai da função
  
  // Ciclo de controle dos semáforos
  digitalWrite(semaforo2Verde, LOW);  // Desliga o LED verde do semáforo 2
  digitalWrite(semaforo1Amarelo, HIGH);  // Liga o LED amarelo do semáforo 1
  digitalWrite(semaforo2Amarelo, HIGH);  // Liga o LED amarelo do semáforo 2
  delay(2000);  // Aguarda 2 segundos
  
  // Semáforos 1 e 2 vermelhos, Semáforo 3 verde
  digitalWrite(semaforo1Amarelo, LOW);  // Desliga o LED amarelo do semáforo 1
  digitalWrite(semaforo2Amarelo, LOW);  // Desliga o LED amarelo do semáforo 2
  digitalWrite(semaforo1Vermelho, HIGH);  // Liga o LED vermelho do semáforo 1
  digitalWrite(semaforo2Vermelho, HIGH);  // Liga o LED vermelho do semáforo 2
  digitalWrite(semaforo3Vermelho, LOW);  // Desliga o LED vermelho do semáforo 3
  digitalWrite(semaforo3Verde, HIGH);  // Liga o LED verde do semáforo 3
  delay(5000);  // Aguarda 5 segundos
  
  // Amarelo Semáforo 3
  digitalWrite(semaforo3Verde, LOW);  // Desliga o LED verde do semáforo 3
  digitalWrite(semaforo3Amarelo, HIGH);  // Liga o LED amarelo do semáforo 3
  delay(2000);  // Aguarda 2 segundos
  
  // Volta ao início
  digitalWrite(semaforo1Vermelho, LOW);  // Desliga o LED vermelho do semáforo 1
  digitalWrite(semaforo2Vermelho, LOW);  // Desliga o LED vermelho do semáforo 2
  digitalWrite(semaforo3Amarelo, LOW);  // Desliga o LED amarelo do semáforo 3
}

// Função para tratar a rota raiz do servidor web
void handleRoot() {
  String html = "<html><body><h1>Controle de Semáforos</h1>";  // Cria o cabeçalho HTML
  html += "<p>Status: " + String(semaforosAtivos ? "Ligado" : "Desligado") + "</p>";  // Exibe o status dos semáforos
  html += "<a href='/toggle'><button>Alternar Estado</button></a>";  // Botão para alternar o estado dos semáforos
  html += "</body></html>";  // Fecha o HTML
  server.send(200, "text/html", html);  // Envia a resposta ao cliente
}

// Função para alternar o estado dos semáforos
void handleToggle() {
  semaforosAtivos = !semaforosAtivos;  // Alterna o estado dos semáforos
  if (!semaforosAtivos) {
    desligarSemaforos();  // Desliga os semáforos se estiverem inativos
  }
  server.sendHeader("Location", "/");  // Redireciona para a página inicial
  server.send(303);  // Envia o código de redirecionamento
}

// Função de configuração inicial
void setup() {
  Serial.begin(115200);  // Inicializa a comunicação serial
  configurarSemaforos();  // Configura os pinos dos semáforos
  desligarSemaforos();  // Desliga todos os LEDs dos semáforos

  WiFi.begin(ssid, password);  // Conecta ao WiFi com as credenciais fornecidas
  while (WiFi.status() != WL_CONNECTED) {  // Aguarda até que a conexão seja estabelecida
    delay(1000);  // Aguarda 1 segundo
    Serial.println("Conectando ao WiFi...");  // Exibe mensagem de conexão
  }
  Serial.println("WiFi conectado");  // Exibe mensagem de sucesso na conexão
  server.on("/", handleRoot);  // Define a função para a rota raiz
  server.on("/toggle", handleToggle);  // Define a função para alternar o estado
  server.begin();  // Inicia o servidor web
}

// Função principal de execução contínua
void loop() {
  server.handleClient();  // Trata as requisições do cliente
  loopSemaforo();  // Executa o ciclo dos semáforos
}
