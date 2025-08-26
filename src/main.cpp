#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#define buzzer PD4
// this three difines sets up the speedrate of the UART and initilizing it
#define clk_speed 16000000
#define baud 9600
#define my_ubrr (clk_speed/16/baud-1)
//////////////////////////////////////////////
#define gas_A0 PC3
//in this function we set up the USART if u wanna know how these register works and stuff you have to go and look at the datasheet
void USART_init(unsigned int ubrr){
  UBRR0H=(unsigned char)(ubrr>>8);
  UBRR0L=(unsigned char)ubrr;
  UCSR0B=(1<<RXEN0)|(1<<TXEN0);
  UCSR0C=(1<<UCSZ00)|(1<<UCSZ01);
}
//transmitter
void USART_TX(unsigned char data){
  while(!(UCSR0A&(1<<UDRE0)));
  UDR0=data;
}
//recivier
unsigned char USART_RX(void){
while(!(UCSR0A&(1<<RXC0)));
  return UDR0;
}
//and this is the function that we will pass the string 
void USART_strTransmit(char*str){
  while(*str){
    USART_TX(*str++);
  }
}
/////////////////////////////////////////////////////////////
//setting up the ADC
void ADC_INIT(void){
  ADMUX|=(1<<REFS0)|(1<<MUX1)|(1<<MUX0);
  ADCSRA|=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
}
uint16_t ADC_READ(uint8_t source){
  ADMUX=(ADMUX&0b11110000)|(source&0b00001111);
  ADCSRA|=(1<<ADSC);
  while(ADCSRA&(1<<ADSC));
  return ADC;
}
///////////////////////////////////////////////////////////////
void setup() {
  DDRD|=(1<<PD7)|(1<<buzzer);
  USART_init(my_ubrr);
  ADC_INIT();
}

void loop() {
   if (UCSR0A & (1 << RXC0)) { 
    unsigned char data = UDR0;
    USART_TX(data);
    }
    uint16_t value_pot=ADC_READ(gas_A0);
    if(value_pot>100){
      PORTD|=(1<<PD7);
      PORTD|=(1<<buzzer);

      USART_strTransmit("hazarduos gas detected!\r\n");
    }
    else{
      PORTD&=~(1<<PD7);
      PORTD&=~(1<<buzzer);

  
      USART_strTransmit("everything is fine\r\n");
    }
}
