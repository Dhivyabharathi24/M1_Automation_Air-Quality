/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
? Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 22-03-2016
Author  : NeVaDa
Company : 
Comments: 


Chip type               : ATmega8
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega8.h>

#include <delay.h>
#include <alcd.h>
   int S;
// Alphanumeric LCD Module functions
  #include <stdio.h> 
   #include <stdlib.h>    
   
  int T1,T2,T3,T4,s;
   eeprom unsigned int gps,gps1;  



#define ADC_VREF_TYPE 0xC0
//

void adc_init(void)
{
   
   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz

   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC
   //ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading

   // No MUX values needed to be changed to use ADC0

   //ADCSRA |= (1 << ADFR);  // Set ADC to Free-Running Mode
   ADCSRA |= (1 << ADEN);  // Enable ADC
   ADCSRA |= (1 << ADSC);  // Start A2D Conversions
}


// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
}

  void sendtext(char *text) //for sending text
{
  char i=0;
  while (text[i]!=0)
 {
  putchar(text[i]);
  i++;
  delay_ms(10);
  }
}


signed int v,i,c,p,r;

  void num(unsigned int s)
{
 unsigned int a;
 unsigned char b,c,d,e,f;
 a=s/10;
 b=s%10;
 c=a%10;
 d=a/10;
 e=d%10;
 f=d/10;
 lcd_putchar(f+0x30);
 lcd_putchar(e+0x30);
 lcd_putchar(c+0x30);
 lcd_putchar(b+0x30);
 
}



void send(unsigned int s)
{
 unsigned int a;
 unsigned char b,c,d,e,f;
 a=s/10;
 b=s%10;
 c=a%10;
 d=a/10;
 e=d%10;
 f=d/10;
 putchar(f+0x30);
 putchar(e+0x30);
 putchar(c+0x30);
 putchar(b+0x30);
 //putchar(0x0A);
}


 

#ifndef RXB8
#define RXB8 1
#endif

#ifndef TXB8
#define TXB8 0
#endif

#ifndef UPE
#define UPE 2
#endif

#ifndef DOR
#define DOR 3
#endif

#ifndef FE
#define FE 4
#endif

#ifndef UDRE
#define UDRE 5
#endif

#ifndef RXC
#define RXC 7
#endif

#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<DOR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)

// USART Receiver buffer
#define RX_BUFFER_SIZE 8
char rx_buffer[RX_BUFFER_SIZE];

#if RX_BUFFER_SIZE <= 256
unsigned char rx_wr_index,rx_rd_index,rx_counter;
#else
unsigned int rx_wr_index,rx_rd_index,rx_counter;
#endif

// This flag is set on USART Receiver buffer overflow
bit rx_buffer_overflow;

// USART Receiver interrupt service routine
interrupt [USART_RXC] void usart_rx_isr(void)
{
char status,data;
status=UCSRA;
data=UDR;
 {
//  if(data=='A')  {lcd_gotoxy(0,1);lcd_puts("S1:ON ");PORTD.4=1;delay_ms(1000);  }
//  if(data=='B')  {lcd_gotoxy(0,1);lcd_puts("S1:OFF"); PORTD.4=0;delay_ms(1000);   }  
//  if(data=='C')  {    PORTD.5=1;lcd_gotoxy(0,1);lcd_puts("S2:ON ");delay_ms(1000);   }  
//  if(data=='D')  {    PORTD.5=0;lcd_gotoxy(0,1);lcd_puts("S2:OFF");delay_ms(1000);   }  
//  if(data=='E')  {    PORTD.6=1;lcd_gotoxy(0,1);lcd_puts("S3:ON ");delay_ms(1000);   } 
//  if(data=='F')  {    PORTD.6=0;lcd_gotoxy(0,1);lcd_puts("S3:OFF");delay_ms(1000);   }
//  if(data=='G')  {    PORTD.7=1;  }
//  if(data=='H')  {    PORTD.7=0;  }
// check();
//  if(data=='F')  {     PORTD.6=0; PORTD.7=1;delay_ms(1000); lcd_gotoxy(0,2);lcd_puts("S3:OFF");}  
//  if(data=='G')  {     PORTD.7=1; PORTD.6=0;delay_ms(1000); lcd_gotoxy(0,3);lcd_puts("S4:ON ");}  
//  if(data=='H')  {     PORTD.7=0; PORTD.6=1;delay_ms(1000); lcd_gotoxy(0,3);lcd_puts("S4:OFF");}  
//  else 
//  {
//   PORTD.2=0; 
//   PORTD.3=0; 
//   PORTD.4=0; 
//   PORTD.5=0;  
//   PORTD.6=0;
//   PORTD.7=0;
//  }
 }
 
}

