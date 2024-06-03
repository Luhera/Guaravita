
Documentação de Especificação do Projeto IoT
Este documento descreve o projeto IoT implementado no código fornecido. O projeto visa monitorar o ambiente e controlar LEDs com base nas leituras dos sensores.

Visão Geral
O sistema coleta dados de temperatura, luminosidade e som do ambiente utilizando sensores DHT11, LDR e KY-037, respectivamente. Em seguida, envia esses dados para um servidor via HTTP POST a intervalos regulares. Além disso, o sistema controla o estado de três conjuntos de LEDs, alterando sua cor de acordo com as leituras dos sensores.

Requisitos do Sistema
Hardware:

Microcontrolador compatível com WiFi (ESP32, por exemplo)
Sensor DHT11 (temperatura e umidade)
Sensor LDR (luminosidade)
Sensor KY-037 (som)
Três conjuntos de LEDs (vermelho, verde e azul)
Cabos de conexão
Software:

IDE Arduino
Bibliotecas: WiFi.h, HTTPClient.h, DHT.h
Rede:

Rede Wi-Fi com acesso à internet (para comunicação com o servidor)
Servidor:

Servidor web capaz de receber dados JSON via HTTP POST (desenvolvido separadamente)
Arquitetura do Sistema
O sistema consiste em três módulos principais:

Módulo de Aquisição de Dados: Responsável por ler os sensores DHT11, LDR e KY-037, convertendo as leituras em valores digitais.
Módulo de Comunicação: Estabelece conexão Wi-Fi com a rede e envia os dados coletados para o servidor em formato JSON via HTTP POST.
Módulo de Controle de LEDs: Controla o estado (liga/desliga e cor) dos três conjuntos de LEDs com base nas leituras dos sensores.
Funcionamento do Sistema
Inicialização (função setup()):
Inicia a comunicação serial para depuração.
Inicializa o sensor DHT11.
Conecta-se à rede Wi-Fi utilizando as credenciais fornecidas (SSID e senha).
Configura todos os pinos utilizados pelos LEDs como saídas digitais.
Loop Principal (função loop()):
Verifica o status da conexão Wi-Fi.
Caso esteja conectado:
Lê a temperatura do sensor DHT11.
Lê o nível de som do sensor KY-037.
Lê o nível de luminosidade do sensor LDR.
Controla a cor do primeiro conjunto de LEDs de acordo com a temperatura:
Verde: temperatura <= 23.0°C
Amarelo: temperatura entre 23.0°C e 24.5°C
Vermelho: temperatura >= 24.6°C
Controla a cor do segundo conjunto de LEDs de acordo com a luminosidade:
Verde: luminosidade <= 2399
Amarelo: luminosidade entre 2399 e 2900
Vermelho: luminosidade >= 2901
Controla a cor do terceiro conjunto de LEDs de acordo com o nível de som:
Verde: nível de som <= 60
Amarelo: nível de som entre 60 e 89
Vermelho: nível de som >= 90
Cria um objeto cliente HTTP para comunicação com o servidor.
Constrói a URL completa do servidor incluindo IP, porta e caminho da API.
Define o cabeçalho HTTP para o tipo de conteúdo (JSON).
Monta um corpo JSON contendo os valores de temperatura, luminosidade, som e um token de autenticação.
Envia uma requisição POST para o servidor com o corpo JSON contendo os dados dos sensores.
Verifica o código de resposta da requisição. Se for positivo, imprime o código e a resposta do servidor. Caso contrário, imprime uma mensagem de erro.
Libera os recursos do cliente HTTP.
Aguarda 25 segundos antes de repetir o loop principal.
Considerações
O código fornecido assume que os sensores estão conectados aos pinos corretos conforme definido pelas constantes.
O servidor precisa implementar uma API para receber dados JSON via HTTP POST.
O token de autenticação utilizado no código precisa ser configurado no servidor para validação.
Este documento fornece uma visão geral do projeto IoT implementado no código. Para implementação e uso efetivo, é necessário realizar a configuração do servidor e adequar o código às necessidades específicas do ambiente de uso.
