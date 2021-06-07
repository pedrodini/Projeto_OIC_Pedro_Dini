# AUTOMAÇÃO RESIDENCIAL - COZINHA 

# Informações do Autor 

Universidade Presbiteriana Mackenzie 
Nome: Pedro Victor Dini 
TIA: 31857345 
Disciplina: Objetos Inteligentes Conectados 
Profº: DR. Wilian Franca Costa 
Turma: 05K 

# Descrição do Projeto 

O Projeto desenvolvido tem como objetivo criar uma simulação de automação residencial (Domótica) precisamente o ambiente da cozinha. Diarimente somos confrontados com a mudança e evolução da tecnologia tornando-a parte indispensável do nosso convívio. Dessa maneira, neste projeto escolhi o ambiente da cozinha para que alguns processos possam ser autimatizados e controlados remotamente utilizando o protocolo MQTT. 

Como parte da simulação, os seguintes processos estão sendo contemplados: 
 - Controle de Temperatura
 - Controle de Umidade 
 - Controle de abertura e fechamento de janela 
 - Controle de movimento de presença 
 - Controle de acendimento automático de luz. 

Com a realização do experimento, temos um maior controle do ambiente da cozinha e automatização de processos manuais como o acendimento de luzes e abertura e fechamento de janelas. 

A montagem final deste projeto foi: 
![Circuito-montado](https://user-images.githubusercontent.com/64094060/120958743-b724d700-c72e-11eb-8b1a-199c20fa4ce9.jpeg)

* Para realização da simulação o Servomotor foi utilizadod como representação de uma Janela (Abrindo quando está na rotação 180 e fechando quando está na rotação 0). 

# Componentes Utilizados 
 - 1 Placa NodeMCU ESP8266 WI-FI
 - 1 Cabo USB 
 - 1 Sensor de Temperatura e Umidade DHT11 
 - 1 Sensor de Movimento e Presença PIR 
 - 1 Servomotor SG90 
 - 2 LEDs amarelos 
 - 2 Resistores 270 Ohms 
 - 18 fios tipo macho-macho
 - 3 fios tipo fêmea-fêmea
 - Arduino IDE 
 - MQTTBox (Web) 
 - MQTT Dash (Mobile)

# Circuito esquematiza  

Para realização da simulação virtual do circuito elaborado, foi utilizada a plataforma Circuits.io 

![Circuito-PedroDini](https://user-images.githubusercontent.com/64094060/120958356-f1da3f80-c72d-11eb-8058-28d1c4c5eb2f.PNG)

* No circuito acima, foi utilizado o DHT22 e no protótipo real o DHT11. Essa mudança não impacta em nada o funcionamento de ambos os circuitos uma vez que a diferença entre eles está nessa "perna" a mais que o DHT22 tem, mas que é apenas ligado à um resistor que retorna para a porta lógica novamente. Ou seja o formato dos dois sensores são identicos (1 entrada lógica, 1 GND e 1 VCC). 


# Descrição Técnica 

Para a implementação do código foi utilizado a IDE do Arduino, por ter uma facilidade maior na realização das simulações e por eu já possuir conhecimento na linguagem C++. 

As seguintes bibliotecas foram incluídas para que o circuito funcionasse: 
 - <ESP8266WiFi.h> : Responsável por trazer os setups necessários para o bom funcionamento do Microcontrolador ESP8266 
 - <PubSubClient.h>: Responsável pela comunicação MQTT e pelo qual os métodos de publicação e subscrição foram feitos 
 - <Adafruit_Sensor.h>: Responspavel pelos setups e desenvolvimentos do Sensor PIR 
 - <DHT.h>: Responsável pelos setups e desenvolvimentos do sensor de temperatura e umidade DHT11 
 - <Servo.h>: Responsável pelos setups e desenvolvimentos do Servomotor SG90 


Com o intuito de comprovar a eficácia do desenvolvimento realizado e comprovar a realização da comunicação do MQTT (Message Queuing Telemetry Transport) responsável por habilitar o controle remoto dos despositivos inteligentes e controlar tanto o _publisher_ como o _subscriber_  foram utilizados os seguintes serviços: 

**MQTTBox**
O MQTTBox é uma extensão do Google Chrome, capaz de acompanhar em tempo real as ações do _publisher_ e do _subscriber_ que foram configuradas no broker (broker.mqtt-dashboard.com.) 

![MQTTBox - Pedro](https://user-images.githubusercontent.com/64094060/120960508-5f886a80-c732-11eb-8b9b-bb150e0d02d1.PNG)


**MQTT Dash**
O MQTT Dash é um aplicativo Mobile Android, no qual assim como o MQTTBox é possível ser feito o acompanhamento em tempo real dos tópicos do dispositivo elaborado. Porém adicionamente, possui funções interativas. No caso do meu projeto, adicionei 6 itens na tela inicial sendo: 
 - Controle de Temperatura (Cº)
 - Controle de Umidade (%) 
 - Status textual da janela (Aberta ou Fechada) 
 - Botão de abertura e fechamento da Janela (Switch) 
 - Status textual da Luz de emergência (Ligada ou Desligada) 
 - Botão de ligar e desligar a Luz  (Switch) 

![MQTT Dash](https://user-images.githubusercontent.com/64094060/120960510-61eac480-c732-11eb-97dd-2e436da51520.jpeg)


# Resultados Finais 

Após a conclusão tanto da montagem como do desenvolvimento do código, posso garantir o funcionamento correto do circuito. A Comunicação via protocolo MQTT de igual forma foi realizado com sucesso, nos mostrando que pode ser uma forma aliada nos desenvolvimentos em IoT, garantindo a execução rápida, eficaz e segura. 