#ifndef _DEBUG_TERMINAL_IO_
// Get a character from the USART Receiver buffer
#define _ALTERNATE_GETCHAR_
#pragma used+
char getchar(void)
{
char data;
while (rx_counter==0);
data=rx_buffer[rx_rd_index++];
#if RX_BUFFER_SIZE != 256
if (rx_rd_index == RX_BUFFER_SIZE) rx_rd_index=0;
#endif
#asm("cli")
--rx_counter;
#asm("sei")
return data;
}
#pragma used-
#endif

// USART Transmitter buffer
#define TX_BUFFER_SIZE 8
char tx_buffer[TX_BUFFER_SIZE];

#if TX_BUFFER_SIZE <= 256
unsigned char tx_wr_index,tx_rd_index,tx_counter;
#else
unsigned int tx_wr_index,tx_rd_index,tx_counter;
#endif

// USART Transmitter interrupt service routine
interrupt [USART_TXC] void usart_tx_isr(void)
{
if (tx_counter)
   {
   --tx_counter;
   UDR=tx_buffer[tx_rd_index++];
#if TX_BUFFER_SIZE != 256
   if (tx_rd_index == TX_BUFFER_SIZE) tx_rd_index=0;
#endif
   }
}

#ifndef _DEBUG_TERMINAL_IO_
// Write a character to the USART Transmitter buffer
#define _ALTERNATE_PUTCHAR_
#pragma used+
void putchar(char c)
{
while (tx_counter == TX_BUFFER_SIZE);
#asm("cli")
if (tx_counter || ((UCSRA & DATA_REGISTER_EMPTY)==0))
   {
   tx_buffer[tx_wr_index++]=c;
#if TX_BUFFER_SIZE != 256
   if (tx_wr_index == TX_BUFFER_SIZE) tx_wr_index=0;
#endif
   ++tx_counter;
   }
else
   UDR=c;
#asm("sei")
}
#pragma used-
#endif

// Standard Input/Output functions
#include <stdio.h>

// Declare your global variables here
void senttext(char *text) //for sending text
{
  char i=0;
  while (text[i]!=0)
 {
  putchar(text[i]);
  i++;
  delay_ms(100);
  }
}

 


 long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

  
  void gps_data()
  {       
        gps=(rand()+gps1)/75;
         lcd_gotoxy(0,1); 
         
          sendtext("ABNORMAL ALERT:"); 
                 sendtext("11.5537 N"); 
       
               lcd_puts("11.");
             
            num(gps);
         lcd_puts("N");
       
            gps1=((gps1+gps)*50/48);
            lcd_gotoxy(8,1); 
               sendtext("78.0078 E"); 
          lcd_puts("78.");
         num(gps1);
           lcd_puts("E");
              putchar(0x0d); 
            
  }
       
  

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTB=0x01;
DDRB=0x02;

// Port C initialization
// Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0x00;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0x8C;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
TCCR0=0x00;
TCNT0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
MCUCR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 9600
UCSRA=0x00;
UCSRB=0xD8;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x33;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC Clock frequency: 1000.000 kHz
// ADC Voltage Reference: Int., cap. on AREF

ADCSRA=0x83;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;

