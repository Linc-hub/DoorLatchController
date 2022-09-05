#include <Servo.h>
Servo myservo;

int OPEN_POSITION = 0;
int CLOSED_POSITION = 100;
int SERVO_PIN = 2;
int BUTTON_PIN = 7;
int LED_PIN = 13;

int currentButtonState;
int lastButtonState;

void setup() 
{
  myservo.attach(SERVO_PIN);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  currentButtonState = digitalRead(BUTTON_PIN);
  
  if (currentButtonState != lastButtonState) 
  {
    if (currentButtonState == LOW) 
    {
      myservo.write(OPEN_POSITION);
      digitalWrite(LED_PIN, LOW);
      Serial.println("digitalWrite(LOW)");
    }

    if (currentButtonState == HIGH) 
    {
      myservo.write(CLOSED_POSITION);
      digitalWrite(LED_PIN, HIGH);
      Serial.println("digitalWrite(HIGH)");
    }

    lastButtonState = currentButtonState;
  }
}