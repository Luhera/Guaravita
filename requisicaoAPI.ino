#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

const char* ssid = "brisa-3352525";
const char* password = "ekcpuuew";

const int DHTpin = 2; // Substitua pelo pino de dados real conectado ao sensor DHT
DHT dht(DHTpin, DHT11); // Objeto não-constante para chamar funções membro

const int ky037Pin = 34; // Pino analógico para o sensor sonoro KY-037
const int ldrPin = 35;   // Pino analógico para o sensor de luminosidade LDR

const int ledRed1 = 5; // Pino do LED vermelho (LED1)
const int ledGreen1 = 18; // Pino do LED verde (LED1)
const int ledBlue1 = 19; // Pino do LED azul (LED1)

const int ledRed2 = 13; // Pino do LED vermelho (LED2)
const int ledGreen2 = 12; // Pino do LED verde (LED2)
const int ledBlue2 = 14; // Pino do LED azul (LED2)

const int ledRed3 = 26; // Pino do LED vermelho (LED3)
const int ledGreen3 = 25; // Pino do LED verde (LED3)
const int ledBlue3 = 33; // Pino do LED azul (LED3)

char serverIP[] = "192.168.0.12"; // Substitua pelo endereço IP do seu servidor
const int serverPort = 8080;
const char* path = "/api/event";

String token = "R4L4B1BIPW38"; // Substitua pelo seu token real

void setup() {
  Serial.begin(115200);
  dht.begin(); // Inicializar o sensor DHT

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("\nERRO DE CREDENCIAIS DE INTERNET, NAO CONECTADO");
  }
  Serial.println("\nConectado ao WiFi");

  pinMode(ledRed1, OUTPUT);
  pinMode(ledGreen1, OUTPUT);
  pinMode(ledBlue1, OUTPUT);

  pinMode(ledRed2, OUTPUT);
  pinMode(ledGreen2, OUTPUT);
  pinMode(ledBlue2, OUTPUT);

  pinMode(ledRed3, OUTPUT);
  pinMode(ledGreen3, OUTPUT);
  pinMode(ledBlue3, OUTPUT);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Ler temperatura do sensor DHT
    float temperature = dht.readTemperature();

    // Checar se houve falha na leitura e sair cedo (para evitar valores NaN)
    if (isnan(temperature)) {
      Serial.println("Falha ao ler do sensor DHT!");
      return;
   }

    // Ler valor do som do sensor sonoro KY-037
    int sound = analogRead(ky037Pin);

    // Ler valor de luminosidade do sensor LDR
    int luminosity = analogRead(ldrPin);

    // Temperatura:
    if (temperature <= 23.0) {
      // Verde
      digitalWrite(ledRed1, LOW);  
      digitalWrite(ledGreen1, HIGH);
      digitalWrite(ledBlue1, LOW);
    } else if ( temperature <= 24.5) {
      // Amarelo
      digitalWrite(ledRed1, LOW);
      digitalWrite(ledGreen1, LOW);
      digitalWrite(ledBlue1, HIGH);
    } else if (temperature >= 24.6) {
      // Vermelho
      digitalWrite(ledRed1, HIGH);
      digitalWrite(ledGreen1, LOW);
      digitalWrite(ledBlue1, LOW);
    }

    // Controlar LEDs de acordo com a luminosidade:
    if (luminosity <= 2399) {
      // Verde
      digitalWrite(ledRed2, LOW);
      digitalWrite(ledGreen2, HIGH);
      digitalWrite(ledBlue2, LOW);
    } else if (luminosity <= 2900) {
      // Amarelo
      digitalWrite(ledRed2, LOW);
      digitalWrite(ledGreen2, LOW);
      digitalWrite(ledBlue2, HIGH);
    } else if (luminosity >= 2901) {
      // Vermelho
      digitalWrite(ledRed2, HIGH);
      digitalWrite(ledGreen2, LOW);
      digitalWrite(ledBlue2, LOW);
    }

// Controlar LEDs de acordo com o som:
    if (sound >= 90) {
      // Vermelho
      digitalWrite(ledRed3, HIGH);
      digitalWrite(ledGreen3, LOW);
      digitalWrite(ledBlue3, LOW);
    } else if (sound <= 89) {
      // Amarelo
      digitalWrite(ledRed3, LOW);
      digitalWrite(ledGreen3, LOW);
      digitalWrite(ledBlue3, HIGH);
    } else if (sound <= 60) {
      // Verde
      digitalWrite(ledRed3, LOW);
      digitalWrite(ledGreen3, HIGH);
      digitalWrite(ledBlue3, LOW);
    }

    HTTPClient http;

    // Construir a URL do servidor
    String url = String("http://") + serverIP + ":" + String(serverPort) + path;

    http.begin(url.c_str());
    http.addHeader("Content-Type", "application/json");

    // Criar corpo JSON com os valores medidos
    String jsonBody = "{\"luminosity\":" + String(luminosity) +
                       ",\"sound\":" + String(sound) +
                       ",\"temperature\":" + String(temperature, 1) + // Formatar para 1 casa decimal
                       ",\"display\":{\"token\":\"" + token + "\"}}";

    int httpResponseCode = http.POST(jsonBody);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Erro ao enviar POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }

  delay(25000); // Enviar dados a cada 25 segundos
}
