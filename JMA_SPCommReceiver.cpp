#include "JMA_SPCommReceiver.h"

void JMA_SPCommReceiver::eventOnDataBeforeVerifyCRC()
{
    if (hasRespondEvent(onEventDataBeforeVerifyCRC))
        (*onEventDataBeforeVerifyCRC)(this);
}

/**
 * @brief 数据解析解析
 * @param dataLocation
 * @param dataLength
 */
void JMA_SPCommReceiver::eventOnEventDataParse(uint8_t dataLocation, uint8_t dataLength)
{
    if (hasRespondEvent(onEventDataParse))
        (*onEventDataParse)(this, &dataFrame, dataLocation, dataLength);
}

void JMA_SPCommReceiver::eventOnEventDataReceived()
{
    if (hasRespondEvent(onEventDataReceived))
        (*onEventDataReceived)(this);
}

void JMA_SPCommReceiver::eventOnEventDataFailed()
{
    if (hasRespondEvent(onEventDataFailed))
        (*onEventDataFailed)(this);
}


/**
 * @brief 解析数据区
 * @param dataRange
 * @return 
 */
bool JMA_SPCommReceiver::_parseData(JMA_SP_Range dataRange)
{
    eventOnEventDataParse(dataRange.location, dataRange.length);
}


void JMA_SPCommReceiver::initFrameBuffer()
{
    clearBuffer();
    dataFrame.appendByte(DATA_FRAME_HEADER_1); //0x02
    // dataFrame.appendByte(0x3C); 不用插入，会通过串口接收到
}

void JMA_SPCommReceiver::addByte(uint8_t byte)
{
    _receiveCount++;    //接收字符计数
    
    //接收到完整头标志 - 清空当前数据缓存，然后初始化一个新数据缓存区
    //0x3C and 0x02
    if (DATA_FRAME_HEADER_2 == byte && DATA_FRAME_HEADER_1 ==_lastByte){
        _beginFrame = true;
        _receiveCount = 2;
        initFrameBuffer();
        //NSLog(@">>> FRAME BEGIN >>>");
    }

    //记录数据帧长度
    if (3 == _receiveCount) _frameLen = byte;

    //记录字节数据
    dataFrame.appendByte(byte);
    
    if (_receiveCount-3 == _frameLen){
        //数据帧CRC校验前
        eventOnDataBeforeVerifyCRC();
        
        //数据帧接收完毕，检测数据帧，如果正确马上进行解析。之后清空
        switch (checkDataFrames(true)) {
            case DF_CHECK_OK:
                //传递数据成功接收并且解析完毕消息
                eventOnEventDataReceived();
                break;
                
            //数据帧错误，通常丢弃
            default:
                //数据帧接收错误消息
                eventOnEventDataFailed();
                break;
        }
        
        //清空数据帧，等待接收新的数据
        _receiveCount = 0;
        _beginFrame = false;
        _lastByte = 0x00;
        _frameLen = 0x00;
        clearBuffer();

    }
    
    _lastByte = byte;

    //数据帧长度不能超过 256字节，超过就自动清空
    if (_receiveCount > dataFrame.maxLength()) {
        //清空数据帧，等待接收新的数据
        _receiveCount = 0;
        _beginFrame = false;
        _lastByte = 0x00;
        _frameLen = 0x00;
        clearBuffer();
    }
}
