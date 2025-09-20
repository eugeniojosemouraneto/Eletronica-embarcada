# Roteiro de Aprendizagem: Eletrônica Embarcada para Impressoras 3D (Foco em Hardware)

---

### Projeto 1: Entradas Digitais: Debounce de Botão por Hardware

- **Módulo:** Fundamentos
- **Objetivo:** Implementar e validar um circuito de debounce de hardware usando um filtro RC e um Inversor Schmitt Trigger, e controlar uma ação via interrupção.
- **Pré-requisitos:**
  - Leitura de esquemáticos básicos
  - Conceito de Interrupções
- **Hardware Mínimo:**
  - ATmega328P ou Arduino Uno
  - Botão (push-button)
  - Resistor 10kΩ, Resistor 1kΩ
  - Capacitor cerâmico 100nF (0.1µF)
  - Circuito Integrado 74HC14 (Inversor Schmitt Trigger Hex)
  - LED e resistor 220Ω
- **Tempo Estimado:** 5 horas
- **Dificuldade:** 2/5
- **Dependências:** Nenhuma
- **Passos Principais (Milestones):**
  - Montar o circuito de debounce de hardware: O botão carrega/descarrega o capacitor através de um resistor (filtro RC).
  - A saída do filtro RC é conectada à entrada de uma das portas do 74HC14.
  - A saída "limpa" do Schmitt Trigger é conectada ao pino de interrupção externa (INT0/INT1) do microcontrolador.
  - Escrever uma ISR simples que apenas define um flag para indicar que o botão foi pressionado.
  - No loop principal, verificar o flag e alternar o estado do LED.
- **Entregáveis:**
  - Foto do circuito montado na protoboard.
  - Código-fonte funcional e comentado.
  - Vídeo curto mostrando o acionamento limpo, sem repiques.
- **Testes de Validação:**
  - O LED deve alternar seu estado uma única vez por clique, de forma perfeitamente consistente.
  - Observar com um osciloscópio (se disponível) o sinal ruidoso antes do Schmitt Trigger e o sinal limpo depois.
- **Metas Avançadas (Stretch Goals):**
  - Comparar este método com uma implementação de debounce puramente por software e analisar as diferenças no uso da CPU e na complexidade do código.
- **Observações:** Esta abordagem resolve o problema do "bounce" no hardware, resultando em um sinal de entrada perfeito para o microcontrolador e simplificando o software.

---

### Projeto 2: Saídas PWM: Controle de Brilho de LED com Timer

- **Módulo:** Fundamentos
- **Objetivo:** Gerar um sinal PWM (Pulse Width Modulation) via hardware para controlar a intensidade de um LED, manipulando os registradores do Timer.
- **Pré-requisitos:**
  - Configuração de Timers (Modo Normal/CTC)
- **Hardware Mínimo:**
  - ATmega328P ou Arduino Uno
  - LED
  - Resistor 220Ω
- **Tempo Estimado:** 4 horas
- **Dificuldade:** 1/5
- **Dependências:** Nenhuma
- **Passos Principais (Milestones):**
  - Configurar um Timer (Timer0, 1 ou 2) para o modo Fast PWM.
  - Configurar os bits COMnx para saída não-invertida no pino OCnx.
  - Ajustar o prescaler para uma frequência de PWM adequada (>100 Hz para evitar flicker).
  - Escrever um código que varia o valor do registrador de comparação (OCRnx) para alterar o duty cycle de 0% a 100%.
- **Entregáveis:**
  - Código-fonte que faz o LED pulsar (fade in/out) suavemente.
  - Explicação breve dos registradores configurados (TCCRxA, TCCRxB, OCRnx).
- **Testes de Validação:**
  - O brilho do LED varia visivelmente de totalmente apagado a brilho máximo.
  - Medir com um multímetro a tensão média no pino do LED, que deve variar proporcionalmente ao duty cycle.
- **Metas Avançadas (Stretch Goals):**
  - Controlar um LED RGB, usando três canais PWM distintos.
  - Receber o valor do duty cycle via comunicação serial.
- **Observações:** Este projeto já utiliza uma solução de hardware (o periférico Timer) para uma tarefa que seria muito ineficiente de se fazer por software ("bit-banging").

---

### Projeto 3: Comunicação Serial: Echo e Controle via UART

- **Módulo:** Fundamentos
- **Objetivo:** Estabelecer comunicação serial (UART) para enviar e receber dados entre o microcontrolador e um computador.
- **Pré-requisitos:**
  - Conceitos básicos de comunicação serial (baud rate, start/stop bits)
- **Hardware Mínimo:**
  - ATmega328P ou Arduino Uno
  - Computador com monitor serial (IDE do Arduino, PuTTY, etc.)
- **Tempo Estimado:** 3 horas
- **Dificuldade:** 1/5
- **Dependências:** Projeto 2
- **Passos Principais (Milestones):**
  - Configurar os registradores da UART (UBRR, UCSR) para um baud rate padrão (e.g., 9600).
  - Implementar funções para enviar um caractere e uma string.
  - Implementar uma função para receber um caractere (com verificação de buffer).
  - Criar um programa 'echo': tudo que for recebido é enviado de volta.
  - Expandir para controlar o LED do projeto 2 (e.g., enviar 'L100' para 100% de brilho).
- **Entregáveis:**
  - Código-fonte do 'echo' e do controle de LED.
  - Screenshot do monitor serial mostrando a comunicação.
