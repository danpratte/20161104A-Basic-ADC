#define F_CPU 16000000
#include <avr/io.h>
#define PORT_ON(port,pin) port |= (1<<pin)
#define PORT_OFF(port,pin) port &= ~(1<<pin)
#define BEGIN	{
#define END		}	

int main(void)
BEGIN
	unsigned int ADCValue;	// Variable to hold ADC result
	DDRD=0xFF;				// Set Port A as Output
	PORTD = 0x00;			// A Pins Low
	
	ADMUX = (1<<REFS0);  // AVCC with external capacitor at AREF pin. Also MUX4:0, take the 0 default for ADC0.
	
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); 
	// ADEN: Set to turn on ADC. By default it is turned off.
	// ADPS2: ADPS2 and ADPS0 set to invoke prescaler at 128
	

	while (1)
	BEGIN
		ADCSRA |= (1<<ADSC); // In Free Running mode, write this bit to 1 to start conversion
		
		// wait for conversion to complete...then ADSC becomes ’0′ again...till then, run loop continuously
		while(ADCSRA & (1<<ADSC));
				
		ADCValue = ADC; //Store ADC value
		
		if (ADCValue < 512)
		BEGIN
			PORT_OFF(PORTD,7); // Toggle LEDs
			PORT_ON (PORTD,6);
		END	
		else
		BEGIN
			PORT_ON(PORTD,7); // Toggle LEDs
			PORT_OFF (PORTD,6);
		END
	END
END
