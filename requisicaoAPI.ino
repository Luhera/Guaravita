#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

const char* ssid = "Senac-Mesh";
const char* password = "09080706";

const int DHTpin = 4; // Substitua pelo pino de dados real conectado ao sensor DHT
DHT dht(DHTpin, DHT11); // Objeto não-constante para chamar funções membro

const int ky037Pin = 34; // Pino analógico para o sensor sonoro KY-037
const int ldrPin = 35;   // Pino analógico para o sensor de luminosidade LDR

char serverIP[] = "172.16.82.64"; // Substitua pelo endereço IP do seu servidor
const int serverPort = 8080;
const char* path = "/api/event";

String token = "BQPMNMZXRLJT"; // Substitua pelo seu token real

void setup() {
  Serial.begin(115200);
  dht.begin(); // Inicializar o sensor DHT

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("\nERRO DE CREDENCIAIS DE INTERNET, NAO CONECTADO");
  }
  Serial.println("\nConectado ao WiFi");
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
