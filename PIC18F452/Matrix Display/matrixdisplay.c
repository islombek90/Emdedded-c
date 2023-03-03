void main()
{
TRISC = 0x00;
TRISD = 0;

do{

PORTD = 0b1111110;
PORTC = 0b00000100;
delay_ms(5);
PORTD = 0b1111101;
PORTC = 3;
delay_ms(5);
PORTD = 0b1111011;
PORTC = 2;
delay_ms(5);
PORTD = 0b1110111;
PORTC = 1;
delay_ms(5);
PORTD = 0b1101111;
PORTC = 0;
delay_ms(5);
PORTD = 0b1011111;
PORTC = 0;
delay_ms(5);
PORTD = 0b0111111;
PORTC = 0;
delay_ms(5);
} while(1);
}