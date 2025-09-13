
# Trabalho: Robô desvia-objetos — Nível 01

**Faculdade:** PUC-Goiás, Brasil  
**Curso:** Engenharia de Computação (Bacharelado)  
**Disciplina:** Microcontroladores e Microprocessadores  
**Aluno:** Eugênio José Moura Neto  
**Data:** 12/05/2025

---

## Sumário
1. [Objetivos](#objetivos)  
2. [Requisitos](#requisitos)  
3. [Materiais e componentes](#materiais-e-componentes)  
4. [Arquitetura do sistema](#arquitetura-do-sistema)  
5. [Topicos a serem estudados antes do projeto](#topicos-de-estudo)  
6. [Conteudo teorico](#conteudo-teorico)  

---

# Objetivos
- Construir e demonstrar um robô que desvia de obstáculos usando 04x micro-switches e 2 motores DC controlados por ponte H.
- Programar o ATmega328P manipulando registradores de forma direta.

# Requisitos
## Funcionais
- Detectar colisões e responder com movimentos adequados a colisão.
## Não-funcionais
- Sem uso de funções de alto nível (`delay`, `pinMode`).

# Materiais e componentes
- 01x Arduino UNO 
- 02x Motores DC
- 04x Micro-switch
- Ponte H, transistores, relé, LEDs, fonte.

# Arquitetura do sistema 
<!-- ![Figura 01 - Esboço do circuito](../files/image01.jpg) -->

# Topicos de estudo
1. Fundamentos elétricos e instrumentação
    - Lei de Ohm, potência, queda de tensão (V = R·I, P = V·I).
    - Fontes DC (baterias vs fonte de bancada) e ligação terra/comum (GND).
    - Noções de ruído, capacitores de desacoplamento (by-pass) e condensadores de reserva.
    - Uso de multímetro e osciloscópio: medir tensão, corrente, continuidade e forma de onda.
2. Motores DC — comportamento em corrente máxima
    - Curva torque × corrente, corrente de partida (stall current) e corrente contínua máxima admissível.
    - Aquecimento do motor em operação na corrente máxima e impacto na vida útil.
    - Medição de corrente de partida e corrente sob carga.
3. Eletrônica de potência e H-bridge robusta
    - Escolha de dispositivos: MOSFETs logic-level (N-MOS) de baixa Rds(on) ou transistores de potência.
    - Projeto de ponte H: princípio de funcionamento (2 canais por motor para frente/reverso).
    - Proteções: evitar shoot-through, snubbers, diodos flyback, dissipação térmica e dissipadores.
    - Dimensionamento de resistores de gate/base e necessidade de drivers de gate.
4. Fonte, alimentação e proteções
    - Seleção de bateria/fonte que suporte correntes de pico e média; queda de tensão em cabos.
    - Fusíveis (rápidos vs retardados), proteção térmica e monitoramento.
    - Layout de GND e importância do GND comum entre Arduino e drivers.
    - Condensadores de desacoplamento próximos ao driver/motores e supressão EMI.
5. ATmega328P — GPIO e registradores
    - Mapas de pinos: PORTB, PORTC, PORTD; como usar DDRx, PORTx, PINx.
    - Entradas digitais com pull-up internos; leitura com mascaramento de bits.
    - Controle de enable/direction da H-bridge via pinos digitais (ex.: PORTD, PORTB).
    - Ferramentas: avr-gcc / PlatformIO / AVRDUDE; compilação bare-metal.
6. Timers e delays (sem `delay()`)
    - Timers (Timer0/Timer1/Timer2): modos Normal, CTC, Fast PWM, Phase Correct.
    - Cálculo de prescaler, OCRn, overflow e geração de timeouts/delays.
    - Implementar `delay_ms()` e timeouts de manobra sem bloqueios longos.
7. Interrupções, debounce e lógica de manobra
    - Interrupções externas INT0/INT1 e Pin-Change Interrupts (PCICR, PCMSKx).
    - Configurar bordas de detecção (subida/descida) e habilitar globalmente (`sei()`).
    - Debounce: técnicas de hardware (RC) e software (tempo mínimo entre eventos).
    - Algoritmo de reação sugerido: sensor frontal → parar → ré X ms → girar para lado oposto Y ms.
8. Medições e análise (corrente / térmica / sinais)
    - Medir pico de corrente na partida (inrush) com alicate ou shunt e registrar com osciloscópio.
    - Medir ruído na alimentação e verificar resets do ATmega; reforçar desacoplamento se necessário.
    - Teste térmico prolongado em MOSFETs e motores (temperatura após N minutos).
9. Integração, testes de robustez e documentação
    - Plano de testes: unitário (sensor, motor), integração (comportamento robô), regressão.
    - Execução de N repetições por cenário (ex.: 10 repetições: frente, traseira, múltiplos sensores).
    - Testes de falha controlados: desconexão de bateria, bateria fraca, curto simulado (com segurança).
11. Cálculos e verificações essenciais
    - Corrente de stall \(I_{stall}\) e corrente média \(I_{médio}\) — medir para dimensionar componentes.
    - Potência dissipada em MOSFET: \(P = I^2 \cdot R_{ds(on)}\) — calcular e dimensionar dissipador.
    - Capacidade mínima da bateria: estimar a autonomia (Ah) com base em I_médio e tempo desejado.
    - Cálculo de resistor de gate/base e seleção de fusível adequado.
12. Segurança e boas-práticas
    - Usar fusível na alimentação positiva e monitoramento térmico do driver.
    - GND comum corretamente estabelecido; evitar loops de terra.
    - Medir correntes com equipamento apropriado; proteções pessoais (óculos, ambiente seguro).
    - Não deixar circuitos sem supervisão durante testes de correntes altas.

# Conteudo teorico
## 1. Fundamentos elétricos e instrumentação
### 1.1. Lei de Ohm
> Princípio físico da eletricidade que descreve a relação entre as grandezas elétricas de tensão, corrente e resistência. <br>
> De forma simplificada, a 1° Lei de Ohm,  estabelece que  a corrente elétrica que flui através de um condutor é diretamente proporcional à tensão aplicada sobre ele e inversamente proporcional à resistencia do mesmo.

**$V = IR$**
- V - Tensão em Volts (V)
- I - Corrente em Ampères (A)
- R - Resistência em Ohms (Ω)

> A formula pode ser reescrita também nas formas d:

**$I = \frac{V}{R}$ ou $R = \frac{V}{I}$**  

**As grandezas:**
- **Tensão (V):** a tensão ou d.d.p. (diferença de potencial), é a força que impulsina as cargas elétricas (geralmente eletrons em condutores metalicos) a se moverem em um circuito. Sua unidade de medida é o **volt (V)**. Pense na tensão como a pressão que faz o movimento das cargas acontecer.
- **Corrente (I):** a corrente elétrica é o fluxo ordenado de cargas em um meio. Onde sua unidade de medida é o **ampère (A)**. Pense que a corrente é a quantificação da quantidade de corrente que passa no meio em um intervalo de tempo.
- **Resistência (R):** a resistência elétrica é a oposição natural que um material oferece a passagem de corrente elétrica. Onde a sua unidade de medida é o **ohm (Ω)**. Pense que a resistencia é a dificuldade na passagem de corrente que um material oferece naturalmente.

### 1.2. Potência
> Potência elétrica é a velocidade em que a energia elétrica é convertida em outra forma de energia. Pense nela como a quantificação da quantidade de quanta corrente é convertida em outro forma de energia, como calor ou luminosa. A sua unidade de medida é o **Watts (W)** 

**$$P = VI$$**
- P - Potência em Watts (W)
- V - Tensão em Volts (V)
- I - Corrente em Ampère (A)

Pode ser utilizado a 1° Lei de Ohm ( $V=RI$ ) para alterar a formula da potência dependendo da sua necessidade ou informações:
- Quando você não tem o conhecimento da tensão (V):
    - $P = I^2R$, esta fórmula é apropriada para calcular o calor que é gerado por uma corrente que passa por uma resistência.
- Quando você não tem conhecimento da corrente (I):
    - $P = \frac{V^2}{R}$, esta fórmula é útil para calcular a potência quando você  conhece a tensão aplicada e a resistência do componente.

**Diferença entre Potência e energia de consumo**
- **Potência (W ou kW):** é uma medida instantânea do consumo de energia por segundo do componente ou dispositivo.
- **Energia (kWh):** é a potência acumulada ao longo do tempo.
    - $Energia(kWh) = Potência(kW) * Tempo(horas)$

### 1.3.  Queda de tensão