- **Testes de Validação:**
  - Caracteres enviados do computador são imediatamente exibidos de volta.
  - Enviar 'L255' acende o LED no brilho máximo, 'L0' apaga.
- **Metas Avançadas (Stretch Goals):**
  - Criar um buffer circular para recepção de dados para evitar perda de caracteres.
  - Implementar um parser de comandos mais robusto.
- **Observações:** A comunicação UART é a base para receber comandos G-code na impressora.

---

### Projeto 4: Entradas Analógicas: Leitura de Potenciômetro com ADC

- **Módulo:** Fundamentos
- **Objetivo:** Ler um valor de tensão analógica usando o Conversor Analógico-Digital (ADC) e mapear o resultado para uma ação.
- **Pré-requisitos:**
  - Conceito de tensão e divisor de tensão
- **Hardware Mínimo:**
  - ATmega328P ou Arduino Uno
  - Potenciômetro 10kΩ
- **Tempo Estimado:** 3 horas
- **Dificuldade:** 1/5
- **Dependências:** Projetos 2, 3
- **Passos Principais (Milestones):**
  - Configurar os registradores do ADC (ADMUX, ADCSRA) para selecionar o canal e a referência de tensão.
  - Iniciar uma conversão e aguardar o resultado.
  - Ler o valor de 10 bits do resultado (ADCL, ADCH).
  - Mapear o valor lido (0-1023) para o duty cycle do PWM (0-255) do projeto 2.
- **Entregáveis:**
  - Código que permite controlar o brilho de um LED girando o potenciômetro.
  - Enviar o valor lido (0-1023) pela serial (projeto 3) para depuração.
- **Testes de Validação:**
  - Girar o potenciômetro de um extremo ao outro causa uma variação suave do brilho do LED de 0% a 100%.
  - O valor no monitor serial corresponde à posição do potenciômetro.
- **Metas Avançadas (Stretch Goals):**
  - Implementar leitura contínua usando a interrupção de conversão completa do ADC.
  - Filtrar o sinal com média móvel para reduzir ruído.
- **Observações:** Base para a leitura de sensores analógicos, como os termistores.

---

### Projeto 5: Memória Não-Volátil: Salvar e Ler Dados da EEPROM

- **Módulo:** Fundamentos
- **Objetivo:** Aprender a gravar e ler dados na memória EEPROM interna do microcontrolador para que persistam após um reset.
- **Pré-requisitos:**
  - Manipulação de variáveis e ponteiros em C
- **Hardware Mínimo:**
  - ATmega328P ou Arduino Uno
- **Tempo Estimado:** 4 horas
- **Dificuldade:** 2/5
- **Dependências:** Projetos 1, 4
- **Passos Principais (Milestones):**
  - Entender o processo de escrita e leitura da EEPROM (registradores de endereço, dados e controle).
  - Criar funções para escrever e ler um byte em um endereço específico.
  - Modificar o projeto 4 para que o último valor de brilho do LED seja salvo na EEPROM quando um botão é pressionado.
  - Ao ligar, o programa deve ler o valor da EEPROM e restaurar o brilho do LED.
- **Entregáveis:**
  - Código-fonte que salva e restaura o estado do LED.
  - Vídeo mostrando: ajuste do brilho, reset do microcontrolador, e o LED reacendendo com o brilho anterior.
- **Testes de Validação:**
  - Após desligar e ligar a placa, o LED assume o brilho que foi salvo.
  - A leitura de um endereço da EEPROM retorna o último valor escrito nele.
- **Metas Avançadas (Stretch Goals):**
  - Criar funções para salvar e ler tipos de dados maiores (int, float, structs).
  - Implementar um sistema de verificação (checksum) para garantir a integridade dos dados salvos.
- **Observações:** Usado em impressoras para salvar configurações como PID, offsets de eixos, etc.

---

### Projeto 6: Controle de Motor de Passo: Full-step Básico

- **Módulo:** Motores de Passo
- **Objetivo:** Controlar um motor de passo unipolar ou bipolar em modo full-step, acionando suas bobinas em sequência.
- **Pré-requisitos:**
  - Conceitos básicos de funcionamento de motores de passo
- **Hardware Mínimo:**
  - ATmega328P ou Arduino Uno
  - Motor de passo (NEMA 17 é ideal)
  - Driver de motor (ULN2003 para unipolar, L298N para bipolar)
  - Fonte de alimentação externa para o motor (e.g., 12V)
- **Tempo Estimado:** 6 horas
- **Dificuldade:** 2/5
- **Dependências:** Nenhuma
- **Passos Principais (Milestones):**
  - Identificar os fios das bobinas do motor.
  - Conectar o motor ao driver e o driver ao microcontrolador.
  - Escrever a sequência de acionamento para o modo full-step.
  - Criar uma função `step()` que avança o motor um passo.
  - Fazer o motor girar continuamente em uma direção e depois na outra.
- **Entregáveis:**
  - Código-fonte para girar o motor.
  - Diagrama de conexão.
  - Vídeo do motor girando em ambos os sentidos.
- **Testes de Validação:**
  - O motor gira de forma audível e visível.
  - Inverter a sequência de acionamento inverte a direção de rotação.
- **Metas Avançadas (Stretch Goals):**
  - Implementar modo half-step para dobrar a resolução.
  - Controlar a velocidade alterando o delay entre os passos.
- **Observações:** Use uma fonte externa para o motor. Nunca alimente um motor diretamente pelos pinos do microcontrolador.

---

### Projeto 7: Driver Dedicado: Controle com A4988/DRV8825

