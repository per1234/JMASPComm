/**
   JMASPComm base example

*/

#include <JMAFoundation.h>
#include <JMA_SPComm.h>
JMA_SPComm myComm;


// Correct data frame 正确的数据帧
uint8_t cmd0xB0[] =
{
  0x02 , 0x3C , 0x14 , 0x10 , 0x10 , 0xB0 , 0x0F , 0xEA ,
  0x00 , 0x00 , 0x00 , 0x6D , 0x27 , 0x00 , 0x00 , 0xE8 ,
  0x03 , 0x00 , 0x00 , 0x14 , 0x00 , 0x50 , 0xD3
};

int led = 13;

void setup() {
  Serial.begin(9600);


  // put your setup code here, to run once:
  pinMode(led, OUTPUT);

  myComm.begin(32);
  myComm.addBuffer(&cmd0xB0, sizeof(cmd0xB0));
  printBuffer(myComm.dataFrame.buffer, myComm.dataFrame.length());
  printBufferInfo();
}

void loop() {

  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    byte incomingByte = Serial.read();
    myComm.addBuffer(incomingByte);

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);

    printBuffer(myComm.dataFrame.buffer, myComm.dataFrame.length());

    // 函数测试
    printBufferInfo();


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
  Serial.println("\n---------| BUFFER |---------");
  for (byte i = 0; i < length; i++) {

    if ((i % 16) == 0) {
      Serial.println("");
    } else if ((i % 8) == 0 && i > 0) {
      Serial.print("--\t");
    }

    Serial.print(((byte *)buffer)[i], HEX);
    Serial.print("\t");

  }

  Serial.println("\n----------------------------\n");
}

void printBufferInfo()
{
  // 函数测试
  Serial.print("buffer length: ");
  Serial.println(myComm.dataFrame.length(), DEC);

  int frameLen = myComm._getFrameLength();
  JMA_SP_Range crcRange = myComm._getCRCRange(frameLen);
  Serial.print("Frame length: ");
  Serial.println(frameLen, DEC);
  Serial.print("CRC: ");
  Serial.print(crcRange.location, DEC);
  Serial.print(" len:");
  Serial.println(crcRange.length, DEC);


  uint8_t isFrameOK = myComm.checkDataFrames(true);
  if (DF_CHECK_OK == isFrameOK) {
    Serial.println("Frame Data OK.");
  } else {
    Serial.print("Frame Data ERROR. ERROR CODE:");
    Serial.println(isFrameOK, DEC);
  }
}