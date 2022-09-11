#include <avdweb_Switch.h>
#include <IRremote.h>
#include <Servo.h>
Servo myservo;

int OPEN_POSITION = 0;
int CLOSED_POSITION = 100;
int SERVO_PIN = 2;
int BUTTON_PIN = 7;
int LED_PIN = 13;
int IR_PIN = 12;
int IR_OPEN_CODE = 16;
int IR_CLOSED_CODE = 18;

int currentButtonState;
int lastButtonState;
int lastLatchPosition = OPEN_POSITION;

Switch pushButton = Switch(BUTTON_PIN);

IRrecv irrecv(IR_PIN);
IRData results;

void setup()
{
  myservo.attach(SERVO_PIN);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(IR_PIN, INPUT);
  irrecv.enableIRIn();
  Serial.begin(9600);
}

void openLatch()
{
  myservo.write(OPEN_POSITION);
  digitalWrite(LED_PIN, LOW);
  Serial.println("Open Latch");
  delay(1000);
}

void closeLatch()
{
  myservo.write(CLOSED_POSITION);
  digitalWrite(LED_PIN, HIGH);
  Serial.println("Close Latch");
  delay(1000);
}

void loop()
{
  boolean hasReceivedData = irrecv.decode();
  currentButtonState = digitalRead(BUTTON_PIN);

  pushButton.poll();

  //  if (currentButtonState == HIGH)
  //  {
  //    Serial.println("Button Pressed!");

  if (pushButton.pushed())
  {
    Serial.println("Button Pressed!");
    int newLatchPosition;

    if (lastLatchPosition == OPEN_POSITION)
    {
      newLatchPosition = CLOSED_POSITION;
      closeLatch();
    }
    else
    {
      newLatchPosition = OPEN_POSITION;
      openLatch();
    }

    myservo.write(newLatchPosition);

    lastLatchPosition = newLatchPosition;
  }

  else if (hasReceivedData)
  {
    irrecv.resume();
    results = irrecv.decodedIRData;

    if (results.command == IR_OPEN_CODE)
    {
      openLatch();
    }
    else if (results.command == IR_CLOSED_CODE)
    {
      closeLatch();
    }
  }
}
