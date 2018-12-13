#include "JMA_SPCommSender.h"

/**
 * @brief 
 * \~english Generate data send area preparation event
 * \~chinese 创建数据发送区准备事件
 */
void JMA_SPCommSender::eventOnFrameDataAlready()
{
    if (hasRespondEvent(onEventFrameDataAlready))
        onEventFrameDataAlready(this);
}

/**
 * @brief 
 * \~english Initialize the receive buffer
 * \~chinese 初始化数据帧
 */
void JMA_SPCommSender::initFrameBuffer()
{
    clearBuffer();
    dataFrame.appendByte(DATA_FRAME_HEADER_1);	//0x02
    dataFrame.appendByte(DATA_FRAME_HEADER_2);	//0x3C

    //初始化默认桢长
    dataFrame.appendByte(0x00);

    dataFrame.appendByte(comMainVer);
    dataFrame.appendByte(comDataVer);
}

/**
 * @brief 
 * \~english 
 * Calculate the CRC of the data frame. 
 * When the send buffer is ready, call this function to calculate the CRC of data.
 * 
 * \~chinese
 * 计算数据帧的 CRC 校验码。当发送缓存准备好以后调用计算数据的 CRC, 完成后即可发送
 * 
 * @return boolean
 */
uint8_t JMA_SPCommSender::calcCRCFromDataFrames()
{
    //计算数据帧长
    uint8_t fl = dataFrame.length() - DATA_LEN_HEADER;
    //写入数据帧长度
    dataFrame.replaceBytes(DATA_POS_FRAME_LENGTH, DATA_LEN_FRAME_LENGTH, &fl);

	if (enabledCRC == true) {
	  //------- 计算CRC --------------
	  //取得需要计算 CRC 校验码的数据区数据
	  //CRC 范围 = 数据帧长度 + 版本 + 数据区
	  //计算出数据CRC码
	  unsigned char dCRC=0x00;
	  dCRC = crc8FromBytes(dataFrame.buffer, DATA_POS_FRAME_LENGTH, fl);
	  dataFrame.appendBytes(&dCRC, DATA_LEN_CRC);
	}
    return true;
}