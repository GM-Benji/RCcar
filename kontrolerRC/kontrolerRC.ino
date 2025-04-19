const byte pin1=PC1;
const byte pin2=PC2;
const byte pin3=PD2;
int16_t Rx;
int16_t Ry;
int16_t calibRx = 0;
int16_t calibRy = 0;
int16_t switch_bounceOC = 0;
int16_t switch_bounce = 0;
ISR(TIMER1_COMPA_vect)
{
  OCR1A += 25000; // Advance The COMPA Register
  Rx = analogRead(pin1) - calibRx;
  Ry = analogRead(pin2) - calibRy;
  Serial.print(Rx);
  Serial.print("  ");
  Serial.println(Ry);
  
  if(switch_bounce == 65635)
  {
    switch_bounce = 0;
    switch_bounceOC = 0;
  }
  else switch_bounce++;
}

void setup()
{
  Serial.begin(9600);
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  TCCR1A = 0;           // Init Timer1
  TCCR1B = 0;           // Init Timer1
  TCCR1B |= B00000011;  // Prescalar = 64
  OCR1A = 25000;        // Timer CompareA Register
  OCR1A = 25000;        // Timer CompareB Register
  TIMSK1 |= B00000010;  // Enable Timer COMPA Interrupt
  pinMode(pin3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin3), SW, FALLING);
  calibRx = analogRead(pin1);
  calibRy = analogRead(pin2);
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