- **Módulo:** Motores de Passo
- **Objetivo:** Controlar um motor de passo usando um driver dedicado (step/dir), que abstrai a complexidade do acionamento das bobinas em hardware.
- **Pré-requisitos:**
  - Projeto 6
- **Hardware Mínimo:**
  - ATmega328P ou Arduino Uno
  - Motor de passo NEMA 17
  - Driver A4988 ou DRV8825
  - Capacitor eletrolítico (100µF) para a alimentação do motor
  - Fonte de alimentação externa (12V ou 24V)
- **Tempo Estimado:** 5 horas
- **Dificuldade:** 2/5
- **Dependências:** Projeto 6
- **Passos Principais (Milestones):**
  - Conectar o driver A4988/DRV8825 (pinos STEP, DIR, ENABLE, alimentação).
  - Ajustar a corrente do driver (Vref) de acordo com a especificação do motor.
  - Escrever um código que gera pulsos no pino STEP para mover o motor.
  - Controlar a direção alterando o nível lógico do pino DIR.
  - Testar diferentes configurações de micro-passos (pinos MS1, MS2, MS3).
- **Entregáveis:**
  - Código-fonte para controlar velocidade, direção e número de passos.
  - Vídeo mostrando o motor se movendo de forma mais suave em modo de micro-passo (e.g., 1/16).
- **Testes de Validação:**
  - O motor avança um micro-passo para cada pulso no pino STEP.
  - O motor gira para a esquerda com DIR=LOW e para a direita com DIR=HIGH.
- **Metas Avançadas (Stretch Goals):**
  - Criar uma biblioteca C simples para abstrair o controle do motor.
- **Observações:** O driver é um exemplo de abstração por hardware. Ajustar o Vref é CRÍTICO para evitar superaquecimento.

---

### Projeto 8: Movimento Controlado: Interrupção de Timer para Geração de Passos

- **Módulo:** Motores de Passo
- **Objetivo:** Usar uma interrupção de timer para gerar os pulsos para o driver do motor, permitindo um controle de velocidade preciso e não-bloqueante.
- **Pré-requisitos:**
  - Configuração de Timers em modo CTC
  - Uso de interrupções de timer
  - Projeto 7
- **Hardware Mínimo:**
  - Mesmo do projeto 7
- **Tempo Estimado:** 8 horas
- **Dificuldade:** 3/5
- **Dependências:** Projeto 7
- **Passos Principais (Milestones):**
  - Configurar um timer (e.g., Timer1) em modo CTC.
  - Calcular o valor de OCR1A para gerar uma interrupção na frequência desejada.
  - Na ISR do timer, gerar um pulso no pino STEP.
  - No loop principal, definir o número de passos a serem executados e habilitar o timer.
  - A ISR deve decrementar um contador de passos e desabilitar o timer quando chegar a zero.
- **Entregáveis:**
  - Código-fonte que move o motor por um número exato de passos a uma velocidade precisa sem usar `delay()`.
- **Testes de Validação:**
  - Comandar um movimento para 200 passos faz um motor de 1.8°/passo dar exatamente uma volta.
  - O loop principal fica livre para executar outras tarefas enquanto o motor se move.
- **Metas Avançadas (Stretch Goals):**
  - Variar o valor de OCR1A dinamicamente para alterar a velocidade em tempo real.
- **Observações:** Esta é a base do sistema de movimento de qualquer firmware de impressora 3D.

---

### Projeto 9: Aceleração Linear (Trapezoidal)

- **Módulo:** Motores de Passo
- **Objetivo:** Implementar um perfil de aceleração e desaceleração para o motor, evitando perda de passos e movimentos bruscos.
- **Pré-requisitos:**
  - Projeto 8
- **Hardware Mínimo:**
  - Mesmo do projeto 7
- **Tempo Estimado:** 12 horas
- **Dificuldade:** 4/5
- **Dependências:** Projeto 8
- **Passos Principais (Milestones):**
  - Definir parâmetros: aceleração, velocidade máxima.
  - Na ISR do timer, recalcular o próximo delay entre passos com base na velocidade atual.
  - Implementar a fase de aceleração: diminuir o delay a cada passo.
  - Implementar a fase de cruzeiro: manter o delay constante.
  - Implementar a fase de desaceleração: calcular quando começar a frear e aumentar o delay a cada passo.
- **Entregáveis:**
  - Código-fonte que implementa um movimento com perfil trapezoidal.
  - Gráfico (plotado a partir de dados da serial) mostrando a velocidade ao longo do tempo.
- **Testes de Validação:**
  - O som do motor deve ser suave ao iniciar e parar, sem trancos.
  - Movimentos longos devem atingir a velocidade máxima.
- **Metas Avançadas (Stretch Goals):**
  - Implementar aceleração com curva S (S-curve) para movimentos ainda mais suaves.
- **Observações:** A lógica de aceleração é uma tarefa de software que comanda o hardware (timer) de forma inteligente.

---

### Projeto 10: Coordenadas Cartesianas: Movimento de 2 Eixos (X-Y)

- **Módulo:** Motores de Passo
- **Objetivo:** Sincronizar dois motores de passo para mover um ponto em uma linha reta em um plano 2D, usando o algoritmo de Bresenham.
- **Pré-requisitos:**
  - Projeto 8
- **Hardware Mínimo:**
  - ATmega328P ou Arduino Mega
  - 2x Motor de passo NEMA 17
  - 2x Driver A4988/DRV8825
  - Fonte de alimentação
