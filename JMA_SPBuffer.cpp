
#include "JMA_SPBuffer.h"

JMA_SPBuffer::JMA_SPBuffer()
{
	buffer = 0x00;
}

///分配缓存空间
void JMA_SPBuffer::begin(uint8_t bufferLength)
{
	_bufferLength = bufferLength;
	buffer = (uint8_t *)malloc(_bufferLength);
	clearBuffer();
}

///释放缓存空间
void JMA_SPBuffer::closeBuffer()
{
	free(buffer);
	_curPos = 0;
}


int JMA_SPBuffer::length()
{
	return _curPos;
}

int JMA_SPBuffer::maxLength()
{
	return _bufferLength;
}

void JMA_SPBuffer::clearBuffer()
{
	memset(buffer, 0x00, _bufferLength);
	_curPos = 0;
}

void JMA_SPBuffer::appendByte(uint8_t aByte)
{
	if (_curPos < _bufferLength) {
		buffer[_curPos] = aByte;
		_curPos++;
	}
}

void JMA_SPBuffer::appendBytes(const void *bytes, uint8_t length)
{
	unsigned char *in = (unsigned char *)bytes;
	for (uint8_t i=0; i<length; i++){
		appendByte(in[i]);
	}
}

///替换指定范围内的数据
void JMA_SPBuffer::replaceBytes(uint8_t loccation, uint8_t length, const void *bytes)
{
	unsigned char *in = (unsigned char *)bytes;
	for (uint8_t i=0; i<length; i++){
		buffer[i+loccation] = in[i];
	}
}

///读取指定范围的数据
void JMA_SPBuffer::getBytes(void *aBuffer, uint8_t location, uint8_t length)
{
	if (location < _bufferLength && location+length < _bufferLength) {
		uint8_t *r = (uint8_t *)malloc(length);
		for(uint8_t i=0; i<length; i++){
			r[i] = buffer[i+location];
		}
		memcpy(aBuffer, r, length);
		free(r);
	}
}
