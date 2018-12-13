//
//  lbcrc8.c
//  Simulator LBC100
//
//  Created by 张鲲鹏 on 2014-2-10.
//  Copyright (c) 2014年 JungleMetal Inc. All rights reserved.
//
//	Kunpeng Zhang
//	2015.10.28 modified for Arduino
//

// #include <stdio.h>
#include "JMACRC8.h"

///计算1Byte CRC8（字符，前一字符计算出的 CRC）
unsigned char crc8FromByte(unsigned char in, unsigned char prev_crc) {
	unsigned char i, crc;
	crc = prev_crc;
	for(i = 0; i < 8; i++)
	{
		if(((in & 0x01) ^ (crc & 0x01)) == 0)
		{
			crc >>= 1;
		} /* 做(1),(2); (1)=0,则CRC向高位移1位. */
		else
		{
			crc = crc ^ 0x18;	/* (1)=1,则异或18 */
			crc >>= 1;
			crc |= 0x80;	/* 置CRC.0为1 */
		}
		in >>= 1;
	}
	return crc;
}

///计算指定数据的 CRC8（字符串，字符串长度）
unsigned char crc8FromBytes(unsigned char *in, unsigned char len) {
    unsigned char CRC=0x00;
    for (int i=0; i<len; i++) {
        CRC = crc8FromByte(in[i], CRC);
    }
    
    return CRC;
}

///计算指定数据的 CRC8（字符串，起始位置，字符串长度）
unsigned char crc8FromBytes(unsigned char *in, unsigned char loc, unsigned char len)
{
    unsigned char CRC=0x00;
    for (int i=loc; i<len+loc; i++) {
        CRC = crc8FromByte(in[i], CRC);
        // Serial.println(in[i], HEX);
    }

    return CRC;
}

///翻转字节顺序 (8-bit)
unsigned char reverse8( unsigned char c )
{
    c = ( c & 0x55 ) << 1 | ( c & 0xAA ) >> 1;
    c = ( c & 0x33 ) << 2 | ( c & 0xCC ) >> 2;
    c = ( c & 0x0F ) << 4 | ( c & 0xF0 ) >> 4;
    return c;
}


///翻转字节顺序 (16-bit)
unsigned short reverseBytes16(unsigned short value)
{
    return (unsigned short)((value & 0xFF) << 8 | (value & 0xFF00) >> 8);
}

///翻转字节顺序 (32-bit)
unsigned long reverseBytes32(unsigned long value)
{
    return (value & 0x000000FFU) << 24 | (value & 0x0000FF00U) << 8 |
    (value & 0x00FF0000U) >> 8 | (value & 0xFF000000U) >> 24;
}

///翻转字节顺序 (64-bit)
unsigned long long reverseBytes64(unsigned long long value)
{
    return (value & 0x00000000000000FFUL) << 56 | (value & 0x000000000000FF00UL) << 40 |
    (value & 0x0000000000FF0000UL) << 24 | (value & 0x00000000FF000000UL) << 8 |
    (value & 0x000000FF00000000UL) >> 8 | (value & 0x0000FF0000000000UL) >> 24 |
    (value & 0x00FF000000000000UL) >> 40 | (value & 0xFF00000000000000UL) >> 56;
}

