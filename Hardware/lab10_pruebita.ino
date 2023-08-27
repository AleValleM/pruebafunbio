//maestro!!

//sotelo
//espinoza
//valle

#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include <Wire.h>
int opcion;
String palabra()= string; //vacio para poner palabra tipo string para unirla

void setup() {
  USART_INIT(MYUBRR);

  Wire.begin() ;//este es el maestro
  Serial.begin(9600);//velocidad de comunicacion e inicia comu serial
}

void loop() {   
  char b;
  int i=0;
  byte coso;

  //inicamos la transmicion
  Wire.beginTransmission(1);

  if(i<3){
    coso=USART_Receive();
    USART_send(coso);
    palabra(i)=coso;
    i++;
  }

  b=palabra.concat();//concatenamos la palabra
  if(b=="pwm"){
    //ingresa la palabra
    opcion=0;
    Wire.write(opcion);
    //Paramos la transmision
    Wire.endTransmission(); 
  }
  if(b=="adc"){
    opcion=1;
    Wire.write(opcion);
    //Paramos la transmision
    Wire.endTransmission();
  }
  else{
    //nada hace
  }
}

void USART_INIT(unsigned int ubrr){
  //ubrr a UBRR0H y UBRR0L
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  //Se configura 1 bit de parada y 8 bits de data
  UCSR0C|= (1<<UCSZ01)|(1<<UCSZ00);
  //Habilitar receptor y transmisor
  UCSR0B |= ((1<<RXEN0)|(1<<TXEN0));
}

void USART_send(unsigned char data)
{
  //loop nulo si el buffer de transmision no esta vacio
  while(!(UCSR0A&(1<<UDRE0)));
  //si el buffer esta vacio
  UDR0=data;
}

unsigned char USART_Receive(void)
{
  while(!(UCSR0A&(1<<RXC0)));
  //recibe la data recibida al registro UDR0
  return UDR0;
}

