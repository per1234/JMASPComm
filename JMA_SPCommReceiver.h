/**
 * Created by Kunpeng Zhang on 2014-1-27.
 * Copyright (c) 2014 JungleMetal Software. All rights reserved.
 * 
 * Kunpeng Zhang
 * 2015.10.28 modified for Arduino
 */

#include <JMAFoundation.h>
#include <JMA_SPBuffer.h>
#include <JMA_SPRange.h>
#include <JMA_SPComm.h>

#ifndef __jma_sp_comm_receiver_h
#define __jma_sp_comm_receiver_h

/**
 * \~english Define data parse events (*event_sender, *buffer, data_location, data_length)
 * \~chinese 定义数据区解析事件（事件发送者指针, 缓存区, 数据位置, 数据长度）
 * @param sender
 * @param buffer
 * @param dataLocation
 * @param dataLength
 */
typedef void(*JMASPCommEventDataParse)(void*, void*, uint8_t, uint8_t);


class JMA_SPCommReceiver : public JMA_SPComm
{
	public:

		void addByte(uint8_t byte);

		/**
		 * \~english Data received event before verify CRC
		 * \~chinese 数据接收完成，未进行CRC校验事件
		 */
		JMAEvent onEventDataBeforeVerifyCRC = NULL;
		/**
		 * \~english data parse event
		 * \~chinese 数据区解析
		 */
		JMASPCommEventDataParse onEventDataParse = NULL;
		/**
		 * \~english Data received and verify CRC is OK
		 * \~chinese 数据接收完成并且正确解析完成
		 */
		JMAEvent onEventDataReceived = NULL;
		/**
		 * \~english Received data error
		 * \~chinese 接收的数据错误
		 */
		JMAEvent onEventDataFailed = NULL;

	protected:
    uint8_t _receiveCount = 0x00;
    uint8_t _lastByte= 0x00;
    uint8_t _hearder1= 0x00, _hearder2= 0x00;
    uint8_t _frameLen= 0x00;

    /**
	 * 数据帧开始 - 检测到 hearder1 = 0x02 && hearder2 = 0x3C
	 */
	bool _beginFrame= false;

	/**
	 * @brief 
	 * \~english Parse data
	 * \~chinese 解析数据区
	 * 
	 * @param dataRange
	 * @return 
	 */
    bool _parseData(JMA_SP_Range dataRange);

	/**
     * @brief 
	 * \~english Initialize the receive buffer (called when the message header is received)
	 * \~chinese 初始化接收缓存区（当收到信息头以后调用）
	 * 
	 */
    void initFrameBuffer();

    /**
     * @brief 
	 * \~english Generate data received event before verify CRC
	 * \~chinese 回调数据接收事件
	 * 
     */
    void eventOnDataBeforeVerifyCRC();
    
	/**
     * @brief 
	 * \~english Generate data parse event
	 * \~chinese 数据解析解析
	 * 
	 * @param dataLocation
	 * @param dataLength
	 */
    void eventOnEventDataParse(uint8_t dataLocation, uint8_t dataLength);

    /**
     * @brief 
	 * \~english Generate data received and verify CRC is OK
	 * \~chinese 数据接收完成并且正确解析完成
     */
    void eventOnEventDataReceived();
    
	/**
	 * @brief
	 * \~english Generate received data error
	 * \~chinese 接收的数据错误
	 */
    void eventOnEventDataFailed();

};

#endif