- **Tempo Estimado:** 10 horas
- **Dificuldade:** 4/5
- **Dependências:** Projeto 8
- **Passos Principais (Milestones):**
  - Adaptar o código do projeto 8 para controlar dois motores.
  - Estudar e implementar o Algoritmo de Linha de Bresenham.
  - Criar uma função `line(x1, y1, x2, y2)`.
  - Usar uma única interrupção de timer para comandar os motores com base na lógica de Bresenham.
- **Entregáveis:**
  - Código-fonte que move os eixos X e Y de um ponto a outro em linha reta.
  - Vídeo de uma caneta presa ao eixo X desenhando um quadrado ou triângulo.
- **Testes de Validação:**
  - Comandar um movimento de (0,0) para (1000,1000) resulta em uma linha diagonal perfeita de 45°.
- **Metas Avançadas (Stretch Goals):**
  - Integrar o planejador de aceleração (Projeto 9) ao movimento coordenado.
- **Observações:** O uso do Arduino Mega é recomendado por ter mais timers e pinos.

---

### Projeto 11: Leitura de Temperatura: Termistor NTC

- **Módulo:** Controle Térmico
- **Objetivo:** Ler a resistência de um termistor NTC, convertê-la para temperatura usando a equação de Steinhart-Hart e exibi-la.
- **Pré-requisitos:**
  - Projeto 4 (Leitura ADC)
- **Hardware Mínimo:**
  - ATmega328P ou Arduino Uno
  - Termistor NTC 100kΩ (comumente B3950)
  - Resistor de precisão de 100kΩ (1%)
- **Tempo Estimado:** 5 horas
- **Dificuldade:** 2/5
- **Dependências:** Projetos 3, 4
- **Passos Principais (Milestones):**
  - Montar o circuito divisor de tensão com o termistor.
  - Ler o valor do ADC.
  - Converter o valor do ADC para a resistência do termistor.
  - Implementar a equação de Steinhart-Hart (software) para obter a temperatura.
  - Enviar a temperatura via serial.
- **Entregáveis:**
  - Código-fonte que lê e calcula a temperatura.
  - Screenshot do monitor serial mostrando a temperatura subir ao aquecer o termistor.
- **Testes de Validação:**
  - A temperatura lida em ambiente deve ser plausível (e.g., 20-30°C).
- **Metas Avançadas (Stretch Goals):**
  - Substituir o termistor por um termopar e um CI amplificador dedicado (e.g., MAX31855). Isso move a complexidade de linearização e compensação de junta fria do software para um hardware especializado, comunicando-se via SPI.
- **Observações:** A equação requer o uso da biblioteca `math.h` para logaritmos.

---

### Projeto 12: Acionamento de Carga: Controle de Aquecedor com MOSFET

- **Módulo:** Controle Térmico
- **Objetivo:** Controlar uma carga de alta potência usando um MOSFET como chave, focando nos componentes de hardware para um chaveamento seguro.
- **Pré-requisitos:**
  - Projeto 2 (PWM)
- **Hardware Mínimo:**
  - ATmega328P ou Arduino Uno
  - MOSFET de potência N-Channel (e.g., IRLZ44N)
  - Resistor de Gate (~220Ω), Resistor de Pull-down (10kΩ)
  - Cartucho aquecedor de impressora 3D (12V ou 24V)
  - Fonte de alimentação externa (>3A)
- **Tempo Estimado:** 6 horas
- **Dificuldade:** 2/5
- **Dependências:** Projeto 2
- **Passos Principais (Milestones):**
  - Entender o funcionamento do MOSFET e a função dos resistores de gate e pull-down.
  - Conectar o gate do MOSFET ao pino PWM através do resistor de gate.
  - Conectar o resistor de pull-down entre o gate e o source (GND).
  - Conectar a carga (aquecedor) entre a fonte (+) e o drain do MOSFET.
  - Adaptar o código do Projeto 2 para controlar a potência.
- **Entregáveis:**
  - Código-fonte para controlar a potência do aquecedor.
  - Diagrama do circuito.
- **Testes de Validação:**
  - Com PWM em 0%, o aquecedor está frio. Com PWM em 100%, o aquecedor atinge potência máxima.
- **Metas Avançadas (Stretch Goals):**
  - Adicionar um diodo de flyback em paralelo com a carga.
- **Observações:** SEGURANÇA É CRÍTICA. O resistor de gate protege o pino do microcontrolador e o de pull-down garante que o MOSFET permaneça desligado durante a inicialização.

---

### Projeto 13: Controle On-Off (Bang-Bang)

- **Módulo:** Controle Térmico
- **Objetivo:** Implementar um sistema de controle de temperatura simples (on-off com histerese) para manter o aquecedor em uma temperatura alvo.
- **Pré-requisitos:**
  - Projeto 11, Projeto 12
- **Hardware Mínimo:**
  - Combinação dos projetos 11 e 12
- **Tempo Estimado:** 4 horas
- **Dificuldade:** 2/5
- **Dependências:** Projetos 11, 12
- **Passos Principais (Milestones):**
  - Integrar os códigos dos projetos 11 e 12.
  - Definir um setpoint e uma faixa de histerese.
  - Implementar a lógica: ligar o aquecedor abaixo do setpoint, desligar acima.
  - Enviar estado e temperatura via serial.
- **Entregáveis:**
  - Código-fonte do controlador on-off.
  - Gráfico da temperatura ao longo do tempo, mostrando a oscilação.
- **Testes de Validação:**
  - A temperatura oscila em torno do setpoint.
