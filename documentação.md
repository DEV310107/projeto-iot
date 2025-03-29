# Documentação do Projeto IoT - Sistema de Semáforos com Web Server

### Simulador
- https://wokwi.com/projects/426726437704652801

## Introdução

Este projeto tem como objetivo criar um sistema de controle para três semáforos utilizando um ESP32. O dispositivo gerencia os LEDs dos semáforos e hospeda um servidor web, permitindo que o usuário controle o funcionamento dos semáforos remotamente por meio de uma interface web simples e intuitiva. Isso possibilita um gerenciamento eficiente do tráfego em tempo real.

## Componentes Utilizados

Para construir este projeto, utilizamos:

- **ESP32** - O cérebro do sistema, responsável pelo controle dos semáforos e a comunicação via web.
- **LEDs (vermelho, amarelo e verde)** - Representam os sinais dos semáforos.
- **Resistores de 220Ω** - Para limitar a corrente nos LEDs.
- **Jumpers e Protoboard** - Para conexões elétricas.

## Conexões dos Semáforos

Os LEDs foram conectados ao ESP32 da seguinte maneira:

| Semáforo | LED Verde | LED Amarelo | LED Vermelho |
| --- | --- | --- | --- |
| 1 | GPIO 14 | GPIO 12 | GPIO 27 |
| 2 | GPIO 26 | GPIO 25 | GPIO 36 |
| 3 | GPIO 35 | GPIO 32 | GPIO 34 |

## Como Funciona

1. O ESP32 se conecta à rede WiFi configurada.
2. Ele configura os pinos dos LEDs como saídas para controle dos semáforos.
3. Um servidor web é iniciado, permitindo que o usuário acesse a interface de controle via navegador.
4. O usuário pode visualizar o estado atual dos semáforos e alternar entre ligado/desligado com um clique.
5. O ESP32 gerencia automaticamente o ciclo dos semáforos, garantindo que o trânsito flua corretamente.
6. Opcionalmente, sensores podem ser adicionados para detectar o fluxo de veículos e otimizar os tempos de sinalização.

## Código-Fonte

O programa está estruturado da seguinte forma:

- **Conexão WiFi** - Permite que o ESP32 seja acessado remotamente.
- **Configuração dos pinos** - Define os LEDs como saídas e inicializa os estados.
- **Controle do ciclo dos semáforos** - Alternância entre verde, amarelo e vermelho em tempos programados.
- **Servidor web** - Exibe a interface de controle ao usuário e recebe comandos para alternar o estado dos semáforos.

```arduino
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

```

### Funções Principais

- **configurarSemaforos()** - Define os pinos dos LEDs como saída.
- **desligarSemaforos()** - Desliga todos os LEDs.
- **loopSemaforo()** - Controla a lógica de funcionamento dos semáforos.
- **handleRoot()** - Exibe a página web com o status atual dos semáforos.
- **handleToggle()** - Alterna entre ativado e desativado.
- **conectarWiFi()** - Gerencia a conexão do ESP32 com a rede WiFi.

## Interface Web

A interface web permite o controle do sistema de forma remota. Ela exibe:

- O estado atual dos semáforos (ligado/desligado).
- Um botão para alternar o funcionamento do sistema.
- Mensagens de status para informar ao usuário o que está acontecendo.

## Imagens do Protótipo

### Protótipo Montado na Protoboard

As imagens acima mostram a montagem do projeto em uma protoboard, utilizando um ESP32 e LEDs para representar os semáforos. Os resistores garantem que a corrente esteja dentro dos limites adequados para os LEDs. Os jumpers conectam os componentes ao ESP32, permitindo o controle via código.

- **ESP32** - O cérebro do sistema, responsável pelo controle dos semáforos e a comunicação via web.
- **LEDs (vermelho, amarelo e verde)** - Representam os sinais dos semáforos.
- **Resistores de 220Ω** - Para limitar a corrente nos LEDs.
- **Jumpers e Protoboard** - Para conexões elétricas.
- **Fonte de alimentação 5V** - Para alimentar o ESP32.

## Conexões dos Semáforos

Os LEDS foram conectados da seguinte maneira:

| Semáforo | LED Verde | LED Amarelo | LED Vermelho |
| --- | --- | --- | --- |
| 1 | GPIO 14 | GPIO 12 | GPIO 27 |
| 2 | GPIO 26 | GPIO 25 | GPIO 36 |
| 3 | GPIO 35 | GPIO 32 | GPIO 34 |

## Como Funciona

1. O ESP32 se conecta à rede WiFi.
2. Ele configura os pinos dos LEDs como saídas.
3. Um servidor web é iniciado, permitindo que o usuário acesse a interface de controle.
4. O usuário pode visualizar o estado atual dos semáforos e alternar entre ligado/desligado com um clique.
5. O ESP32 gerencia o ciclo dos semáforos, garantindo que o trânsito flua corretamente.

## Código-Fonte

O programa está estruturado da seguinte forma:

- **Conexão WiFi** - Para acesso remoto ao sistema.
- **Configuração dos pinos** - Definição dos LEDs como saídas.
- **Controle do ciclo dos semáforos** - Alternância entre verde, amarelo e vermelho.
- **Servidor web** - Exibe a interface de controle ao usuário.

### Funções Principais

- **configurarSemaforos()** - Define os pinos dos LEDs como saída.
- **desligarSemaforos()** - Desliga todos os LEDs.
- **loopSemaforo()** - Controla o funcionamento dos semáforos.
- **handleRoot()** - Exibe a página web com o status dos semáforos.
- **handleToggle()** - Alterna entre ativado e desativado.

# Projeto Físico:

![image.png](https://github.com/DEV310107/projeto-iot/blob/main/1.jpg)

![image.png](https://github.com/DEV310107/projeto-iot/blob/main/2.jpg)
