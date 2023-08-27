int cuenta=0;
int sw1, sw2, sw3;

void setup() {
  // put your setup code here, to run once:
  DDRD = 0xFF;// todos los bits son salida :)
  DDRB = 0x00;// PB0, PB1, PB2 son entradas
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTD = cuenta;    // la cuenta va a aparecer en ek led tons need salida!
  sw1 = PINB&0x01; //LO LEE DE FRENTE Y ENMASCARA
  if (sw1 == 0x01){
    sw1 = PINB&0x01; // LO SIGUE LEYENDO
    while(sw1 == 0x01)
      {sw1 = PINB&0x01;} // LO SIGUE LEYENDO HASTA QU EYA NO SEA PIN 0
    cuenta++;
    PORTD = cuenta;
  }
  sw2 = PINB&0x02;
  if (sw2 == 0x02){
    sw2 = PINB&0x02;
    while(sw2 == 0x02)
      {sw2 = PINB&0x02;}
    cuenta= cuenta*2;
    PORTD = cuenta;
  }

  sw3 = PINB&0b00000100;//0x04
  if (sw3 == 0x04){
    sw3 = PINB&0x04;
    while(sw3 == 0x04)
      {sw3 = PINB&0x04;}
    cuenta=0;
    PORTD = cuenta;
  }
  
 
}
