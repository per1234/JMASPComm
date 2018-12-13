#include <JMAFoundation.h>
#include <JMA_SPCommReceiver.h>
JMA_SPCommReceiver myComReceiver;

//正确的数据帧
uint8_t cmd0xB0[] =
{
  0x02 , 0x3C , 0x14 , 0x10 , 0x10 , 0xB0 , 0x0F, 0xEA,
  0x00 , 0x00 , 0x00 , 0x6D , 0x27 , 0x00 , 0x00, 0xE8,
  0x03 , 0x00 , 0x00 , 0x14 , 0x00 , 0x50 , 0xD3
};

uint8_t error_cmd0xB0_crc[] =
{
  0x02 , 0x3C , 0x14 , 0x10 , 0x10 , 0xB0 , 0x0F , 0xEA,
  0x00 , 0x00 , 0x00 , 0x6D , 0x27 , 0x00 , 0x00 , 0xE8,
  0x03 , 0x00 , 0x00 , 0x14 , 0x00 , 0x50 , 0x3D
};

int led = 13;

void setup() {
  Serial.begin(9600);


  // put your setup code here, to run once:
  pinMode(led, OUTPUT);

  myComReceiver.onEventDataBeforeVerifyCRC = onEventDataBeforeCRC;
  myComReceiver.onEventDataParse = onEventDataParse2;
  myComReceiver.onEventDataReceived = onEventDataOK;
  myComReceiver.onEventDataFailed = onEventDataFailed;

  myComReceiver.begin(64);

  simulatorInput(cmd0xB0, 23);

  printBuffer(myComReceiver.dataFrame.buffer, myComReceiver.dataFrame.length());
  printBufferInfo();


}

void loop() {

  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    uint8_t incomingByte = Serial.read();
    myComReceiver.addByte(incomingByte);

    // // // say what you got:
    // Serial.print("I received: ");
    // Serial.println(incomingByte, HEX);

    // printBuffer(myComReceiver.dataFrame.buffer, myComReceiver.dataFrame.length());
    // // 函数测试
    // printBufferInfo();

  } else {
    // put your main code here, to run repeatedly:
    digitalWrite(led, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(200);               // wait for a second
    digitalWrite(led, LOW);   // turn the LED off by making the voltage LOW
    delay(200);               // wait for a second
  }
}

///模拟输入接收的数据
void simulatorInput(unsigned char *buffer, uint8_t length)
{
  for (uint8_t i = 0; i < length; i++) {
    myComReceiver.addByte(buffer[i]);
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
  Serial.println(myComReceiver.dataFrame.length(), DEC);

  int frameLen = myComReceiver._getFrameLength();
  JMA_SP_Range crcRange = myComReceiver._getCRCRange(frameLen);
  Serial.print("Frame length: ");
  Serial.println(frameLen, DEC);
  Serial.print("CRC: ");
  Serial.print(crcRange.location, DEC);
  Serial.print(" len:");
  Serial.println(crcRange.length, DEC);


  uint8_t isFrameOK = myComReceiver.checkDataFrames(true);
  if (DF_CHECK_OK == isFrameOK) {
    Serial.println("Frame Data OK.");
  } else {
    Serial.print("Frame Data ERROR. ERROR CODE:");
    Serial.println(isFrameOK, DEC);
  }
}

void onEventDataBeforeCRC(void *sender)
{
  Serial.println("Data before");

  printBuffer(myComReceiver.dataFrame.buffer, myComReceiver.dataFrame.length());
  printBufferInfo();
}

void onEventDataParse2(void *sender, void *buffer, uint8_t locaton, uint8_t length)
{
  JMA_SPBuffer *myBuffer = (JMA_SPBuffer *)buffer;
  uint8_t cmdID, cmdParamLength;
  myBuffer->getBytes(&cmdID, locaton, 1);
  myBuffer->getBytes(&cmdParamLength, locaton + 1, 1);


  Serial.println("------ JMACOMMReceiver -----------");
  Serial.print("Command: ");
  Serial.print(cmdID, HEX);
  Serial.print(" | ");
  Serial.println(cmdParamLength);
}

void onEventDataOK(void *sender)
{
  Serial.println("Data is OK");
}

void onEventDataFailed(void *sender)
{
  Serial.println("Data is ERROR");
}