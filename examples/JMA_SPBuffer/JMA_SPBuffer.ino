#include <JMA_SPBuffer.h>

JMA_SPBuffer myBuffer;

int led = 13;

void setup() {
  myBuffer.begin(24);
  Serial.begin(9600);


  // put your setup code here, to run once:
  pinMode(led, OUTPUT);

  myBuffer.appendByte(53);
  myBuffer.appendByte(89);
  myBuffer.appendByte(55);
  myBuffer.appendByte(57);
  myBuffer.appendByte(54);
  myBuffer.appendByte(45);
  printBuffer(myBuffer.buffer, myBuffer.length());

  byte myString[3];
  myBuffer.getBytes(myString, 3, 3);

  Serial.print("myString = ");
  Serial.println((char *)myString);

  printBuffer(myString, sizeof(myString));

}

void loop() {

  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    byte incomingByte = Serial.read();

    myBuffer.appendByte(incomingByte);

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);

    printBuffer(myBuffer.buffer, myBuffer.length());

  } else {
    // put your main code here, to run repeatedly:
    digitalWrite(led, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(100);               // wait for a second
    digitalWrite(led, LOW);   // turn the LED off by making the voltage LOW
    delay(100);               // wait for a second
  }
}


void printBuffer(void *buffer, int length)
{
  for (byte i = 0; i < length; i++) {
    Serial.println(((byte *)buffer)[i], DEC);
  }

  Serial.println("-------------------------");
}