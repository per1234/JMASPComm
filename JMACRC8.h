//
//  lbcrc8.h
//  lbcom
//
//  Created by 张鲲鹏 on 14-2-3.
//  Copyright (c) 2014年 JungleMetal Software. All rights reserved.
//
//	Kunpeng Zhang
//	2015.10.28 modified for Arduino
//

// #if ARDUINO >= 100
//   #include "Arduino.h"
// #else
//   #include "WProgram.h"
// #endif

#ifndef __jma_sp_crc8_h
#define __jma_sp_crc8_h

///计算1Byte CRC8（字符，前一字符计算出的 CRC）
unsigned char crc8FromByte(unsigned char in, unsigned char prev_crc);

///计算指定数据的 CRC8（字符串，字符串长度）
unsigned char crc8FromBytes(unsigned char *in, unsigned char len);
///计算指定数据的 CRC8（字符串，起始位置，字符串长度）
unsigned char crc8FromBytes(unsigned char *in, unsigned char loc, unsigned char len);


///翻转字节顺序 (8-bit)
unsigned char reverse8( unsigned char c );

///翻转字节顺序 (16-bit)
unsigned short reverseBytes16(unsigned short value);

///翻转字节顺序 (32-bit)
unsigned long reverseBytes32(unsigned long value);
///翻转字节顺序 (64-bit)
unsigned long long reverseBytes64(unsigned long long value);

#endif