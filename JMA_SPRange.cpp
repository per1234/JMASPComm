/*
 *	Range
 *	
 *	Kunpeng Zhang
 *	Copyright 2015.10.29 JungleMetal Software.
 */

#include "JMA_SPRange.h"

///创建范围结构
JMA_SP_Range makeSPRange(int loc, int len)
{
    JMA_SP_Range r;
    r.location = loc;
    r.length = len;
    return r;
}

///返回最大位置
int maxRange(JMA_SP_Range range)
{
	return (range.location + range.length);
}
