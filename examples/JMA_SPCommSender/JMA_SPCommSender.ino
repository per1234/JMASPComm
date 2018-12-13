#include <JMAFoundation.h>
#include <JMA_SPCommSender.h>
JMA_SPCommSender myCommSender;

//正确的数据帧
uint8_t cmd0xB0[] = 
{
	0x02 ,0x3C ,0x14 ,0x10 ,0x10 ,0xB0 ,0x0F,0xEA,
	0x00 ,0x00 ,0x00 ,0x6D ,0x27 ,0x00 ,0x00,0xE8,
	0x03 ,0x00 ,0x00 ,0x14 ,0x00 ,0x50 ,0xD3
};

uint8_t error_cmd0xB0_crc[] = 
{
	0x02 ,0x3C ,0x14 ,0x10 ,0x10 ,0xB0 ,0x0F ,0xEA,
	0x00 ,0x00 ,0x00 ,0x6D ,0x27 ,0x00 ,0x00 ,0xE8,
	0x03 ,0x00 ,0x00 ,0x14 ,0x00 ,0x50 ,0x3D
};

int led = 13;

void setup() {
	Serial.begin(9600);


  // put your setup code here, to run once:
  pinMode(led, OUTPUT);

	myCommSender.begin(64);
	myCommSender.onEventFrameDataAlready = onEventSendFrameDataAlready2;

	// for(uint8_t i =0; i<sizeof(cmd0xB0); i++) {
	// 	myComReceiver.addByte(cmd0xB0[i]);
	// }

	// myCommSender.cmd_0x01_hardware_version();
	printBuffer(myCommSender.dataFrame.buffer, myCommSender.dataFrame.length());
	printBufferInfo();


}

void loop() {

	// myComReceiver.clearBuffer();
	simulatorInput(cmd0xB0, 23);
	printBuffer(myCommSender.dataFrame.buffer, myCommSender.dataFrame.length());
	printBufferInfo();

	delay(1000);
}

///模拟输入接收的数据
void simulatorInput(unsigned char *buffer, uint8_t length)
{
	for(uint8_t i =0; i<length; i++) {
		myCommSender.addBuffer(buffer[i]);
	}
}

void printBuffer(void *buffer, int length)
{
	Serial.println("\n---------| BUFFER |---------");
	for (byte i=0; i<length; i++){

		if ((i % 16) == 0) {
			Serial.println("");
		} else
			if ((i % 8) == 0 && i>0) {
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
	Serial.println(myCommSender.dataFrame.length(), DEC);

	int frameLen = myCommSender._getFrameLength();
	JMA_SP_Range crcRange = myCommSender._getCRCRange(frameLen);
	Serial.print("Frame length: ");
	Serial.println(frameLen, DEC);
	Serial.print("CRC: ");
	Serial.print(crcRange.location, DEC);
	Serial.print(" len:");
	Serial.println(crcRange.length, DEC);


	uint8_t isFrameOK = myCommSender.checkDataFrames(true);
	if (DF_CHECK_OK == isFrameOK) {
		Serial.println("Frame Data OK.");
	} else {
		Serial.print("Frame Data ERROR. ERROR CODE:");
		Serial.println(isFrameOK, DEC);
	}
}

void onEventSendFrameDataAlready2(void *sender)
{
	printBuffer(myCommSender.dataFrame.buffer, myCommSender.dataFrame.length());
	printBufferInfo();
}
