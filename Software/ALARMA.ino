#define cbi(sfr, bit) (_SFR_BYTE(sfr) &=~ (1<< bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= (1<< bit))

#include <avr/interrupt.h>


//Alessandra Valle
//gloria atencio

volatile int bandera=0; //variables valotailes porque entran al adc
byte valoradc_sig; //variable para leer el adc

void setup() {
Serial.begin(9600);

DDRD=0xF0; //ENTRADAS-->INTERUCPCONES INT 0  Y INT 1
// salidas ledS LSB-->LED1 MSB-->LED4

//adc:
cbi (ADCSRA , ADEN); //DESAHIBILIAMOS EL ENABLE
cbi (ADCSRA , ADLAR); //LIMPIAMOS EL ADC

//habilitamos y establemos EL ADC
sbi (ADMUX , REFS0); //ELIGEMOS VOLTAJE DE 5V

sbi (ADCSRA , ADLAR); //usamos el adch para mostrar la conversion, solo seran need 8 bit mas significativos para la lectura

sbi (ADCSRA , ADPS2);
sbi (ADCSRA , ADPS1);
sbi (ADCSRA , ADPS0); //DIVIDIMOS LA FREC ENTRE 128! es lo mas cercano a 1Hz

ADMUX &= (0xF0 << MUX0);  //ENMASCARAM y limpiamos EL CANAL
ADMUX |= (0<< MUX0); //(canal 0) para el potenciometro

sbi (ADCSRA , ADEN); //habilitamos el enable
_delay_us(100); //esperamos 100 um

sbi (ADCSRA , ADSC); //damos inicio al adc

//sbi (ADCSRA , ADIE); //habilitamos el INTRRR

//interrupciones:
EICRA=0;
EIMSK=0; //limpiando los registros 

EIMSK |= (1<<INT0) | (1<<INT1); //se van a utilizar los dos pines de int ext
EICRA |= (1<<ISC01) | (1<<ISC00) | (1<<ISC11); // interrupciones seran para int0 flanco de subida y para int1 flanco de bajada

sei(); //el que habilita las interrupciones
}

void loop() {
  if(bandera==1){ //si esque esta leyendo el estado del led1
    valoradc_sig=ADCH;
    cbi (ADCSRA , ADSC); //por si lo pongo
    cbi (ADCSRA , ADIF); // ponerlo manualmente cuando acaba la conversión
    Serial.print(valoradc_sig);
    bandera=0;
    if(valoradc_sig<1){
      PORTD&=~(1<<PORTD7);
      PORTD&=~(1<<PORTD6); //NO SE ENCIENDE NI LED 3 NI LED4
    }
    if(valoradc_sig<1 && valoradc_sig>4){
      PORTD|=(1<<PORTD6); // SE PRENDE SLO EL EL LED 3
    }
    else{
      PORTD|=(1<<PORTD7); 
      PORTD|=(1<<PORTD6); //SE ENCIENDE el lED y  LED4
    }
  }
}

ISR(INT0_vect){
  if(PIND&0x10){ // aqui estoy leyendo el estado donde esta el led1 y esta prendido
    PORTD|=0x00; // led se apaga
  }
  else{
    PORTD|=0x10; // led se prende
  }
  Serial.print("prendi");
  bandera=1;
}

ISR(INT1_vect){
   if(PIND&0x20){ // aqui estoy leyendo el estado donde esta el led2 y esta prendido
   PORTD|=0x00; //se apaga
  }
  else{
   PORTD|=0x20; //se prende
  }
  Serial.print("prendi");
}