- **Metas Avançadas (Stretch Goals):**
  - Tornar o setpoint e a histerese ajustáveis via comandos seriais.
- **Observações:** Este método é um passo para entender a necessidade do PID.

---

### Projeto 14: Controle Proporcional-Integral-Derivativo (PID)

- **Módulo:** Controle Térmico
- **Objetivo:** Implementar um controlador PID para manter a temperatura do aquecedor estável no setpoint.
- **Pré-requisitos:**
  - Projeto 13
- **Hardware Mínimo:**
  - Mesmo do projeto 13
- **Tempo Estimado:** 12 horas
- **Dificuldade:** 4/5
- **Dependências:** Projeto 13
- **Passos Principais (Milestones):**
  - Estudar a teoria do controle PID.
  - Implementar a lógica do PID para calcular a saída PWM.
  - Limitar (clampar) a saída do PID entre 0 e 255.
  - Integrar a saída do PID ao controle do MOSFET.
  - Realizar a sintonia manual básica dos ganhos Kp, Ki, Kd.
- **Entregáveis:**
  - Código-fonte do controlador PID.
  - Gráfico da temperatura ao longo do tempo mostrando a estabilização no setpoint.
- **Testes de Validação:**
  - A temperatura estabiliza no setpoint com uma variação mínima (e.g., ±1°C).
- **Metas Avançadas (Stretch Goals):**
  - Implementar um algoritmo de auto-sintonia (autotune).
- **Observações:** O PID é um algoritmo (software) que depende de um hardware de sensoriamento e atuação de alta qualidade para funcionar bem.

---

### Projeto 15: Controle de Ventoinha de Resfriamento

- **Módulo:** Controle Térmico
- **Objetivo:** Controlar a velocidade de uma ventoinha usando PWM e um MOSFET.
- **Pré-requisitos:**
  - Projeto 12
- **Hardware Mínimo:**
  - ATmega328P ou Arduino Uno
  - Ventoinha DC (e.g., 40mm, 12V)
  - MOSFET N-Channel e resistores de gate/pull-down
  - Diodo de flyback (e.g., 1N4007)
  - Fonte de alimentação externa
- **Tempo Estimado:** 3 horas
- **Dificuldade:** 1/5
- **Dependências:** Projetos 3, 12
- **Passos Principais (Milestones):**
  - Conectar a ventoinha ao MOSFET como no Projeto 12.
  - **Adicionar o diodo de flyback em paralelo com a ventoinha (cátodo no V+).**
  - Usar um pino PWM para controlar a velocidade.
  - Criar um programa para definir a velocidade via comando serial.
- **Entregáveis:**
  - Código-fonte para controle da ventoinha.
  - Vídeo mostrando a ventoinha operando em diferentes velocidades.
- **Testes de Validação:**
  - Enviar comandos pela serial altera a velocidade da ventoinha de 0 a 100%.
- **Metas Avançadas (Stretch Goals):**
  - Implementar controle termostático: ligar a ventoinha automaticamente acima de uma certa temperatura.
- **Observações:** O diodo de flyback é um componente de hardware crucial para proteger o MOSFET dos picos de tensão gerados pela carga indutiva do motor da ventoinha.

---

### Projeto 16: Sensores de Fim de Curso (Endstops)

- **Módulo:** Sensores e Interface
- **Objetivo:** Detectar o acionamento de um sensor de fim de curso mecânico.
- **Pré-requisitos:**
  - Projeto 1
- **Hardware Mínimo:**
  - ATmega328P ou Arduino Uno
  - Micro-switch (endstop mecânico)
- **Tempo Estimado:** 3 horas
- **Dificuldade:** 1/5
- **Dependências:** Projetos 1, 3
- **Passos Principais (Milestones):**
  - Conectar o endstop a um pino digital (contatos NC e C).
  - Configurar o pino como entrada com pull-up interno.
  - Ler o estado do pino e enviar uma mensagem via serial quando acionado.
- **Entregáveis:**
  - Código-fonte que detecta o acionamento do endstop.
- **Testes de Validação:**
  - O estado lógico lido do pino deve mudar quando o endstop é acionado.
- **Metas Avançadas (Stretch Goals):**
  - Usar uma interrupção de pino (PCINT ou INTx) para detecção assíncrona.
- **Observações:** A configuração NC é preferida por ser mais segura.

---

### Projeto 17: Homing de Eixo

- **Módulo:** Sensores e Interface
- **Objetivo:** Implementar uma rotina de 'homing' para um eixo: mover até o endstop ser acionado para estabelecer a posição zero.
- **Pré-requisitos:**
  - Projeto 8, Projeto 16
- **Hardware Mínimo:**
  - Combinação dos projetos 8 e 16
- **Tempo Estimado:** 6 horas
- **Dificuldade:** 3/5
- **Dependências:** Projetos 8, 16
- **Passos Principais (Milestones):**
  - Integrar o código de controle do motor com o de leitura do endstop.
  - Criar uma função `home_axis()`.
  - Mover o motor lentamente e verificar o endstop a cada passo.
  - Parar o motor ao acionar o endstop e definir a posição como zero.
- **Entregáveis:**
  - Código-fonte com a rotina de homing.
  - Vídeo do eixo se movendo, tocando o endstop e parando.
- **Testes de Validação:**
  - A rotina de homing para o motor de forma consistente no mesmo ponto.
- **Metas Avançadas (Stretch Goals):**
  - Implementar homing para 2 ou 3 eixos (X, Y, Z) em sequência.
- **Observações:** A velocidade de homing deve ser baixa para evitar danos.

