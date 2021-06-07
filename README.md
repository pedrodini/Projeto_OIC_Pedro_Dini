# AUTOMAÇÃO RESIDENCIAL - COZINHA 

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










