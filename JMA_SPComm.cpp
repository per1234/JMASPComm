#include "JMA_SPComm.h"

///打开缓存
void JMA_SPComm::begin(uint8_t bufferLength)
{
    dataFrame.begin(bufferLength);
}

///取得数据桢长度
uint8_t JMA_SPComm::_getFrameLength()
{
    JMA_SP_Range lenRange = makeSPRange(2,1);
    uint8_t length = 0;
    dataFrame.getBytes(&length, lenRange.location, lenRange.length);
    return length;
}

///取得CRC计算范围
JMA_SP_Range JMA_SPComm::_getCRCRange(uint8_t frameLength)
{
    //CRC位置 = 数据帧长 + 2（帧头）- 1
    return makeSPRange(frameLength+2-1, 1);
}


///检查数据帧是否正确(是否解析数据－如果数据帧正确才执行)，返回 YES 代表是正确数据帧，否则 数据帧错误
uint8_t JMA_SPComm::checkDataFrames(bool parseData)
{
    //如果数据帧总长度小于 7 字节说明数据帧不完整
    if (dataFrame.length() < DATA_FRAME_MIN_LENGTH) 
        return DF_CHECK_ERROR_FRAME_TOTAL_LENGTH;
    
    //检查数据帧头
    unsigned int header = 0x00;
    dataFrame.getBytes(&header, DATA_POS_HEADER, DATA_LEN_HEADER);
    
    if (header != DATA_FRAME_HEADER)
        if (reverseBytes16(header) != DATA_FRAME_HEADER) 
            return DF_CHECK_ERROR_FRAME_HEADER; //数据帧头不正确（帧需要翻转字节）
    
    //检查数据帧长度
    uint8_t frameLength;
    dataFrame.getBytes(&frameLength, DATA_POS_FRAME_LENGTH, DATA_LEN_FRAME_LENGTH);
    if (dataFrame.length() != frameLength+3) 
        return DF_CHECK_ERROR_DATA_LENGTH;   //数据帧长超过预定义长度
    
    //---------- CRC 校验 -----------------
    if (enabledCRC) {
        //读取数据帧中包含的CRC码
        uint8_t cCRC;
        dataFrame.getBytes(&cCRC, frameLength + DATA_LEN_HEADER, DATA_LEN_CRC);
        // dataFrame.getBytes(&cCRC, crcRange.location, crcRange.length);

        //计算出数据CRC码
        uint8_t dCRC=0x00;
        dCRC = crc8FromBytes(dataFrame.buffer, DATA_POS_FRAME_LENGTH, frameLength);

        //数据CRC校验错误
        if (cCRC != dCRC) return DF_CHECK_ERROR_CRC;

        dataCRC = cCRC;
    }
    
    //更新数据帧长度
	dataFramesLength = frameLength;
    //如果需要解析数据－交由子类完成
    if (parseData) {        
        //读取 Version
        dataFrame.getBytes(&comMainVer, DATA_POS_MAIN_VERSION, DATA_LEN_MAIN_VERSION);
        dataFrame.getBytes(&comDataVer, DATA_POS_DATA_VERSION, DATA_LEN_DATA_VERSION);

        //解析数据（子类完成数据解析）
        _parseData(makeSPRange(DATA_POS_DATA, frameLength-3));
    }

    return DF_CHECK_OK;
}

uint8_t JMA_SPComm::checkDataFramesAndParse()
{
    return checkDataFrames(true);
}

///解析数据-子类继成实现具体数据的解析
bool JMA_SPComm::_parseData(JMA_SP_Range dataRange)
{
    return true;
}

///清空数据缓存
void JMA_SPComm::clearBuffer()
{
    dataFrame.clearBuffer();
}

///增加缓存数据（单字节）
void JMA_SPComm::addBuffer(uint8_t byte)
{
    dataFrame.appendByte(byte);
}

///增加缓存数据
void JMA_SPComm::addBuffer(const void *buffer, uint8_t length)
{
    dataFrame.appendBytes(buffer, length);
}