int  InputNum, Speed_value;
const byte PWMPin = 6;
const byte DirPin1 = 7;
const byte DirPin2 = 8;

const byte interruptPinA = 2;
const byte interruptPinB = 3;
volatile long EncoderCount = 0; //volatile global varaible to update variable

float theta, RPM;
float  theta_prev = 0;
float CountPerRev = 484; //input 12V will have to run at 600 RPM

unsigned long t;
int dt; //change of time
unsigned long t_prev = 0; //previous time
int dt_desired = 20;

int PWMvalue = 255;




void setup() {
  // put your setup code here, to run once:

  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(DirPin1, OUTPUT);
  pinMode(DirPin2, OUTPUT);

  // pinMode(interruptPinA, INPUT_PULLUP); //gets internnaly conencted to 5V using 50kohm, pins set to high state
  // pinMode(interruptPinB, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(interruptPinA), ISR_EncoderA, CHANGE); //ISR_EncoderA: whenever interruptPinA changes its status from low to High
  // attachInterrupt(digitalPinToInterrupt(interruptPinB), ISR_EncoderB, CHANGE);


}

void loop() {
  // put your main code here, to run repeatedly:
  int i = 1;
  //State-Machine

  switch (i)
  {
    case 1:
      Serial.println(i);
      i++;
    case 2:
      //set clockwise-direction
      Serial.println(i);
      digitalWrite(DirPin1, HIGH);
      digitalWrite(DirPin2, LOW);
      delay(2000);
      i++;
    case 3:
      //accelerate motor
      Serial.println(i);
      delay(2000);
      Accelerate(PWMvalue);
      i++;
    case 4:
      //maintain-speed ten seconds
      Serial.println(i);
      delay(10000);
      i++;
    case 5:
      //decelerate motor
      Serial.println(i);
      delay(1000);
      Decelerate(PWMvalue);
      i++;
    case 6:
      //set counterclockwise-direction
      Serial.println(i);
      delay(2000);
      digitalWrite(DirPin1, LOW);
      digitalWrite(DirPin2, HIGH);
      i++;
    case 7:
      //accelerate motor
      Serial.println(i);
      delay(2000);
      Accelerate(PWMvalue);
      i++;
    case 8:
      //decelerate motor
      Serial.println(i);
      delay(2000);
      Decelerate(PWMvalue);
    default:
      break;
  }


}


//Accelerate
void Accelerate(int PWMval)
{

  for (int i = 0; i <= PWMval; i++)
  {
    //Serial.print("PWM Value: ");
    //Serial.println(i);
    analogWrite(PWMPin, i);
    delay(10);

  }

  delay(10000);
}


void Decelerate(int PWMval)
{
  delay(2000);
  for (int i = PWMval; i >= 0; i--)
  {
    //Serial.print("PWM Value: ");
    //Serial.println(i);
    analogWrite(PWMPin, i);
    delay(20);
  }

}



