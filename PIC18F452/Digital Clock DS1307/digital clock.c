
 // modified by ISLOMBEK MAMATOV
 // shunisi ishledi
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
#include <built_in.h>






unsigned short read_ds1307(unsigned short address)
{
  unsigned short r_data;
  I2C1_Start();
  I2C1_Wr(0xD0); //address 0x68 followed by direction bit (0 for write, 1 for read) 0x68 followed by 0 --> 0xD0
  I2C1_Wr(address);
  I2C1_Repeated_Start();
  I2C1_Wr(0xD1); //0x68 followed by 1 --> 0xD1
  r_data=I2C1_Rd(0);
  I2C1_Stop();
  return(r_data);
}


void write_ds1307(unsigned short address,unsigned short w_data)
{
  I2C1_Start(); // issue I2C start signal
  //address 0x68 followed by direction bit (0 for write, 1 for read) 0x68 followed by 0 --> 0xD0
  I2C1_Wr(0xD0); // send byte via I2C (device address + W)
  I2C1_Wr(address); // send byte (address of DS1307 location)
  I2C1_Wr(w_data); // send data (data to be written)
  I2C1_Stop(); // issue I2C stop signal
}


unsigned char BCD2UpperCh(unsigned char bcd)
{
  return ((bcd >> 4) + '0');
}


unsigned char BCD2LowerCh(unsigned char bcd)
{
  return ((bcd & 0x0F) + '0');
}


int Binary2BCD(int a)
{
   int t1, t2;
   t1 = a%10;
   t1 = t1 & 0x0F;
   a = a/10;
   t2 = a%10;
   t2 = 0x0F & t2;
   t2 = t2 << 4;
   t2 = 0xF0 & t2;
   t1 = t1 | t2;
   return t1;
}


int BCD2Binary(int a)
{
   int r,t;
   t = a & 0x0F;
   r = t;
   a = 0xF0 & a;
   t = a >> 4;
   t = 0x0F & t;
   r = t*10 + r;
   return r;
}

// timer setup
unsigned cnt1=0 , cnt2=0, cnt3=0, cnt4=0;
 void Interrupt(){
  if (TMR0IF_bit){

    TMR0IF_bit = 0;
    TMR0H         = 0x3C;
    TMR0L         = 0xB0;

    // TIMER1
    if(PORTA.RA3==0)
       {
       Delay_ms(10);
         if(PORTA.RA3 ==0)
         {


         cnt1++;
         }
         else
         {

         cnt1 = 0;

         }
          }
          //TIMER 2
           if(PORTE.RE0==0)
       {
       Delay_ms(1);
         if(PORTE.RE0==0)
         {
    cnt2++;

    }
    else {cnt2 = 0;  }
    }

    //TIMER 3
     if(PORTE.RE1==0)
         {
          Delay_ms(1);
          if(PORTE.RE1==0)
         {
    cnt3++;

    }
    else {cnt3 = 0;  }
    }
    //TIMER 4
       if(PORTE.RE2==0)
       {
       Delay_ms(1);
         if(PORTE.RE2==0)
         {
    cnt4++;

    }
    else {cnt4 = 0;  }
    }  //Enter your code here
  }
}

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
char txt[15];
char txt3[21],txt1[21],txt2[21],cntt;
char float_txt[15];
float m1 = 0.00;
float m2 = 0.00;
float m3 = 0.00;
float m4 = 0.00;
float som = 0.00;
float tarif = 0;
int bitta =0;
float lastvalue1 = 0.00;
float lastvalue2 = 0.00;
float lastvalue3 = 0.00;
float lastvalue4 = 0.00;
float toplam = 0;
float tempdata = 0;
float mem;
//



unsigned short set_count = 0;
short set;


char time[] = "00:00:00 ";
char date[] = "00-00-00";

