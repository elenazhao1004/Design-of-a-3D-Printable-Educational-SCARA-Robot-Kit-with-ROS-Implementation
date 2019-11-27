const byte interruptPinA = 2;
const byte interruptPinB = 3;
volatile long EncoderCount = 0;
const int PWM = 250;
const byte DirPin1 = 7;
const byte DirPin2 = 8;
const byte PWMPin = 6;

float Theta, RPM;
float Theta_prev = 0;
unsigned long t;
unsigned long t_prev = 0;
int dt;
int dt_desired = 20;
float CountPerRev = 3286;

void setup()
{
  Serial.begin(9600);


  pinMode(interruptPinA, INPUT_PULLUP);
  pinMode(interruptPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPinA), ISR_EncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPinB), ISR_EncoderB, CHANGE);
}

void loop()
{
  Serial.print("Encoder Count: ");
  Serial.println(EncoderCount);

  t = millis();


  Theta = (EncoderCount / CountPerRev);
  dt = (t - t_prev);               // time step in milliseconds
  RPM = (Theta - Theta_prev) / (dt / 1000.0) * 60; // Velocity in rev/minute
  t_prev = t;
  Theta_prev = Theta;

  Serial.print("Angle: ");
  Serial.println(Theta);
  Serial.print("RPM: ");
  Serial.println(RPM);
  delay(dt_desired - (t - millis()));

  delay(1000);



  analogWrite(PWMPin, PWM);
  Serial.print("Set as Clockwise!");
  delay(200);
  digitalWrite(DirPin1, HIGH);
  digitalWrite(DirPin2, LOW);


}

/************************************************************************************/
void ISR_EncoderA() {

  bool PinB = digitalRead(interruptPinB);
  bool PinA = digitalRead(interruptPinA);
  if (PinB == LOW) {
    if (PinA == HIGH) {
      EncoderCount++;
    }
    else {
      EncoderCount--;
    }
  }
  else {
    if (PinA == HIGH) {
      EncoderCount--;
    }
    else {
      EncoderCount++;
    }
  }
}
/************************************************************************************/

void ISR_EncoderB() {
  bool PinA = digitalRead(interruptPinA);
  bool PinB = digitalRead(interruptPinB);
  if (PinA == LOW) {
    if (PinB == HIGH) {
      EncoderCount--;
    }
    else {
      EncoderCount++;
    }
  }
  else {
    if (PinB == HIGH) {
      EncoderCount++;
    }
    else {
      EncoderCount--;
    }
  }
} 

/************************************************************************************/
