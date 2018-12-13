/*
 *	Range
 *	
 *	Kunpeng Zhang
 *	Copyright 2015.10.29 JungleMetal Software.
 */

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#ifndef __jma_sp_range_h
#define __jma_sp_range_h

///范围结构
typedef struct {
	///起始位置
	int location;
	///长度
	int length;
} JMA_SP_Range;

///创建范围结构
JMA_SP_Range makeSPRange(int loc, int len);
///返回最大位置
int maxRange(JMA_SP_Range range);

#endif