---

### Projeto 18: Interface: Display LCD 20x4

- **Módulo:** Sensores e Interface
- **Objetivo:** Exibir informações de status em um display LCD de caracteres.
- **Pré-requisitos:**
  - Conceitos de comunicação paralela ou I2C
- **Hardware Mínimo:**
  - ATmega328P ou Arduino Uno/Mega
  - Display LCD 20x4 (com ou sem módulo I2C)
- **Tempo Estimado:** 5 horas
- **Dificuldade:** 2/5
- **Dependências:** Projeto 11
- **Passos Principais (Milestones):**
  - Conectar o display ao microcontrolador.
  - Incluir e configurar uma biblioteca para o display.
  - Escrever funções para exibir texto e variáveis.
  - Atualizar as informações na tela periodicamente.
- **Entregáveis:**
  - Código-fonte que exibe dados em tempo real no LCD.
  - Foto do LCD mostrando temperatura e posição.
- **Testes de Validação:**
  - O texto aparece claramente e os valores são atualizados corretamente.
- **Metas Avançadas (Stretch Goals):**
  - Criar caracteres customizados.
- **Observações:** O uso de um módulo I2C simplifica drasticamente a fiação.

---

### Projeto 19: Interface: Encoder Rotativo com Botão e Filtragem de Hardware

- **Módulo:** Sensores e Interface
- **Objetivo:** Ler a rotação e o clique de um encoder, usando filtros RC de hardware para garantir um sinal limpo.
- **Pré-requisitos:**
  - Projeto 1
- **Hardware Mínimo:**
  - ATmega328P ou Arduino Uno
  - Encoder rotativo (e.g., KY-040)
  - 2x Resistor 1kΩ, 2x Capacitor cerâmico 100nF
- **Tempo Estimado:** 7 horas
- **Dificuldade:** 3/5
- **Dependências:** Projetos 1, 3
- **Passos Principais (Milestones):**
  - **Montar os filtros RC passa-baixa para as saídas A e B do encoder.**
  - Conectar as saídas filtradas do encoder aos pinos do microcontrolador.
  - Usar interrupções de pino (PCINT) para detectar mudanças nos pinos A e B.
  - Na ISR, ler o estado de A e B para determinar a direção da rotação.
  - Implementar o debounce para o botão do encoder (pode ser por hardware, como no Projeto 1).
- **Entregáveis:**
  - Código-fonte que rastreia a posição do encoder.
  - Enviar a posição do contador via serial para verificação.
- **Testes de Validação:**
  - Girar o encoder incrementa/decrementa um contador sem perder passos, mesmo com rotação rápida.
- **Metas Avançadas (Stretch Goals):**
  - Acelerar a mudança do valor com base na velocidade de rotação.
- **Observações:** O filtro de hardware remove ruídos e transientes dos contatos mecânicos do encoder, o que simplifica o software e evita leituras falsas.

---

### Projeto 20: Interface: Menu Simples no LCD

- **Módulo:** Sensores e Interface
- **Objetivo:** Criar um sistema de menu navegável no display LCD usando o encoder rotativo.
- **Pré-requisitos:**
  - Projeto 18, Projeto 19
- **Hardware Mínimo:**
  - Combinação dos projetos 18 e 19
- **Tempo Estimado:** 8 horas
- **Dificuldade:** 3/5
- **Dependências:** Projetos 18, 19
- **Passos Principais (Milestones):**
  - Estruturar o menu em C (e.g., usando structs).
  - Implementar a lógica de navegação: girar o encoder move um cursor.
  - Clicar no encoder entra em um sub-menu ou seleciona uma opção para edição.
  - Girar para alterar um valor e clicar para confirmar.
- **Entregáveis:**
  - Código-fonte de um menu funcional.
  - Vídeo demonstrando a navegação e alteração de um parâmetro.
- **Testes de Validação:**
  - A navegação pelo menu é fluida e responsiva.
- **Metas Avançadas (Stretch Goals):**
  - Implementar múltiplos níveis de sub-menus.
  - Salvar os parâmetros alterados na EEPROM (Projeto 5).
- **Observações:** Uma máquina de estados finitos (FSM) é uma excelente forma de organizar a lógica.

---

### Projeto 21: Parser de G-Code Básico

- **Módulo:** Firmware e Integração
- **Objetivo:** Receber strings de G-code via serial e extrair os comandos e seus parâmetros.
- **Pré-requisitos:**
  - Projeto 3, Manipulação de strings em C
- **Hardware Mínimo:**
  - ATmega328P ou Arduino Uno
- **Tempo Estimado:** 8 horas
- **Dificuldade:** 3/5
- **Dependências:** Projeto 3
- **Passos Principais (Milestones):**
  - Criar uma função que lê uma linha completa da serial.
  - Analisar a linha para identificar o comando (G/M) e seu número.
  - Analisar os parâmetros (X, Y, Z, E, F, S) e seus valores.
  - Armazenar os valores extraídos em uma struct.
- **Entregáveis:**
  - Código-fonte do parser.
  - Screenshot do monitor serial mostrando a string enviada e os valores extraídos.
- **Testes de Validação:**
  - Enviar 'G1 X100 Y50' resulta em comando='G', codigo=1, x_val=100, y_val=50.
- **Metas Avançadas (Stretch Goals):**
  - Implementar um buffer de comandos para enfileirar vários G-codes.
- **Observações:** Funções como `strtok()` e `atof()` são muito úteis aqui.

---

### Projeto 22: Integração: Movimento por G-Code

