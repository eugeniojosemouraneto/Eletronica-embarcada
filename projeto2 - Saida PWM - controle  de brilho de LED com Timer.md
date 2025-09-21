# Projeto 2: Saída PWM: controle de brilho de LED com Timer

No projeto 1 foi usado os pinos do microcontrolador para atuar como saídas digitais simples, estado alto ou baixo. No entanto, em muitas aplicações, como no controle de rotação de motores, vai ser necessario um controle analógico, um nível de potência intermediario ou variado.

A  técnica mais comum para simular uma saída  analógica usando um pino digital é o PWM (Pulse Width Modulation, modulação por largura de pulso). Ao ligar e desligar um pino digital em alta velocidade, podemos controlar a potência média entregue a uma componente, variando a proporção de tempo em que o sinal fica em alto.

## Aprendizagem com o projeto

- Entendimento dos conceitos de frequência, período e ciclo de trabalho de um sinal PWM.

- Configure um timer de 8 bits do ATmega328P para operar no modo Fast PWM.

- Manipular os registradores TCCRxA e controlar a forma e a saída do sinal PWM TCCTxB. OCRxA/B.

- Gerar um efeito de fade (aumento e diminuição gradual do brilho) em um LED.

- Compreender a vantagem de usar periféricos de hardware em vez de implementações baseadas em software ("bit-banging").

## Materiais necessários

- 1x ATmega328P ou Arduino UNO

- 1x LED (vermelho: $V_f=2.2V, I_f=10mA$)

- 1x resistor ($220\Omega$ para fontes de $5V$)

- Protoboard e jumpers

## Entregáveis e testes de validação

- Entregáveis:
    - Código-fonte completo e funcional que produz o efeito de fade in/out.

    - Uma breve explicação do uso específico dos registradores TCCR0A, TCCR0B e OCR0A no código.

- Testes de validação:

    - Teste visual: o LED deve começar a pulsar suavemente, aumentando e transmitindo o brilho, sem piscar bruscamente.

    - Teste com multimetro: medir a voltagem entre o pino PD6 e o GND, verificar como você deve configurar o multimetro.

## Teoria

### Timer em um Microcontrolador

O Timer é relogio de hardware especializado dentro do microcontrolador. Onde a sua principal função é contar. Onde ele pode contar de duas formaas diferentes.

- Contar por pulso de clock interno: está a forma mais básica do timer, onde ele incrementa 1 no registrador responsavel a cada pulso de clock do sistema. Como a frequência de clock é constante e precisa, essa contagem se traduz diretamente em uma medição de tempo.

- Contar por eventos externos: o timer pode ser configurado para contar pulsos que chegam em um pino específico do microcontrolador, funcionando como um contador de eventos externo ao microcontrolador.

A principal vantagem de um timer por hardware é que ele execulta a sua função sem bloquear a CPU. Onde ele funciona em segundo plano, o que não consome tempo de processamento.

### PWM o que é e como funciona

PWM, ou modulação por largura de pulso, é uma técnica usada para controlar a quantidade de energia que o microcontrolador envia a um dispositivo externo a ele por meio de um de seus pinos. Onde ele é feito ligando e desligando a energia rapidamente, em uma frequência constante. O PWM varia o tempo que o sinal elétrico permanece ligado em cada ciclo.

### O que é Duty Cycle?

O duty cycle, ou ciclo de trabalho, é o conceito mais importante no PWM. Onde ele representa uma porcentagem de tempo em que o sinal fica no estado alto dentro de um ciclo completo. O uso desses sinais é baseado no conceito de valor médio de uma forma de onda periódica.

$$V_{medio}=\frac{Amplitude máxima}{período}*(Tempo ativo no periodo)$$

- **Duty cycle de 0%:** o sinal de estado alto está sempre desligado.

- **Duty cycle de 50%:** o sinal de estado alto fica assim por metado de tempo e em estado baixo a outra metado do tempo. A energia entregue é de 50%.

- **Duty cycle de 100%:** o sinal de estado alto fica ativo por todo o tempo do ciclo.

> O controle de dispositivos por PWM é, portanto, uma questão de ajustar o ciclo de trabalho.

### Registradores envolvidos no PWM por Timer (modo de operação do Timer Fast PWM)

Como exemplo será usado o Timer2 do ATmega3288P. Ele é um timer de 8 bits (conta de 0 a 255).

O Modo Fast PWM é um dos mais simples e eficientes. O contador TCNT2 conta de 0 a 255 e, ao chegar em 255, ele estoura (overflow) e volta para 0 no próximo ciclo de clock, recomeçando a contagem. 

A geração do PWM ocorre pela comparação constante entre o valor do contador TCNT2 e um valor que nós definimos em um registrador de comparação (OCR2A ou OCR2B).

