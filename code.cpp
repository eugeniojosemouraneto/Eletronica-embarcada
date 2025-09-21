#define PIN_LED PB5
#define PIN_BUTTON PD2

int main() {
    DDRB |= (1 << PIN_LED);
    PORTB &= ~(1 << PIN_LED);
    DDRD &= ~(1 << PIN_BUTTON);
    PORTD &= ~(1 << PIN_BUTTON);

    while(1) {
        if(PIND & (1 << PIN_BUTTON)) {
            PORTB |= (1 << PIN_LED);
        }
    }
}