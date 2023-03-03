//Timer0
//Prescaler 1:4; TMR0 Preload = 15536; Actual Interrupt Time : 100 ms

 // LCD module connections
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;
sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;
// End LCD module connections

  int i;
  int bitta = 0;
//Place/Copy this part in declaration section
char txt[7];
unsigned cnt, j;
int som = 0;
int  tarif;
/*void InitTimer0(){
  T0CON         = 0x81;
  TMR0H         = 0x3C;
  TMR0L         = 0xB0;
  GIE_bit         = 1;
  TMR0IE_bit         = 1;
}
   */
void Interrupt(){
  if (TMR0IF_bit){
    TMR0IF_bit = 0;
    TMR0H         = 0x3C;
    TMR0L         = 0xB0;
    cnt++;    //Enter your code here
  }
}


 
      //tarif example



 
void main() {

     ADCON1 |= 0x0F;        // Configure all ports with analog function as digital
    CMCON  |= 7;
   //init timer
  T0CON         = 0x81;
  TMR0H         = 0x3C;
  TMR0L         = 0xB0;
  GIE_bit         = 1;
  TMR0IE_bit         = 1;
  
  
    TRISA  = 0;
    TRISC = 0xff;              // PORTB is output
    LATA = 0;             // Initialize PORTB

   Lcd_Init();                        // Initialize LCD
   Lcd_Cmd(_LCD_CLEAR);               // Clear display
   Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
   Lcd_out(1,1,"Tarif :");
   Delay_ms(2000);
     while (bitta<1)
     {
     if (PORTC.RC1 == 0)
    {
    delay_ms(100);
    {
    if(PORTC.RC1 == 0)
    {

             som = som+1;
           IntToStr(som, txt);
           Lcd_out(1,7,txt);
           Lcd_out(1,14,"s/m");
           tarif = som;
    }
    }
    }


     else if (PORTC.RC2 == 0)
    {
    delay_ms(100);
    {
    if(PORTC.RC2 == 0)
    {

             som = som-1;
           IntToStr(som, txt);
           Lcd_out(1,7,txt);
           Lcd_out(1,14,"s/m");
           tarif = som;
    }
    }
    }

    


    else if (PORTC.RC3 == 0)
    {
    delay_ms(100);
    {
    if(PORTC.RC3 == 0)
    {
                bitta = 1;
    }
    }
    }
    }
   Lcd_Cmd(_LCD_CLEAR);
   Lcd_out(1,1,"Choyhona RAHAT ");
   Lcd_out(2,1,"HUSH KELIBSIZ");
   Delay_ms(2000);                    // 2s delay
   Lcd_Cmd(_LCD_CLEAR);               // Clear display
   Lcd_out(1,1,"Tarif:");




  
   do {


    
   if (PORTC.RC0 == 0)
   {
    delay_ms(1);
       if (PORTC.RC0 == 0)
       {
          if (cnt >= 10) {
           LATA = ~PORTA;
           j= (j+tarif);     // Toggle PORTB LEDs
           IntToStr(j, txt);
           Lcd_out(2,1,txt);
           cnt = 0;             // Reset cnt
           
           
    }
    }
    }





  
  } while(1);
}