void main()
{
   I2C1_Init(100000); //DS1307 I2C is running at 100KHz
  ADCON1 |= 0x07;        // Configure all ports with analog function as digital
         //init timer
  T0CON         = 0x81;
  TMR0H         = 0x3C;
  TMR0L         = 0xB0;
  GIE_bit         = 1;
  TMR0IE_bit         = 1;
  cnt1 =0;
  cnt2 =0;
  cnt3 =0;
  cnt4 =0;

    // Bit directions of buttons
    TRISA = 0xff;
    TRISE0_bit = 1;
      TRISE1_bit = 1;
         TRISE2_bit = 1;
    // Bit directions of lEDS
  TRISD = 0;
  PORTD = 0;

    // buttons of set up down
    PORTA.RA0 = 1;
    PORTA.RA1 = 1;
    PORTA.RA2 = 1;

    // ports of switches

    PORTA.RA3 = 1;
    PORTE.RE0 = 1;
    PORTE.RE1 = 1;
    PORTE.RE2 = 1;
    // LED ports


   delay_ms(100);
   Lcd_Init(); 
   delay_ms(100);                       // Initialize LCD
   Lcd_Cmd(_LCD_CLEAR);               // Clear display
   Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
   Lcd_out(1,1,"TARIF TOLLANG:");
   Lcd_out(2,1,"som/soat:");
   Lcd_out(3,-3,"som/minut:");
   Delay_ms(2000);
    // AT THE BEGINING, CHOOSING VALUE FOR COUNTER TO ADD THIS VALUE,  FOR ONE LOOP ONLY,

     while (bitta<1)
     {
     if (PORTA.RA1 == 0)
    {
    delay_ms(100);
    {
    if(PORTA.RA1 == 0)
    {

           som = som + 10;
           IntToStr(som, txt);
           Lcd_out(2,11,txt);

           tarif = (float)(som/60.0);

           //FloatToStr(tarif, float_txt);
           sprintf(float_txt,"%.2f",tarif);
           Lcd_out(3,9,float_txt);
    }
    }
    }


     else if (PORTA.RA2 == 0)
    {
    delay_ms(100);
    {
    if(PORTA.RA2 == 0)
    {

             som = som - 10;
           IntToStr(som, txt);
           Lcd_out(2,11,txt);

           tarif = som/60.0;

          // FloatToStr(tarif, float_txt);
           sprintf(float_txt,"%.2f",tarif);
           Lcd_out(3,9,float_txt);
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


  // STARTING MAIN LOOP
   Lcd_Cmd(_LCD_CLEAR);
   Lcd_out(1,1,"CHAYHANA RAHAT ");
   Lcd_out(2,1,"HUSH KELIBISIZ");
   Delay_ms(2000);                    // 2s delay
   Lcd_Cmd(_LCD_CLEAR);               // Clear display
   Lcd_out(1,1,"Soat:");
   //Lcd_out(2,1,"Sana:");
   do
   {
     set = 0;
     if(PORTA.F0 == 0)
     {
         Delay_ms(100);
         if(PORTA.F0 == 0)
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
        if(PORTA.F1 == 0)
        {
          Delay_ms(100);
          if(PORTA.F1 == 0)
              set = 1;
        }

        if(PORTA.F2 == 0)
        {
          Delay_ms(100);
          if(PORTA.F2 == 0)
              set = -1;
        }
        if(set_count && set)
        {
          switch(set_count)
          {
            case 1:
                    hour = BCD2Binary(hour);
                    hour = hour + set;
                    hour = Binary2BCD(hour);
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
                     minute = BCD2Binary(minute);
                     minute = minute + set;
                     if(minute >= 60)
                        minute = 0;
                     if(minute < 0)
                        minute = 59;
                     minute = Binary2BCD(minute);
                     write_ds1307(1, minute); //write min
                     break;
            case 3:
                    if(abs(set))
                      write_ds1307(0,0x00); //Reset second to 0 sec. and start Oscillator
                    break;
            case 4:
                     day = BCD2Binary(day);
                     day = day + set;
                     day = Binary2BCD(day);
                     if(day >= 0x32)
                        day = 1;
                     if(day <= 0)
                        day = 0x31;
                     write_ds1307(4, day); // write date 17
                     break;
            case 5:
                    month = BCD2Binary(month);
                    month = month + set;
                    month = Binary2BCD(month);
                    if(month > 0x12)
                      month = 1;
                    if(month <= 0)
                      month = 0x12;
                    write_ds1307(5,month); // write month 6 June
                    break;
            case 6:
                    year = BCD2Binary(year);
                    year = year + set;
                    year = Binary2BCD(year);
                    if(year <= -1)
                       year = 0x99;
                    if(year >= 0x50)
                       year = 0;
                    write_ds1307(6, year); // write year

                    break;
          }
        }
     }

      second = read_ds1307(0);
      minute = read_ds1307(1);
      hour = read_ds1307(2);
       hr = hour & 0b00011111;
       ap = hour & 0b00100000;
      dday = read_ds1307(3);
      day = read_ds1307(4);
      month = read_ds1307(5);
      year = read_ds1307(6);


      time[0] = BCD2UpperCh(hr);
      time[1] = BCD2LowerCh(hr);
      time[3] = BCD2UpperCh(minute);
      time[4] = BCD2LowerCh(minute);
      time[6] = BCD2UpperCh(second);
      time[7] = BCD2LowerCh(second);

      date[0] = BCD2UpperCh(day);
      date[1] = BCD2LowerCh(day);
      date[3] = BCD2UpperCh(month);
      date[4] = BCD2LowerCh(month);
      date[6] = BCD2UpperCh(year);
      date[7] = BCD2LowerCh(year);
      /*
      if(ap)
      {
         time[9] = 'P';
         time[10] = 'M';
      }
      else
      {
         time[9] = 'A';
         time[10] = 'M';
      }
        */

         
      // WHEN CLOSE SWITCHES THE LEDS TURN ON
      // 1st lED code, SW1
        if (toplam > 9999)
        {
        toplam = 0;
        }
       if(PORTA.RA3==0)
       {
       Delay_ms(10);
         if(PORTA.RA3 ==0)
         {

            LATD.RD4 = 1;

             //IntToStr(m1, txt);
             sprintf(txt,"%.2fC  ",m1);
             Lcd_out(4, -3, txt);
            //Lcd_out(3, 3, "C" );

        if (cnt1 >= 600)
         {

          m1=(m1+tarif);

          //IntToStr(m1, txt);
          sprintf(txt,"%.2fC  ",m1);
          Lcd_out(4, -3, txt);
          //Lcd_out(3, 3, "C" );
          cnt1 = 0;

          lastvalue1 = m1;
          }
         }
          }
         else
         {

                LATD.RD4 = 0;
                toplam = toplam +m1;
               //IntToStr(lastvalue1, txt);
               sprintf(txt,"%.2fC  ",lastvalue1);
               Lcd_out(4, -3, txt );
              // Lcd_out(3, 3, "C" );
               m1 = 0.00;

          }



          // 2nd LED code    SW2

              if(PORTE.RE0==0)
       {
       Delay_ms(1);
         if(PORTE.RE0==0)
         {


            LATD.RD5 = 1;

             //IntToStr(m2, txt);
             sprintf(txt,"%.2fC  ",m2);
             Lcd_out(4, 6, txt);
             //Lcd_out(4, 3, "C" );

           if (cnt2 >= 600)
           {

            m2=(m2+tarif);
             //IntToStr(m2, txt);
             sprintf(txt,"%.2fC  ",m2);
             Lcd_out(4, 6, txt);
             //Lcd_out(4, 3, "C" );
              cnt2 = 0;
              lastvalue2 = m2;
           }
         }
         }
         else
         {



                LATD.RD5 = 0;
                toplam = toplam +m2;
           //IntToStr(lastvalue2, txt);
           sprintf(txt,"%.2fC  ",lastvalue2);
           Lcd_out(4, 6, txt);
           //Lcd_out(4, 3, "C" );
           m2=0.00;
          }


         // 3rd LED code          SW3


         if(PORTE.RE1==0)
         {
          Delay_ms(1);
          if(PORTE.RE1==0)
         {

            LATD.RD6 = 1;

          //IntToStr(m3, txt);
          sprintf(txt,"%.2fC  ",m3);
          Lcd_out(3, -3, txt);
          //Lcd_out(3, 12, "C");


         if (cnt3 >= 600)
         {


          m3 = (m3+tarif);

          //IntToStr(m3, txt);
          sprintf(txt,"%.2fC  ",m3);
          Lcd_out(3, -3, txt);
          //Lcd_out(3, 12, "C");
          cnt3 = 0;
          lastvalue3 = m3;
          }

         }
          }
         else
         {




               LATD.RD6= 0;
                toplam = toplam +m3;
               //IntToStr(lastvalue3, txt);
               sprintf(txt,"%.2fC  ",lastvalue3);
               Lcd_out(3, -3, txt);
            // Lcd_out(3, 12, "C");
               m3 =0.00;
          }


        // 4th LED code      SW4


           if(PORTE.RE2==0)
       {
       Delay_ms(1);
         if(PORTE.RE2==0)
         {



            LATD.RD7= 1;
          //IntToStr(m4, txt);
          sprintf(txt,"%.2fC  ",m4);
          Lcd_out(3, 6, txt);
          //Lcd_out(4, 12, "C");

         if (cnt4 >= 600)
         {

          m4=(m4+tarif);
          //IntToStr(m4, txt);
          sprintf(txt,"%.2fC  ",m4);
          Lcd_out(3, 6, txt);
          //Lcd_out(4, 12, "C");
          cnt4 = 0;
          lastvalue4 = m4;
         }
         }
         }
         else
         {

             LATD.RD7 =0;
               toplam = toplam +m4;
          //IntToStr(lastvalue4, txt);
          sprintf(txt,"%.2fC  ",lastvalue4);
          Lcd_out(3, 6, txt);
          //Lcd_out(4, 12, "C");
          m4 =0.00;
          }









sprintf(txt1,"%2.2f",toplam);

for (cntt=0;cntt < sizeof(txt1); cntt++){
EEPROM_Write(cntt,txt1[cntt]);
delay_ms(20);
}
for (cntt=0;cntt < sizeof(txt2);cntt++){
txt2[cntt]=(EEPROM_Read(cntt));
}
mem=atof(txt2);
sprintf(txt3,"%2.2f",mem);
//Lcd_out_cp(2, 10, txt2);
Lcd_out(2, 10, txt3);


  eeprom_write(00,Highest(toplam));
delay_ms(100);
eeprom_write(01,Higher(toplam));
delay_ms(100);
eeprom_write(02,Hi(toplam));
delay_ms(100);
eeprom_write(03,Lo(toplam));
delay_ms(100);

Highest(tempdata)=eeprom_read(0);
Higher(tempdata)=eeprom_read(1);
Hi(tempdata)=eeprom_read(2);
Lo(tempdata)=eeprom_read(3);

sprintf(txt3,"%2.2f",tempdata);
lcd_out(2,10,txt3);


      Lcd_out(1, 6, time);
      Lcd_out(2, 1, date);
      sprintf(txt,"%.2f   ",tempdata);
      Lcd_out(2, 10, txt1);
      
        // experiment

        /*if (time )
              {

                PORTD.RD0 = 1;
                delay_ms(1000);
                PORTD.RD0 = 0;
                }
                 /*
                Lcd_out(2, 1, "Budilnik");
              }      */
      Delay_ms(100);


   }while(1);
}