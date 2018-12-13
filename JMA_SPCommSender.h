/*****************
 *
 * \~english 
 * Communication frame transmitter, responsible for generating data frames
 * 
 * \~chinese 
 * 通讯帧发送器，负责生成数据帧
 *
 *	Kunpeng Zhang
 *	2015.10.30
 * 
 */
#include <JMAFoundation.h>
#include <JMA_SPComm.h>

#ifndef __jma_sp_comm_sender_h
#define __jma_sp_comm_sender_h

class JMA_SPCommSender : public JMA_SPComm
{
	public:

	 	/**
		 * \~english 
		 * Data buffer already event
		 * 
		 * \~chinese
		 * 数据发送区准备好事件
		 */
	 	JMAEvent onEventFrameDataAlready = NULL;

	protected:
		/**
		 * @brief 
		 * \~english Initialize the receive buffer
		 * \~chinese 初始化数据帧
		 */
		void initFrameBuffer();

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
		uint8_t calcCRCFromDataFrames();

		/**
		 * @brief 
		 * \~english Generate data send area preparation event
		 * \~chinese 创建数据发送区准备事件
		 */
		void eventOnFrameDataAlready();

};

#endif