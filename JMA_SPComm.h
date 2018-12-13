/**
 * Small Pack Communication protocol
 * 
 * Created by Kunpeng Zhang on 2014-1-27.
 * Copyright (c) 2014年 JungleMetal Software. All rights reserved.
 * 
 * Kunpeng Zhang
 * 2015.10.28 modified for Arduino
 * 
 */

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <JMACRC8.h>
#include <JMA_SPBuffer.h>
#include <JMA_SPRange.h>
#include <JMA_SPComm100.h>

#ifndef __jma_sp_comm_h
#define __jma_sp_comm_h

/**
 * \~english 
 * Communication protocol version, using BCD encoding
 * 
 * \~chinese
 * 通讯协议版本，采用 BCD 编码
 * 
 */
#define COMM_MAIN_VER_100    0x10
#define COMM_DATA_VER_100    0x10

/**
 * \~english 
 * Communication protocol version
 * 
 * \~chinese
 * 通讯协议版本
 * 
 */
#define LASTE_COMM_MAIN_VER   COMM_MAIN_VER_100

/**
 * \~english 
 * Data format version
 * 
 * \~chinese
 * 通讯协议数据格式版本
 */
#define LASTE_COMM_DATA_VER   COMM_DATA_VER_100

/**
 * \~english 
 * Data frame detection status
 * 
 * \~chinese
 * 数据帧检测状态
 */
typedef enum {
    DF_CHECK_OK = 0,
	
	/**
	 * \~english 
	 * The total length of the data frame is wrong.
	 * 
	 * \~chinese
	 * 数据帧总长度错误
	 */
    DF_CHECK_ERROR_FRAME_TOTAL_LENGTH,
	
	/**
	 * \~english 
	 * Data frame header error
	 * 
	 * \~chinese
	 * 数据帧头错误
	 */
    DF_CHECK_ERROR_FRAME_HEADER,
	
	/**
	 * \~english 
	 * Wrong data length in data frame
	 * 
	 * \~chinese
	 * 数据帧中数据区长度错误
	 */
    DF_CHECK_ERROR_DATA_LENGTH,
	
	/**
	 * CRC error
	 * 
	 * \~chinese
	 * CRC校验错误
	 */
    DF_CHECK_ERROR_CRC,
	
	/**
	 * Data length overflow in data frame
	 * 
	 * \~chinese
	 * 数据帧中数据区长度 OVER
	 */
    DF_CHECK_ERROR_DATA_LENGTH_OVER

} JMA_SPCommDataFrameCheckStatus;

/***
 * \~english 
 * SPComm (Small pack communication protocol)
 * 
 * \~chinese
 * SPComm 小包通讯协议
 */
class JMA_SPComm
{
	public:

		/**
		 * @brief 
		 * \~english open data buffer
		 * \~chinese 打开缓存
		 * @param bufferLength
		 */
		void begin(uint8_t bufferLength);

		/**
		 * @brief 
		 * \~english 
		 * Check data frame is correct (whether the data is parsed - if the data frame is correct), 
		 * return DF_CHECK_OK to indicate the correct data frame, otherwise the data frame error
		 * 
		 * \~chinese 检查数据帧是否正确，返回 DF_CHECK_OK 是正确数据帧，否则数据帧错误
		 * 
		 * @param parseData boolean 是否解析数据 [True | False ] -- 如果数据帧正确才执行
		 * @return uint8_t
		 * 
		 * \~chinese 
		 * 返回 DF_CHECK_OK 是正确数据帧，否则数据帧错误。返回值为： JMA_SPCommDataFrameCheckStatus
		 */
		uint8_t checkDataFrames(bool parseData);
		
		/**
		 * @brief 
		 * \~english 
		 * Check data frame is correct (whether the data is parsed - if the data frame is correct), 
		 * return DF_CHECK_OK to indicate the correct data frame, otherwise the data frame error
		 * 
		 * \~chinese 检查数据帧是否正确，同时解析数据－如果数据帧正确才执行，返回 DF_CHECK_OK 是正确数据帧，否则数据帧错误
		 * 
		 * @return uint8_t 
		 * \~chinese 返回 DF_CHECK_OK 是正确数据帧，否则数据帧错误。返回值为： JMA_SPCommDataFrameCheckStatus
		 */
		uint8_t checkDataFramesAndParse();

		/**
		 * @brief 
		 * \~english clear data buffer
		 * \~chinese 清空数据缓存
		 */
		void clearBuffer();
		
		/**
		 * @brief 
		 * \~english add a byte into data buffer
		 * \~chinese 增加缓存数据
		 * @param byte
		 */
		void addBuffer(uint8_t byte);
		
		/**
		 * @brief 
		 * @param buffer	add bytes into 
		 * @param length
		 */
		void addBuffer(const void *buffer, uint8_t length);

		/* data */
		///通讯协议版本 - 解析数据帧，该数值由解析函数赋值。要生成数据帧则设置该数值。
		uint8_t comMainVer;
		///数据协议版本 - 解析数据帧，该数值由解析函数赋值。要生成数据帧则设置该数值。
		uint8_t comDataVer;
		/**
		 * \~english Data frame length = version + data area + CRC
		 * \~chinese 数据帧长度 = 版本 + 数据区 + CRC
		 * 
		 * @note 
		 * \~english
		 * Do not set this property. the value of the property will be updated when checkDataFrames() or checkDataFramesAndParse() is called
		 * \~chinese
		 * 不要设置该属性，当 checkDataFrames() 或 checkDataFramesAndParse() 调用后会更新该属性的数值
		 */
		uint8_t dataFramesLength;
		/**
		 * \~english CRC value of the data frame
		 * \~chinese 数据帧中的 CRC 校验码
		 * 
		 * @note 
		 * \~english
		 * Do not set this property. the value of the property will be updated when checkDataFrames() or checkDataFramesAndParse() is called
		 * \~chinese
		 * 不要设置该属性，当 checkDataFrames() 或 checkDataFramesAndParse() 调用后会更新该属性的数值
		 */
		uint8_t dataCRC;
		/**
		 * \~english Enabled CRC
		 * \~chinese 启用CRC校验
		 */
		bool enabledCRC = true;
		/**
		 * \~english Data buffer
		 * \~chinese 数据缓冲区
		 */
		JMA_SPBuffer dataFrame;

		// protected:

		uint8_t _getFrameLength();
		JMA_SP_Range _getCRCRange(uint8_t frameLength);

		/**
		 * @brief 
		 * \~english Parse data - Subclass implementation data parsing
		 * \~chinese 解析数据-子类继成实现具体数据的解析
		 * @param dataRange
		 * @return boolean
		 */
		virtual bool _parseData(JMA_SP_Range dataRange);
};

#endif
