#include <RCSwitch.h>
const byte pin1=PC1;
const byte pin2=PC2;
const byte pin3=PD2;
const byte pin4=PD4;
uint16_t Rx;
uint16_t Ry;
int16_t calibRx = 0;
int16_t calibRy = 0;
uint16_t switch_bounceOC = 0;
uint16_t switch_bounce = 0;
uint8_t sndX;
uint8_t sndY;
uint8_t xsign;
uint8_t ysign;
uint16_t sdata;
RCSwitch mySwitch = RCSwitch();
void setup()
{
  mySwitch.enableTransmit(pin4);
  Serial.begin(9600);
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  //TCCR1A = 0;           // Init Timer1
  TCCR2A = 0;           // Init Timer1
  TCCR2A |= B00000100;  // Prescalar = 64
  //OCR1A = 25000;        // Timer CompareA Register
  OCR2A = 25000;        // Timer CompareB Register
  TIMSK2 |= B00000010;  // Enable Timer COMPA Interrupt
  pinMode(pin3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin3), SW, FALLING);
  //calibRx = analogRead(pin1);
  //calibRy = analogRead(pin2);
  
}
ISR(TIMER2_COMPA_vect)
{
  OCR2A += 25000; // Advance The COMPA Register
  Rx = analogRead(pin1);
  Ry = analogRead(pin2);
  // Serial.print(Rx);
  // Serial.print("  ");
   //Serial.println(Ry);
  if(Rx<65)Rx=65;
  mySwitch.send(Rx, 11);
  sdata = Ry | 10000000000;
  Serial.println(Rx);
  mySwitch.send(sdata, 11);
  if(switch_bounce == 65635)
  {
    switch_bounce = 0;
    switch_bounceOC = 0;
  }
  else switch_bounce++;
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