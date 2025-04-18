const byte pin1=PC1;
const byte pin2=PC2;
const byte pin3=PD2;
uint8_t Rx;
uint8_t Ry;
uint8_t pRx = 0;
uint8_t pRy = 0;
ISR(TIMER1_COMPA_vect)
{
  OCR1A += 25000; // Advance The COMPA Register
  Rx = analogRead(pin1);
  Ry = analogRead(pin2);
  if(Rx != pRx || Ry != pRy)
  {
    Serial.print(Rx);
    Serial.print("  ");
    Serial.println(Ry);
    pRx = Rx;
    pRy = Ry;
  }
}
 
void setup()
{
  Serial.begin(9600);
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  pinMode(pin3,INPUT);
  TCCR1A = 0;           // Init Timer1
  TCCR1B = 0;           // Init Timer1
  TCCR1B |= B00000011;  // Prescalar = 64
  OCR1A = 25000;        // Timer CompareA Register
  TIMSK1 |= B00000010;  // Enable Timer COMPA Interrupt

}

void loop() {
  // put your main code here, to run repeatedly:

}
