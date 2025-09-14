#include <avr/interrupt.h>

#define PRESCALER_64 ((1 << CS01) | (1 << CS00))
#define TIMER0_OVERFLOW_INTERRUPT_ENABLE (1 << TOIE0)


volatile uint32_t millis_count = 0;

ISR(TIMER0_OVF_vect) {
    millis_count++;
}

void timer0_init() {
    TCCR0A = 0x00; // contador compara canal A
    TCCR0B = PRESCALER_64; // prescaler 64
    TIMSK0 = TIMER0_OVERFLOW_INTERRUPT_ENABLE;
}

void my_delay_ms(uint32_t ms) {
    uint32_t start_time = millis_count;
    while ((millis_count - start_time) < ms);
}