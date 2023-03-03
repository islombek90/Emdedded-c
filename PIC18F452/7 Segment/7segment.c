//7 segment


#define sw1 PORTA.RA0

unsigned char const SEGMENT_MAP[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,0xF7, 0xFC, 0xB9, 0xDE, 0xF9, 0xF1};  //common cathode counter with hexadecimal , no decimal point till 'A'
//unsigned char const SEGMENT_MAP[16] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};  //common anode counter with hexadecimal , no decimal point
//unsigned char const SEGMENT_MAP[16] = {63,6,91,79,102,109,125,7,127, 111,119,124,57,94,121,113 }; // common cathode counter with decimal code, no decimal point
//unsigned char const SEGMENT_MAP[16] = {192, 249,164,176,153,146,130,248,128,144,136,131,198, 161,134,142 }; // common anode counter with decimal code , no decimal point
unsigned char digit = 0;
//unsigned count = 0;

void main() {
 ADCON1 = 0x07;   // configure all ports as digital
 TRISB = 0 ;      // configure portb as outputs   for cammon Cathode mode
 //TRISB = 1 ;      // configure portb as inputs for Common Anode mode
 TRISA.RA0 = 1;     // configure RA0 as input

 while(1)
 {
 if (sw1 == 0)
 {
 delay_ms(10);
 if (sw1 == 0)
 {
 LATB = (SEGMENT_MAP[digit]);
 delay_ms(1000);
 digit++;
 if (digit > 15)digit = 0;
 
 }
 }
  else
  {
  LATB = (SEGMENT_MAP[digit]);
  }
 }
 
 
 
 
}