#include <VirtualWire.h>
const byte pin1=PC1;
const byte pin2=PC2;
const byte pin3=PD2;
const byte pin4=PD4;
int16_t Rx;
int16_t Ry;
int16_t calibRx = 0;
int16_t calibRy = 0;
int16_t switch_bounceOC = 0;
int16_t switch_bounce = 0;
uint8_t xsign;
uint8_t xyign;

ISR(TIMER1_COMPB_vect)
{
  OCR1B += 25000; // Advance The COMPA Register
  Rx = analogRead(pin1) - calibRx;
  Ry = analogRead(pin2) - calibRy;
  Serial.print(Rx);
  Serial.print("  ");
  Serial.println(Ry);
  uint8_t data[3] = {69,21,37};
  uint8_t *senddata = data;
  vw_send(senddata,3);
  if(switch_bounce == 65635)
  {
    switch_bounce = 0;
    switch_bounceOC = 0;
  }
  else switch_bounce++;
}

void setup()
{
  vw_setup(4000);// speed of data transfer in bps, can max out at 10000
  Serial.begin(9600);
  Serial.println("dupa");
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  TCCR1B = 0;           // Init Timer1
  TCCR1B |= B00000011;  // Prescalar = 64
  OCR1B = 25000;        // Timer CompareB Register
  TIMSK1 |= B00000100;  // Enable Timer COMPA Interrupt
  pinMode(pin3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin3), SW, FALLING);
  calibRx = analogRead(pin1);
  calibRy = analogRead(pin2);
  vw_set_tx_pin(pin4); 
  
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
}
void SW()
{
  if(switch_bounceOC + 10 < switch_bounce)
  {
    switch_bounceOC = switch_bounce;
    Serial.println("change breaking");
  }
}