**TCCR2A e TCCR2B** - Registradores de Controle do Timer/Counter 2, eles definem o que o timer vai fazer e como ele vai fazer.

- **TCCR2A e TCCR2B** - Registradores de Controle do Timer/Counter 2. Esses dois registradores são o painel de controle do timer. É aqui que você define o que o timer vai fazer e como ele vai fazer.

    - **TCCR2A** (Timer/Counter Control Register A):
        
        - **Bits COM2A1/COM2A0 e COM2B1/COM2B0 (Compare Output Mode):** Definem o comportamento do pino de saída PWM (OC2A ou OC2B). A configuração mais comum é a não-inversora (10), que significa:
            
            - Coloca o pino em nível ALTO (1) quando o contador zera (TCNT2 = 0).

            - Coloca o pino em nível BAIXO (0) quando o valor do contador TCNT2 iguala ao valor de OCR2A.

        - **Bits WGM21/WGM20 (Waveform Generation Mode):** Selecionam o modo de operação do timer. Para Fast PWM de 8 bits, configuramos esses bits como 11.

    - **TCCR2B** (Timer/Counter Control Register B):

        - **Bits CS22/CS21/CS20 (Clock Select):** Estes bits ligam o timer e definem o prescaler. O prescaler é um divisor de frequência. Ele pega o clock principal do microcontrolador (ex: 16 MHz) e o divide por um fator (1, 8, 32, 64, 128, 256 ou 1024) para diminuir a velocidade da contagem. Isso é crucial para gerar frequências de PWM utilizáveis. Se esses bits forem 000, o timer está desligado.

        - **Bit WGM22:** Completa a seleção do modo de operação. Para o modo Fast PWM que conta até 255, este bit deve ser 0.

- **OCR2A e OCR2B** - Registradores de Comparação de Saída A e B. Este é o registrador que você usará para controlar o duty cycle (o ciclo de trabalho).

    - Funcionalidade: Você escreve um valor aqui (de 0 a 255). O hardware do timer compara o valor deste registrador com o valor do contador TCNT2 em tempo real.

    - Controle do Duty Cycle: No modo não-inversor, a largura do pulso (tempo em nível ALTO) é determinada pelo valor em OCR2A.

        - OCR2A = 0: Duty cycle de ~0.4% (o pulso dura apenas 1 ciclo de clock).

        - OCR2A = 127: Duty cycle de 50%.

        - OCR2A = 255: Duty cycle de 100% (a saída nunca vai para nível baixo).

- **TCNT2** - Registrador do Timer/Counter 2. Este é o registrador que efetivamente conta, de 0 a 255. Você raramente precisa escrever ou ler este registrador diretamente ao usar o modo PWM, pois o hardware gerencia sua contagem automaticamente.

- **DDRx** - Registrador de Direção de Dados. Embora não seja um registrador do timer, é essencial. Para que o sinal PWM gerado pelo timer apareça no pino físico do microcontrolador, esse pino deve ser configurado como saída digital. Por exemplo, o pino de saída OC2A do Timer2 está no pino PB3 do ATmega328P. Portanto, o bit 3 do DDRB (Data Direction Register for Port B) deve ser setado como 1.

![proteus](./files/image%20copy%202.png)

![tinkercad](./files/image%20copy.png)

```cpp
#include <avr/io.h>

#define F_CPU 16000000UL

#define TIMER0_FAST_PWM_NAO_INVERTIDO_OC0A (1 << WGM01) | (1 << WGM00) | (1 << COM0A1)
#define TIMER0_PRESCALER_64 (1 << CS01) | (1 << CS00)

#define PIN_LED PD6

void atraso_ms_timer0(uint16_t millisegundos); 

void calibracao_timer0_fast_pwm_nao_invertida_prescaler64();

int main() {
    DDRD |= (1 << PIN_LED);
    calibracao_timer0_fast_pwm_nao_invertida_prescaler64();
    while(1) {
        for(uint8_t nivel_brilho = 0; nivel_brilho < 255; nivel_brilho++) {
            OCR0A = nivel_brilho;
            atraso_ms_timer0(100)
        }
        for(uint8_t nivel_brilho = 255; nivel_brilho > 0; nivel_brilho--) {
            OCR0A = nivel_brilho;
            atraso_ms_timer0(100)
        }
    }
}

void atraso_ms_timer0(uint16_t millisegundos) {
    for(uint16_t i = 0; i < millisegundos; i++)
        for(volatile uint16_t contador_interno = 0; contador_interno < 1600; contador_interno++);
}

void calibracao_timer0_fast_pwm_nao_invertida_prescaler64() {
    // Timer0 modo Fast PWM saída não-invertida no pino OC0A
    TCCR0A |= TIMER0_FAST_PWM_NAO_INVERTIDO_OC0A;
    // Timer0 prescaler 64
    TCCR0B |= TIMER0_PRESCALER_64;
}
```