- **Módulo:** Firmware e Integração
- **Objetivo:** Integrar o parser de G-code com o sistema de movimento para executar comandos G0/G1.
- **Pré-requisitos:**
  - Projeto 10, Projeto 21
- **Hardware Mínimo:**
  - Combinação dos projetos 10 e 21
- **Tempo Estimado:** 10 horas
- **Dificuldade:** 4/5
- **Dependências:** Projetos 10, 21
- **Passos Principais (Milestones):**
  - Unir o código do parser com o do controle de eixos.
  - Se o comando for G0 ou G1, extrair as coordenadas.
  - Chamar a função de movimento com as novas coordenadas.
  - Aguardar a conclusão do movimento antes de processar o próximo.
- **Entregáveis:**
  - Código-fonte que funciona como um 'plotter' primitivo.
  - Vídeo mostrando os eixos se movendo ao enviar G-code.
- **Testes de Validação:**
  - Enviar uma sequência de comandos G1 desenha a forma geométrica esperada.
- **Metas Avançadas (Stretch Goals):**
  - Implementar coordenadas relativas (G91).
- **Observações:** A gestão do fluxo de comandos é crucial.

---

### Projeto 23: Integração: Controle Térmico por G-Code

- **Módulo:** Firmware e Integração
- **Objetivo:** Integrar o parser de G-code com o sistema de controle de temperatura para executar comandos M104/M109.
- **Pré-requisitos:**
  - Projeto 14, Projeto 21
- **Hardware Mínimo:**
  - Combinação dos projetos 14 e 21
- **Tempo Estimado:** 6 horas
- **Dificuldade:** 3/5
- **Dependências:** Projetos 14, 21
- **Passos Principais (Milestones):**
  - Integrar o código do parser com o controlador PID.
  - Reconhecer comandos M104 S<temp> e M109 S<temp>.
  - M104: atualiza o setpoint do PID.
  - M109: atualiza o setpoint e pausa o processamento até a temperatura ser atingida.
- **Entregáveis:**
  - Código-fonte que permite o controle de temperatura via G-code.
- **Testes de Validação:**
  - Enviar 'M104 S200' muda o setpoint do PID para 200.
  - Enviar 'M109 S180' bloqueia a execução até a temperatura ser atingida.
- **Metas Avançadas (Stretch Goals):**
  - Implementar M106/M107 para controlar a ventoinha.
- **Observações:** M109 é um comando bloqueante e exige uma lógica de estado.

---

### Projeto 24: Máquina de Estados do Firmware

- **Módulo:** Firmware e Integração
- **Objetivo:** Estruturar o firmware como uma máquina de estados finitos (FSM) para gerenciar os modos de operação (Idle, Printing, etc.).
- **Pré-requisitos:**
  - Todos os projetos de integração
- **Hardware Mínimo:**
  - Arduino Mega preferencialmente
- **Tempo Estimado:** 8 horas
- **Dificuldade:** 4/5
- **Dependências:** Projetos 22, 23
- **Passos Principais (Milestones):**
  - Definir os estados possíveis da impressora.
  - Criar uma variável `estado_atual`.
  - No loop principal, usar `switch(estado_atual)` para executar o código relevante.
  - Implementar as transições entre estados.
  - Refatorar o código existente para se encaixar na FSM.
- **Entregáveis:**
  - Código-fonte refatorado usando uma FSM.
  - Diagrama simples dos estados e transições.
- **Testes de Validação:**
  - A impressora responde a comandos de forma diferente dependendo do estado.
- **Metas Avançadas (Stretch Goals):**
  - Adicionar estados de erro ou falha.
- **Observações:** A FSM organiza o código, tornando-o mais legível e escalável.

---

### Projeto 25: Proteção de Segurança: Thermal Runaway

- **Módulo:** Firmware e Integração
- **Objetivo:** Implementar uma verificação que desliga os aquecedores se a temperatura não se comportar como esperado.
- **Pré-requisitos:**
  - Projeto 23
- **Hardware Mínimo:**
  - Mesmo do projeto 23
- **Tempo Estimado:** 5 horas
- **Dificuldade:** 3/5
- **Dependências:** Projeto 23
- **Passos Principais (Milestones):**
  - Quando um aquecedor é ligado, monitorar se a temperatura aumenta um mínimo dentro de um período.
  - Se não aumentar, entrar em estado de erro e desligar todos os aquecedores.
  - Verificar também se a temperatura excede um máximo absoluto.
- **Entregáveis:**
  - Código-fonte com a lógica de proteção implementada.
- **Testes de Validação:**
  - Simular uma falha (desconectar o termistor). O firmware deve detectar o erro e desligar o aquecedor.
- **Metas Avançadas (Stretch Goals):**
  - Exibir uma mensagem de erro específica no LCD.
- **Observações:** Esta é a funcionalidade de segurança mais importante em um firmware de impressora 3D.

---

### Projeto 26: Montagem Mecânica do Kit da Impressora

- **Módulo:** Montagem e Calibração
- **Objetivo:** Montar o chassi e os componentes mecânicos de um kit de impressora 3D.
- **Pré-requisitos:**
  - Ferramentas básicas
- **Hardware Mínimo:**
  - Kit de impressora 3D
- **Tempo Estimado:** 10 horas
- **Dificuldade:** 3/5
- **Dependências:** Nenhuma
- **Passos Principais (Milestones):**
  - Montar o frame principal, garantindo o esquadrejamento.
  - Montar os eixos X, Y e Z.
  - Instalar correias e garantir a tensão correta.
  - Verificar se todos os eixos se movem suavemente à mão.
