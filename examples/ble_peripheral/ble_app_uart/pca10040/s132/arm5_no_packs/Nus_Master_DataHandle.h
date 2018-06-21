#ifndef __NUS_MASTER_DATAHANDLE_H
#define __NUS_MASTER_DATAHANDLE_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nordic_common.h"



typedef enum{
	START_INDEX   = 0,					//��ʼ����
	DATA_LENGTH_INDIX_LOW = 1,          //���ݳ��ȵ�λ
	DATA_LENGTH_INDIX_HIGH = 2,         //���ݳ��ȸ�λ
    DATA_DEVICE_TYPE_INDEX = 4,			//�豸����
	DATA_DEVICE_MAC_INDEX = 5,			//�豸mac ��ַ����
	DATA_COMMOND_WORD = 11,             //����������
	DATA_CONTENT_INDEX = 13			    //������������
	
}data_indix;



unsigned char Crc8( unsigned char *Address, unsigned char Length);
void nus_data_handle(uint8_t *data, uint8_t length);
void get_mac_addr(uint8_t *p_mac_addr);
void User_Get_Addr(void);



#endif



