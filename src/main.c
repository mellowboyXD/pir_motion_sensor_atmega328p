// Connect sensor input to digital pin 8 and output led to digital pin 7.
// when sensor detects motion, it turns led on/off
#include <avr/io.h>
#include <util/delay.h>

#define set(sfr, bit) ((sfr) |= _BV((bit)))
#define unset(sfr, bit) ((sfr) &= ~_BV((bit)))

int main(void)
{
	// set PB0 as input
	unset(DDRB, DDB0);

	// set internal pull-up resistor of PB0
	set(PORTB, PORTB0);

	// set PD7 as output
	set(DDRD, DDD7);

	uint8_t state = 0;
	uint8_t val = 0;

	while (1) {
		// read value of PB0
		if (bit_is_set(PINB, PINB0)) {
                        // motion detected
			if (!state) {
				// state is HIGH
				state = 1;

				if (bit_is_set(PORTD, PORTD7)) {
					// turn off led
					unset(PORTD, PORTD7);
				} else {
					// turn led on
					set(PORTD, PORTD7);
				}

				_delay_ms(100);
			}
		} else {
			if (state) {
				// state is LOW
				state = 0;
				_delay_ms(200);
			}
		}

#ifdef SANITY_CHECK
                // test blink led
		set(PORTD, PORTD7);
		_delay_ms(500);
		unset(PORTD, PORTD7);
		_delay_ms(500);
#endif // SANITY_CHECK
	}

	return 0;
}