// Alphanumeric LCD initialization
// Connections specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTB Bit 2
// RD - PORTB Bit 4
// EN - PORTB Bit 5
// D4 - PORTC Bit 0
// D5 - PORTC Bit 1
// D6 - PORTC Bit 2
// D7 - PORTD Bit 7
// Characters/line: 16
   lcd_init(20);
   adc_init();
   lcd_gotoxy(4,1);
   lcd_puts("WELCOME"); 

   delay_ms(2000);
   lcd_clear(); 
   
   
// Global enable interrupts
#asm("sei")      

while (1)
        {   
                lcd_clear();
          PORTD.7=0;
        T1=read_adc(4)/2;
        lcd_gotoxy(0,0);
        lcd_puts("Co2:");
     num(T1);       
 
        
//        send(T1);
   
         
            
         T2=read_adc(5)/2;
        lcd_gotoxy(9,0);
        lcd_puts("CH4:");
 num(T2);     
                  
         T3=read_adc(5)/1.5;
        lcd_gotoxy(0,1);
        lcd_puts("Smo:");
 num(T3);   
     
         T4=read_adc(5)/1.8;
        lcd_gotoxy(9,1);
        lcd_puts("NH3:");
 num(T4);   
 
 
  delay_ms(1000); 
//         puts("LPG: "); 
//         send(T2);
//          putchar(0x0d);
        
          
//         T4=read_adc(2);
////        lcd_gotoxy(9,1);
////        lcd_puts("SO:");
//lcd_gotoxy(0,1);
//        lcd_puts("Normal:");
//           
       // num(T4);
        // send(T4); 
                  lcd_clear(); 
                     lcd_gotoxy(0,1);
        lcd_puts("Normal:");
             puts("Pollution normal ");
         putchar(0x0d);
                  delay_ms(1000); 
                  lcd_clear();
          
             if(T1>500)  
          {
          
          PORTD.7=1;
          lcd_gotoxy(0,1);
        lcd_puts("Abnormal Alert:");   
         puts("Pollution abnormal "); 
                delay_ms(1000);
                 
          }      
          
          
          else    if(T2>500)  
          {
             PORTD.7=1;  
             lcd_gotoxy(0,1);
        lcd_puts("Abnormal Alert:");
         puts("Pollution abnormal "); 
                   delay_ms(1000);
          
          }     
            else    if(T3>500)  
          {
             PORTD.7=1;  
             lcd_gotoxy(0,1);
        lcd_puts("Abnormal Alert:");
         puts("Pollution abnormal "); 
                   delay_ms(1000);
          
          }  
          
            else    if(T4>500)  
          {
             PORTD.7=1;  
             lcd_gotoxy(0,1);
        lcd_puts("Abnormal Alert:");
         puts("Pollution abnormal "); 
                   delay_ms(1000);
          
          }  
          
          
//             else   if(T4>850)  
//          {
//             PORTD.7=1;
//             lcd_gotoxy(0,1);
//        lcd_puts("Abnormal Alert:");
//         puts("Pollution abnormal "); 
//                   delay_ms(1000);
//          
//          }  
         delay_ms(1000);
         puts("============================================="); 
         putchar(0x0d); 
 
          if(T1>500)  
          {
          
          PORTD.7=1;
          lcd_gotoxy(0,1);
        lcd_puts("Abnormal Alert:");  
         puts("Pollution abnormal "); 
                delay_ms(2000);
          }      
          
          
          else    if(T2>500)  
          {
             PORTD.7=1;
             lcd_gotoxy(0,1);
        lcd_puts("Abnormal Alert:"); 
         puts("Pollution abnormal "); 
                   delay_ms(2000);
          
          }  
          
//             else   if(T4>850)  
//          {
//             PORTD.7=1;
//             lcd_gotoxy(0,1);
//        lcd_puts("Abnormal Alert:"); 
//         puts("Pollution abnormal "); 
//                   delay_ms(2000);
//          
//          }  
              
            
             
}
}