
/*
 * Project name:  Interfacing LCD to PIC Microcontroller using MikroC Pro for PIC
 * Copyright:  (c) www.studentcompanion.co.za, 2013.
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Oscillator:      HS-PLL 32.0000 MHz, 8.0000 MHz Crystal
*/

// Lcd module connections
sbit LCD_RS at LATB4_bit;
sbit LCD_EN at LATB5_bit;
sbit LCD_D4 at LATB0_bit;
sbit LCD_D5 at LATB1_bit;
sbit LCD_D6 at LATB2_bit;
sbit LCD_D7 at LATB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;




   unsigned short read_ds1307(unsigned short address)
{
  unsigned short read_data;
  I2C1_Start();
  I2C1_Wr(0xD0); //address 0x68 followed by direction bit (0 for write, 1 for read) 0x68 followed by 0 --> 0xD0
  I2C1_Wr(address);
  I2C1_Repeated_Start();
  I2C1_Wr(0xD1); //0x68 followed by 1 --> 0xD1
  read_data=I2C1_Rd(0);
  I2C1_Stop();
  return(read_data);
}

void write_ds1307(unsigned short address,unsigned short write_data)
{
  I2C1_Start(); // issue I2C start signal
  //address 0x68 followed by direction bit (0 for write, 1 for read) 0x68 followed by 0 --> 0xD0
  I2C1_Wr(0xD0); // send byte via I2C (device address + W)
  I2C1_Wr(address); // send byte (address of DS1307 location)
  I2C1_Wr(write_data); // send data (data to be written)
  I2C1_Stop(); // issue I2C stop signal
}

unsigned char MSB(unsigned char x)           //Display Most Significant Bit of BCD number
{
  return ((x >> 4) + '0');
}

unsigned char  LSB(unsigned char x)          //Display Least Significant Bit of BCD number
{
  return ((x & 0x0F) + '0');
}

int BinarytoBCD(int x)
{
   int t1, t2;
   t1 = x%10;
   t1 = t1 & 0x0F;
   x = x/10;
   t2 = a%10;
   t2 = 0x0F & t2;
   t2 = t2 << 4;
   t2 = 0xF0 & t2;
   t1 = t1 | t2;
   return t1;
}

int BCDtoBinary(int x)
{
   int r,t;
   t = x & 0x0F;
   r = t;
   x = 0xF0 & x;
   t = a >> 4;
   t = 0x0F & t;
   r = t*10 + r;
   return r;
}

//Global Variables:
int second;
int minute;
int hour;
int hr;
int day;
int dday;
int month;
int year;
int ap;
//money globals
char txt[7];
int m1 = 0;
int m2 = 0;
int m3 = 0;
int m4 = 0;
int som= 0;
int tarif;
int bitta=0;

//
unsigned short set_count = 0;
short set;
// time interrupt
//Timer0
//Prescaler 1:4; TMR0 Preload = 15536; Actual Interrupt Time : 100 ms

unsigned cnt1, cnt2, cnt3, cnt4;
void Interrupt(){
  if (TMR0IF_bit){
    TMR0IF_bit = 0;
    TMR0H         = 0x3C;
    TMR0L         = 0xB0;
    cnt1++;
    cnt2++;
    cnt3++;
    cnt4++;    //Enter your code here
  }
}





char time[] = "00:00:00";
char date[]= "00-00-00";


