#include <Servo.h>

int m1a = 6;
int m1b = 11;
#define ECHOPIN 8
#define TRIGPIN 7
#define ECHOPIN1 2
#define TRIGPIN1 3
#define ECHOPIN2 12
#define TRIGPIN2 9
#define servo_pin 10
#define pos 90

int middleDistance, leftDistance, rightDistance, calcDistance, duration, calcDistance1, duration1,calcDistance2,duration2;
char val;
Servo steering;
Servo myservo;
int checkDistance() 
{
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  calcDistance = (duration * 0.0343) / 2;
  delay(100);
  return calcDistance;
}
int checkDistance1() 
{
  digitalWrite(TRIGPIN1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN1, LOW);
  duration1 = pulseIn(ECHOPIN1, HIGH);
  calcDistance1 = (duration1 * 0.0343) / 2;
  delay(100);
  return calcDistance1;
}
int checkDistance2() 
{
  digitalWrite(TRIGPIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN2, LOW);
  duration2 = pulseIn(ECHOPIN2, HIGH);
  calcDistance2 = (duration2 * 0.0343) / 2;
  delay(100);
  return calcDistance2;
}
void forward() {
      analogWrite(m1a, 75);
      digitalWrite(m1b, LOW);
      steering.write(pos);
}
void backward(){
      digitalWrite(m1a, LOW);
      analogWrite(m1b, 75);
      steering.write(pos);
  }
 void left(){
      steering.write(179);
      analogWrite(m1a, 90);
      digitalWrite(m1b, LOW);
  }
  void right(){
      steering.write(0);
      analogWrite(m1a, 90);
      digitalWrite(m1b, LOW);
    }
 void Stop(){
      analogWrite(m1a, 0);
      digitalWrite(m1b, LOW);
      steering.write(pos);
      
}
 void bluetooth() 
 {
  Serial.println("bluetooth mode");
  while (true) {
    while (Serial.available() > 0) {
       val = Serial.read();
      Serial.println(val);
    }
    if (val == 'F' ) {
      forward();
    }
    else if (val == 'B') {
      backward();

    }
    else if (val == 'L') {
      left();

    }
    else if (val == 'R') {
      right();

    }
    else if (val == 'S') {
      Stop();
    }
    else if (val == 'X') {
      Stop();
    }
     else if(val == 'J') //Backward Right
    {
      steering.write(0);
       digitalWrite(m1a, LOW);
      analogWrite(m1b, 80);
      
 }
   else if(val == 'G') //Forward Left
    {
      steering.write(0);
      analogWrite(m1a, 80);
      digitalWrite(m1b, LOW);
    }
  else if(val == 'H') //Backward Left
    {
      steering.write(180);
      analogWrite(m1b, 80);
      digitalWrite(m1a, LOW);
    }

    else if (val == 'x') {
      return;
    }
  }

}
void setup()
{ 
    pinMode(TRIGPIN, OUTPUT);
    pinMode(ECHOPIN, INPUT);
    pinMode(TRIGPIN1, OUTPUT);
    pinMode(ECHOPIN1, INPUT);
    pinMode(TRIGPIN2, OUTPUT);
    pinMode(ECHOPIN2, INPUT);
    pinMode(m1a, OUTPUT);  // Digital pin 10 set as output Pin
    pinMode(m1b, OUTPUT);  // Digital pin 11 set as output Pin
    Serial.begin(9600);
    steering.attach(servo_pin);
    steering.write(pos);
//    myservo.attach(9);
//    myservo.write(100);
    
}

void loop()
{
  while (Serial.available() > 0) {
     val = Serial.read();
    Serial.println(val);
    
    if (val == 'X') {
      bluetooth();
    }

  }
  myservo.write(100);  //setservo position according to scaled value
  delay(200);
  middleDistance = checkDistance();
  Serial.print("middle: ");
  Serial.println(middleDistance);

  if (middleDistance <= 50) {
    Stop();
    delay(200);
    backward();
    delay(1500);
    Stop();
    delay(10);
//    myservo.write(10);
    rightDistance = checkDistance2();
    delay(1000);
    Serial.print("right: ");
    Serial.println(rightDistance);
//    myservo.write(100);
    delay(1000);
//    myservo.write(170);
    
    leftDistance = checkDistance1();
    
    delay(500);
    Serial.print("left: ");
    Serial.println(leftDistance);

    myservo.write(100);
    delay(1000);
    if (rightDistance > leftDistance) {
      right();
      delay(3000);
      
        }
    else if (rightDistance < leftDistance) {
      left();
      delay(3000);
       
    }
    else if ((rightDistance <= 50) && (leftDistance <= 50)) {
      backward();
      delay(2000);
     
    }
    else {
      forward();
    }
  }
  else {
    forward();
 }
}

 
