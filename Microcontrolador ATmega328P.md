# Arduino UNO (ATmega328P)

> Placa de prototipagem eletrônica de código aberto (open-source), para o microcontrolador **ATmega328P**.

## O que é um microcontrolador?
É um comportamento minpusculo e completo em um único chip. Onde ele tem um processador (8 bits), memória (programa e dados) e pinos de entrada/saída.

O ATmega328P tem as seguintes características:
- **Arquitetura: 8 bits**.
- **Velocidade de clock: 16 MHz**.
- **Memória Flash: 32 kB** (não volátil, onde é armazenado o código a ser execultado).
- **Memória SRAM: 2 kB** (volátil, memória de trabalho).
- **Memória EEPROM: 1 kB** (não volátil)
- **Pinos de I/O: 14 pinos digitais e 6 pinos analógicos**

### Anatomia básica: Partes principais da placa
- **Pinos digitais (0-13):** são pinos que **podem ser** configurados como **entrada ou saída**.
    - **Pinos ~(3, 5, 6, 9, 10, 11)**, o (~) indica que **podem fazer PWM** (Pulse Width Modulation), ou seja, podem simular uma saída analógica.
    - **Pinos o (RX) e 1 (TX)** são usados para **comunicação serial**.
- **Pinos Analógicos (A0-A5):** são pinos dedicados a leitura de valores analógicos. Onde eles convertem a tensão em um valor digital que o microncontrolador possa entender.
- **Alimentação:** ele fornece energia a componentes externos.
    - 3.3-5 V: saídas de tensões fixas.
    - GND: é o terra ou negativo do circuito.
    - VIN: para alimentar a placa Arduino com uma tensão externa.
- **Conector USB (tipo B)** usado para:
    - Carregar o código do computador na memória Flash do ATmega328P.
    - Alimentação da placa.
    - Comunicação com o computador.
- **Conector de energia:** permitir alimentação do Arduino com uma fonte de energia externa, em vez do USB-B.
- **Botão de reset:** ele reinicia o microcontrolador, fazendo o programa da Flash rodar desdo o início