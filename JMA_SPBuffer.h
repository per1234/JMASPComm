#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#ifndef __jma_sp_buffer_h
#define __jma_sp_buffer_h

/**
 * @class JMA_SPBuffer
 * @author Kunpeng Zhang
 * @brief 
 */
class JMA_SPBuffer
{
public:
	///初始化
	JMA_SPBuffer();

	///分配缓存空间
	void begin(byte bufferLength);
	///释放缓存空间
	void closeBuffer();
	///缓存长度
	int length();
	///缓存最大长度
	int maxLength();

	///清空缓存，同时复位游标
	void clearBuffer();
	///增加一字节数据到缓存
	void appendByte(uint8_t aByte);
	///增加指定长度的数据到缓存
	void appendBytes(const void *bytes, uint8_t length);
	///替换指定范围内的数据
  void replaceBytes(uint8_t loccation, uint8_t length, const void *bytes);

	///读取指定范围的数据
	void getBytes(void *aBuffer, uint8_t location, uint8_t length);

	///缓存
	uint8_t *buffer = 0x00;

private:
	uint8_t _bufferLength = 0;
	///当前指针
	uint8_t _curPos = 0;

};

#endif