- **Entregáveis:**
  - Fotos da impressora montada.
- **Testes de Validação:**
  - Os eixos se movem de ponta a ponta sem esforço. A estrutura está rígida.
- **Metas Avançadas (Stretch Goals):**
  - Realizar upgrades mecânicos durante a montagem.
- **Observações:** Um frame mal montado nunca imprimirá bem.

---

### Projeto 27: Conexão Elétrica (Wiring)

- **Módulo:** Montagem e Calibração
- **Objetivo:** Conectar todos os componentes eletrônicos à placa de controle principal.
- **Pré-requisitos:**
  - Projeto 26
- **Hardware Mínimo:**
  - Impressora montada, Placa de controle
- **Tempo Estimado:** 6 horas
- **Dificuldade:** 2/5
- **Dependências:** Projeto 26
- **Passos Principais (Milestones):**
  - Fixar a placa de controle e a fonte de alimentação.
  - Conectar motores, endstops, aquecedores, termistores e ventoinhas.
  - Conectar a fonte de alimentação à placa.
  - Organizar os cabos.
- **Entregáveis:**
  - Fotos detalhadas da fiação completa.
- **Testes de Validação:**
  - Verificar a continuidade e ausência de curtos com um multímetro antes de ligar.
- **Metas Avançadas (Stretch Goals):**
  - Usar conectores e terminais apropriados.
- **Observações:** Atenção à polaridade. Siga o diagrama da sua placa de controle.

---

### Projeto 28: Compilação e Flash de Firmware (Marlin/Klipper)

- **Módulo:** Montagem e Calibração
- **Objetivo:** Configurar, compilar e instalar um firmware de mercado (como Marlin) na placa de controle.
- **Pré-requisitos:**
  - Projeto 27
- **Hardware Mínimo:**
  - Impressora montada, Computador com VSCode e PlatformIO
- **Tempo Estimado:** 10 horas
- **Dificuldade:** 4/5
- **Dependências:** Projeto 27
- **Passos Principais (Milestones):**
  - Baixar a versão correta do Marlin.
  - Configurar `Configuration.h` (placa, termistores, dimensões, etc.).
  - Compilar o firmware.
  - Transferir (flashear) o firmware para a placa.
  - Conectar à impressora e verificar a comunicação.
- **Entregáveis:**
  - Arquivos `Configuration.h` e `Configuration_adv.h` modificados.
- **Testes de Validação:**
  - A impressora liga e é possível conectar-se via USB e enviar comandos.
- **Metas Avançadas (Stretch Goals):**
  - Configurar e instalar o Klipper.
- **Observações:** Este passo aplica todo o conhecimento teórico adquirido.

---

### Projeto 29: Calibração de Movimento e Extrusão

- **Módulo:** Montagem e Calibração
- **Objetivo:** Calibrar os parâmetros fundamentais do firmware para precisão de movimento e extrusão.
- **Pré-requisitos:**
  - Projeto 28
- **Hardware Mínimo:**
  - Impressora funcional, Paquímetro digital, Filamento
- **Tempo Estimado:** 8 horas
- **Dificuldade:** 3/5
- **Dependências:** Projeto 28
- **Passos Principais (Milestones):**
  - Verificar a direção de cada motor.
  - Realizar o Homing dos eixos.
  - Calibrar os 'steps per mm' para os eixos X, Y, Z.
  - Calibrar os 'steps per mm' do extrusor (E-steps).
  - Realizar a sintonia do PID do hotend e da mesa (autotune).
  - Salvar as configurações na EEPROM (M500).
- **Entregáveis:**
  - Valores calculados e configurados de 'steps per mm' e PID.
- **Testes de Validação:**
  - Comandar um movimento de 100mm move o eixo exatamente 100mm.
  - Comandar a extrusão de 100mm consome exatamente 100mm de filamento.
- **Metas Avançadas (Stretch Goals):**
  - Calibrar 'Linear Advance' ou 'Pressure Advance'.
- **Observações:** A calibração correta é a diferença entre uma impressão de baixa e alta qualidade.

---

### Projeto 30: Impressão do Primeiro Objeto: Nivelamento e Calibração Final

- **Módulo:** Montagem e Calibração
- **Objetivo:** Nivelar a mesa de impressão e realizar a primeira impressão de um objeto de calibração.
- **Pré-requisitos:**
  - Projeto 29
- **Hardware Mínimo:**
  - Impressora calibrada, Filamento (PLA)
- **Tempo Estimado:** 6 horas
- **Dificuldade:** 3/5
- **Dependências:** Projeto 29
- **Passos Principais (Milestones):**
  - Aquecer o hotend e a mesa.
  - Realizar o nivelamento da mesa.
  - Carregar um G-code de um cubo de calibração.
  - Iniciar a impressão e observar a primeira camada, ajustando se necessário.
  - Analisar o objeto impresso e fazer ajustes finos.
- **Entregáveis:**
  - O primeiro objeto impresso com sucesso.
  - Fotos da primeira camada e do objeto finalizado.
- **Testes de Validação:**
  - A primeira camada adere bem à mesa.
  - As dimensões do cubo impresso estão próximas do esperado.
- **Metas Avançadas (Stretch Goals):**
  - Imprimir objetos mais complexos.
  - Configurar um perfil de fatiamento otimizado.
- **Observações:** A primeira impressão raramente é perfeita. Use-a como ferramenta de diagnóstico.