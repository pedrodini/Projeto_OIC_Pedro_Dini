/**
 * UNIVERSIDADE PRESBITERIANA MACKENZIE
 * 
 * NOME: PEDRO VICTOR DINI SILVA DE PAULA
 * TIA: 31857345 
 * MATÉRIA: OBJETOS INTELIGENTES CONECTADOS 
 * TURMA: 05k
 * PROFESSOR: DR. WILIAN FRANCA COSTA
 * PROJETO: DOMÓTICA - AUTOMAÇÃO RESIDENCIAL (COZINHA)
 * 
 * 
   * ESTE PROJETO É DE AUTORIA PRÓPRIA. QUALQUER CÓPIA PRECISA SER REFERENCIADA. 
 * 
 * 
 */

// ---------- Inclusão de Bibliotecas --------------------- 
#include <ESP8266WiFi.h> // Placa do Microcontrolador ESP8266
#include <PubSubClient.h>  // Biblioteca do Publicador / Subscrito 
#include <Adafruit_Sensor.h> // Biblioteca do Sensor 
#include <DHT.h>
#include <DHT_U.h>
#include <Servo.h>

// --------------------------------------------------------

// ---------- Definições de Componentes ------------------- 

// Sensor de Temperatura e Umidade 
#define DHTPIN 2 
#define DHTTYPE DHT11 
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

// Sensor de Presença e Movimento e LED de acionamento 
#define pinPIR 4
#define LED1 5

// Atuador ServoMotor SG92R 
#define SERVO 0
Servo myservo;
  
// Mensagem do Buffer
#define MSG_BUFFER_SIZE  (50)


// --------------------------------------------------------

// --------- Configurações de Conexão WI-FI ---------------


const char* ssid = "Kingdom";
const char* password = "hamburguer10";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
char msg[MSG_BUFFER_SIZE];
int value = 0;


// ------------------------------------------------------------- 

void setup() {

  
// -----------------Luz de Emergência -------------------------------


  pinMode(16, OUTPUT); 

// -----------------Sensor de Movimento e Presença ------------------

  pinMode(pinPIR, INPUT);
  pinMode(LED1, OUTPUT);

// -----------------Sensor de Temperatura ---------------------------
  dht.begin();
  Serial.println(F("Sensor DHT11"));
  sensor_t sensor;
  

  dht.temperature().getSensor(&sensor);
  Serial.println(F("Temperatura"));
  Serial.print  (F("Sensor: ")); Serial.println(sensor.name);
  Serial.print  (F("Valor máximo: ")); Serial.print(sensor.max_value); Serial.println(F("°C")); 
  Serial.print  (F("Valor mínimo: ")); Serial.print(sensor.min_value); Serial.println(F("°C")); 
  Serial.print  (F("Resolução: ")); Serial.print(sensor.resolution); Serial.println(F("°C"));    
  Serial.println(F("------------------------------------"));

 
// -----------------Sensor de Umidade ---------------------------
  dht.humidity().getSensor(&sensor);

  Serial.println(F("Umidade")); 
  Serial.print  (F("Sensor: ")); Serial.println(sensor.name); 
  Serial.print  (F("Valor máximo: ")); Serial.print(sensor.max_value); Serial.println(F("%")); 
  Serial.print  (F("Valor mínimo: ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolução: ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  
  delayMS = sensor.min_delay / 1000;        

 // -----------------ServoMotor SG90 -----------------------------

  myservo.attach(SERVO); 
  

 // -----------------Configuração Wi-FI---------------------------

 
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}


void setup_wifi() {

  delay(10);
  Serial.println("");
  Serial.print("Conectando com: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WI-FI CONECTADO! ");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem Recebida!  [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  Serial.println("");
  if ((char)payload[0] == 'A') {
    myservo.write(0);
    snprintf (msg, MSG_BUFFER_SIZE, "Janela Fechada!"); 
    Serial.print("Publica mensagem: ");
    Serial.println(msg);
    client.publish("cozinha/janela", msg);   
  }
  Serial.println("");
  if ((char)payload[0] == 'a') {
    myservo.write(180);
    snprintf (msg, MSG_BUFFER_SIZE, "Janela Aberta!"); 
    Serial.print("Publica mensagem: ");
    Serial.println(msg);
    client.publish("cozinha/janela", msg); 
  }

  Serial.println("");
  if ((char)payload[0] == 'E') {
    digitalWrite(16, HIGH);
    snprintf (msg, MSG_BUFFER_SIZE, "A luz de emergência está ligada");
    Serial.print("Publica mensagem: ");
    Serial.println(msg);
    client.publish("cozinha/emergencia", msg);
  }
  Serial.println("");
  if ((char)payload[0] == 'e') {
    digitalWrite(16, LOW);
    snprintf (msg, MSG_BUFFER_SIZE, "A luz de emergência desligada");
    Serial.print("Publica mensagem: ");
    Serial.println(msg);
    client.publish("cozinha/emergencia", msg);
  }

}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Aguardando Coenxão MQTT...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado");
      client.subscribe("cozinha/publisher");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" Tente novamente em 5 segundos");
      delay(5000);
    }
  }
}

void loop() {
  
// Regras de Funcionamento PIR ------------------------------ 

  //Leitura do sensor de presença 
  int sinal_sensor = digitalRead(pinPIR);
  
  //Condição de movimento detectado
  if(sinal_sensor == HIGH){
    digitalWrite(LED1, HIGH);
    Serial.println("Movimento Detectado");
    client.publish("cozinha/movimento", msg);
    
  }
  else{
    digitalWrite(LED1, LOW); 
  }


// Regras de Funcionamento DHT11 ---------------------------- 
  delay(delayMS); 
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Erro na leitura da temperatura!"));
  }
  else {
    Serial.print(F("Temperatura: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    sprintf(msg,"%f",event.temperature);
    client.publish("cozinha/temperatura", msg);
  }
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Erro na leitura da umidade!"));
  }
  else {
    Serial.print(F("Umidade: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    sprintf(msg,"%f",event.relative_humidity);
    client.publish("cozinha/umidade", msg);
  }

  
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); 

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
