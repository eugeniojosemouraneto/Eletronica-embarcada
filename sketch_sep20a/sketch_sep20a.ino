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
            atraso_ms_timer0(1);
        }
        for(uint8_t nivel_brilho = 255; nivel_brilho > 0; nivel_brilho--) {
            OCR0A = nivel_brilho;
            atraso_ms_timer0(1);
        }
    }
}

void atraso_ms_timer0(uint16_t millisegundos) {
  	if(millisegundos == 0) return;
  	
  	uint32_t overflows = ((uint32_t)millisegundos * 125 + 127) / 128;
  	TCNT0 = 0;
	TIFR0 |= (1 << TOV0);
	
  for(uint32_t i = 0; i < overflows; i++) {
    while(!(TIFR0 & (1 << TOV0)));
    TIFR0 |= (1 << TOV0);
  }
}

void calibracao_timer0_fast_pwm_nao_invertida_prescaler64() {
    TCCR0A = 0;
    TCCR0B = 0;
    TCNT0  = 0;  
  
  	// Timer0 modo Fast PWM saída não-invertida no pino OC0A
    TCCR0A |= TIMER0_FAST_PWM_NAO_INVERTIDO_OC0A;
    // Timer0 prescaler 64
    TCCR0B |= TIMER0_PRESCALER_64;
    // Garantir que flags antigas não interfiram
  	TIFR0 |= (1 << TOV0);
}