void main()
{
   I2C1_Init(100000); //DS1307 I2C is running at 100KHz

   ADCON1 |= 0x07;        // Configure all ports with analog function as digital
        // Disable comparators
     //init timer
  T0CON         = 0x81;
  TMR0H         = 0x3C;
  TMR0L         = 0xB0;
  GIE_bit         = 1;
  TMR0IE_bit         = 1;
    //setting counters
    cnt1 = 0;
    cnt2 = 0;
    cnt3 = 0;
    cnt4 = 0;


    // Bit directions of buttons
    TRISA = 0xff;
    TRISE0_bit = 1;
    TRISE1_bit = 1;

    // Bit directions of lamps
    TRISD4_bit = 0;
    TRISD5_bit = 0;
    TRISD6_bit = 0;
    TRISD7_bit = 0;

    
    // buttons of set up down
    PORTA.RA0 = 1;
    PORTA.RA1 = 1;
    PORTA.RA2 = 1;

    // ports of switches

    PORTA.RA3 = 1;
    PORTE.RE0 = 1;
    PORTE.RE1 = 1;
    PORTE.RE2 = 1;
    // lamp ports
    PORTD.RD4 = 0;
    PORTD.RD5 = 0;
    PORTD.RD6 = 0;
    PORTD.RD7 = 0;



   Lcd_Init();                        // Initialize LCD
   Lcd_Cmd(_LCD_CLEAR);               // Clear display
   Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off

   Lcd_out(1,1,"Tarif Tollang:");
   Lcd_out(2,1,"som/minut:");
   Delay_ms(2000);
     while (bitta<1)
     {
     if (PORTA.RA1 == 0)
    {
    delay_ms(100);
    {
    if(PORTA.RC1 == 0)
    {

             som = som+1;
           IntToStr(som, txt);
           Lcd_out(2,11,txt);

           tarif = som;
    }
    }
    }


     else if (PORTA.RA2 == 0)
    {
    delay_ms(100);
    {
    if(PORTA.RA2 == 0)
    {

             som = som-1;
           IntToStr(som, txt);
           Lcd_out(2,11,txt);

           tarif = som;
    }
    }
    }




    else if (PORTA.RA0 == 0)
    {
    delay_ms(100);
    {
    if(PORTA.RA0 == 0)
    {
                bitta = 1;
    }
    }
    }
    }

   Lcd_Cmd(_LCD_CLEAR);
   Lcd_out(1,1,"CHAYHANA RAHAT ");
   Lcd_out(2,1,"HUSH KELIBSIZ");
   Delay_ms(2000);                    // 2s delay
   Lcd_Cmd(_LCD_CLEAR);               // Clear display
   Lcd_out(1,1,"Time:");
   Lcd_out(2,1,"Date:");
   Lcd_out(3,1,"TEST:");
   Lcd_out(4,1,"TEST:");

   do
   {
     /*set = 0;
     if(PORTA.RA0 == 0)
     {
         Delay_ms(100);
         if(PORTA.RA0 == 0)
         {
             set_count++;
             if(set_count >= 7)
             {
                set_count = 0;
             }
         }
     }
     if(set_count)
     {
        if(PORTA.RA1 == 0)
        {
          Delay_ms(100);
          if(PORTA.RA1 == 0)
              set = 1;
        }
        if(PORTA.RA2 == 0)
        {
          Delay_ms(100);
          if(PORTA.RA2 == 0)
              set = -1;
        }
        if(set_count && set)
        {
          switch(set_count)
          {
            case 1:
                    hour = BCDtoBinary(hour);
                    hour = hour + set;
                    hour = BinarytoBCD(hour);
                    if((hour & 0x1F) >= 0x13)
                    {
                      hour = hour & 0b11100001;
                      hour = hour ^ 0x20;
                    }
                    else if((hour & 0x1F) <= 0x00)
                    {
                      hour = hour | 0b00010010;
                      hour = hour ^ 0x20;
                    }
                    write_ds1307(2, hour); //write hour
                    break;
            case 2:
                     minute = BCDtoBinary(minute);
                     minute = minute + set;
                     if(minute >= 60)
                        minute = 0;
                     if(minute < 0)
                        minute = 59;
                     minute = BinarytoBCD(minute);
                     write_ds1307(1, minute); //write min
                     break;
            case 3:
                    if(abs(set))
                      write_ds1307(0,0x00); //Reset second to 0 sec. and start Oscillator
                    break;

              /*
            case 4:
                     day = BCDtoBinary(day);
                     day = day + set;
                     day = BinarytoBCD(day);
                     if(day >= 0x32)
                        day = 1;
                     if(day <= 0)
                        day = 0x31;
                    write_ds1307(4, day); // write date 17
                     break;

            case 5:
                    month = BCDtoBinary(month);
                    month = month + set;
                    month = BinarytoBCD(month);
                    if(month > 0x12)
                      month = 1;
                    if(month <= 0)
                      month = 0x12;
                    write_ds1307(5,month); // write month 6 June
                    break;
            case 6:
                    year = BCDtoBinary(year);
                    year = year + set;
                    year = BinarytoBCD(year);
                    if(year <= -1)
                       year = 0x99;
                    if(year >= 0x50)
                       year = 0;
                    write_ds1307(6, year); // write year
                    break;

          }
        }
     }
      */
      second = read_ds1307(0);
      minute = read_ds1307(1);
      hour = read_ds1307(2);
      //hr = hour & 0b00011111;
     // ap = hour & 0b00100000;
      dday = read_ds1307(3);
      day = read_ds1307(4);
      month = read_ds1307(5);
      year = read_ds1307(6);

      time[0] = MSB(hr);
      time[1] = LSB(hr);
      time[3] = MSB(minute);
      time[4] = LSB(minute);
      time[6] = MSB(second);
      time[7] = LSB(second);
      date[0] = MSB(day);
      date[1] = LSB(day);
      date[3] = MSB(month);
      date[4] = LSB(month);
      date[6] = MSB(year);
      date[7] = LSB(year);
     /* if(ap)
      {
         time[9] = 'A';
         time[10] = 'M';
      }
      else
      {
         time[9] = 'P';
         time[10] = 'M';
      }
        */


      // 1st lamp code

       if(PORTA.RA3==0)
       {
       Delay_ms(1);
         if(PORTA.RA3 ==0)
         {
         PORTD.RD4 = 1;

         if (cnt1 >= 10)
         {

          m1=(m1+tarif);
          IntToStr(m1, txt);
          Lcd_out(3, -5, txt);
          Lcd_out(3, 1, "som" );
          cnt1 = 0;
          }
         }
         }
         else
         {
               PORTD.RD4 = 0;
               IntToStr(m1, txt);
               Lcd_out(3, -5, txt );
               Lcd_out(3, 1, "som" );
               m1 = 0;

          }



          // 2nd lamp code

              if(PORTE.RE0==0)
       {
       Delay_ms(1);
         if(PORTE.RE0==0)
         {
         PORTD.RD5 = 1;
           if (cnt2 >= 10)
           {

            m2=(m2+tarif);
             IntToStr(m2, txt);
             Lcd_out(4, -5, txt);
             Lcd_out(4, 1, "som" );
              cnt2 = 0;
           }
         }
         }
         else
         {
           PORTD.RD5 = 0;
           IntToStr(m2, txt);
           Lcd_out(4, -5, txt);
           Lcd_out(4, 1, "som" );
           m2=0;
          }


         // 3rd lamp code


         if(PORTE.RE1==0)
         {
          Delay_ms(1);
          if(PORTE.RE1==0)
         {
          PORTD.RD6 = 1;

         if (cnt3 >= 10)
         {


          m3 = (m3+tarif);

          IntToStr(m3, txt);
          Lcd_out(3, 4, txt);
          Lcd_out(3, 10, "som");
          cnt3 = 0;
          }

         }
         }
         else
         {
               PORTD.RD6 = 0;
               IntToStr(m3, txt);
               Lcd_out(3, 4, txt);
               Lcd_out(3, 10, "som");
               m3 =0;
          }


          // 4th lamp code


           if(PORTE.RE2==0)
       {
       Delay_ms(1);
         if(PORTE.RE2==0)
         {
         PORTD.RD7 = 1;
         if (cnt4 >= 10)
         {

          m4=(m4+tarif);
          IntToStr(m4, txt);
          Lcd_out(4, 4, txt);
          Lcd_out(4, 10, "som");
          cnt4 = 0;
         }
         }
         }
         else
         {
          PORTD.RD7 = 0;
          IntToStr(m4, txt);
          Lcd_out(4, 4, txt);
          Lcd_out(4, 10, "som");
          m4 =0;
          }






      Lcd_out(1, 6, time);

      Lcd_out(2, 6, date);



      Delay_ms(100);

   }while(1);
}
