/**
 * Small pack comm v1.0.0
 * 
 * Created by Kunpeng Zhang on 2014-2-10.
 * Copyright (c) 2014年 JungleMetal Software. All rights reserved.
 * 
 * Kunpeng Zhang
 * 2015.10.28 modified for Arduino
 */

#ifndef __jma_sp_comm100_h
#define __jma_sp_comm100_h

/***
 * Data frame format
 * \~chinese
 * 数据帧格式
 * 
 * +------------------------------------------------------------+
 * | 0x023C | FRAME LENGTH  | COM VERSION |   DATA    | CRC     |
 * | 2bytes | 1byte         | 2bytes      | 1~N Bytes | 1 Byte  |
 * +------------------------------------------------------------+
 * 
 * +------------------------------------------------------------+
 * |              DATA (N Bytes)                                |
 * +------------------------------------------------------------+
 * | COMMAND | PARAM LENGTH | PARAMS                            |
 * |  1byte  | 1 byte       | N-2 Bytes                         |
 * +------------------------------------------------------------+
 * 
 */

#define DATA_FRAME_MIN_LENGTH   7

#define DATA_FRAME_HEADER   	0x023C
#define DATA_FRAME_HEADER_1   	0x02
#define DATA_FRAME_HEADER_2   	0x3C

/**
 * \~english
 * Data frame header
 * 
 * \~chinese 数据帧头
 */
#define DATA_POS_HEADER         0
#define DATA_LEN_HEADER         2

/**
 * \~english 
 * Data frame length
 * \~chinese 数据帧长
 */
#define DATA_POS_FRAME_LENGTH   2
#define DATA_LEN_FRAME_LENGTH   1

/**
 * \~english Communication protocol version number
 * \~chinese 通讯协议版本号
 */
#define DATA_POS_MAIN_VERSION   3
#define DATA_LEN_MAIN_VERSION   1

/**
 * \~english Communication protocol data format version number
 * \~chinese 通讯协议数据格式版本号
 */
#define DATA_POS_DATA_VERSION   4
#define DATA_LEN_DATA_VERSION   1


/**
 * \~english Communication Protocol Data Area = Command + Command_Parameter_Length + Parameter [+ CRC]
 * \~chinese 通讯协议数据区 = 指令 + 指令参数长度 + 参数 [+ CRC]
 */
#define DATA_POS_DATA           5

/**
 * \~english Command
 * \~chinese 指令
 */
#define DATA_POS_COMMAND        5
#define DATA_LEN_COMMAND        1

/**
 * \~english Command Length
 * \~chinese 指令参数长度
 */
#define DATA_POS_COMMAND_PARAM  6
#define DATA_LEN_COMMAND_PARAM  1

/**
 * \~english Command Data
 * \~chinese 指令数据
 */
#define DATA_POS_COMMAND_DATA   7

/**
 * \~english CRC Length
 * \~chinese CRC 长度
 */
#define DATA_LEN_CRC            1

#endif