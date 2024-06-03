Monitoramento Ambiental e Controle de LEDs com IoT
Visão Geral

Este projeto IoT implementa um sistema completo para monitorar o ambiente e controlar LEDs com base em dados coletados por sensores. A solução utiliza um microcontrolador compatível com Wi-Fi para coletar dados de temperatura, luminosidade e som, e envia esses dados para um servidor via HTTP POST a cada 25 segundos. Além disso, o sistema controla o estado de três conjuntos de LEDs, alterando sua cor de acordo com as leituras dos sensores, fornecendo visualização instantânea das condições do ambiente.

Funcionalidades

Aquisição de dados:
Coleta temperatura, luminosidade e nível de som em tempo real.
Utiliza sensores DHT11, LDR e KY-037, respectivamente.
Conversão de leituras em valores digitais para processamento.
Comunicação com servidor:
Estabelece conexão Wi-Fi com a rede configurada.
Envia dados coletados para um servidor via HTTP POST a cada 25 segundos.
Formato JSON para fácil integração com APIs e sistemas backend.
Controle de LEDs:
Controla três conjuntos de LEDs (vermelho, verde e azul).
A cor dos LEDs indica as condições do ambiente:
Temperatura: Verde (<=23°C), Amarelo (23°C - 24.5°C), Vermelho (>=24.6°C).
Luminosidade: Verde (<=2399), Amarelo (2399 - 2900), Vermelho (>=2901).
Nível de som: Verde (<=60), Amarelo (60 - 89), Vermelho (>=90).
Flexibilidade:
Código facilmente adaptável para diferentes tipos de sensores e aplicações.
Integração com diversos servidores e plataformas IoT.
Requisitos

Hardware:
Microcontrolador compatível com Wi-Fi (ESP32, por exemplo).
Sensor DHT11 (temperatura e umidade).
Sensor LDR (luminosidade).
Sensor KY-037 (som).
Três conjuntos de LEDs (vermelho, verde e azul).
Cabos de conexão.
Software:
IDE Arduino.
Bibliotecas: WiFi.h, HTTPClient.h, DHT.h.
Rede:
Rede Wi-Fi com acesso à internet para comunicação com o servidor.
Servidor:
Servidor web capaz de receber dados JSON via HTTP POST (desenvolvido separadamente).
Benefícios

Monitoramento ambiental completo e em tempo real.
Controle visual intuitivo das condições do ambiente através de LEDs.
Flexibilidade para diferentes aplicações e integração com diversos sistemas.
Solução econômica e eficiente para diversos ambientes.
Implementação

O código completo do projeto está disponível para download e implementação. A documentação detalhada fornece instruções passo a passo para configuração e uso do sistema. Para integração com um servidor, é necessário desenvolver uma API personalizada para receber e processar os dados enviados pelo microcontrolador.

Conclusão

Este projeto IoT oferece uma solução completa e versátil para monitorar o ambiente e controlar LEDs com base em dados de sensores. Com sua flexibilidade e simplicidade, o sistema pode ser facilmente adaptado para diversas aplicações, desde ambientes domésticos inteligentes até monitoramento industrial e pesquisas científicas.
