#include "Nus_Master_DataHandle.h"

#include "Protocol_Analysis.h"
#include "Somputon_BLE_DataHandle.h"
#include "ble_gap.h"
#include "ble_srv_common.h"
#include "sdk_common.h"

#include "System_Variable.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


extern uint8_t mac_addr[6];



typedef struct{

	uint8_t  Data_Length;      //保存数据长度
	uint16_t Common_World;     //保存命令字
	uint8_t  Device_Type;      //设备类型
	uint8_t  MacAddr_Device;   //设备mac 地址
}_s_analsis_word;


_s_analsis_word  Common_Word;


//crc8 校验
unsigned char Crc8( unsigned char *Address, unsigned char Length )
{
		static unsigned char crc;
		static unsigned char crcbuff;
		static unsigned char i;
		crc = 0;
	
		while( Length-- )
		{
			crcbuff = *Address ++;
			for(i = 0; i < 8; i++)
			{
				if((crc ^ crcbuff) & 0x01)
				{
					crc ^= 0x18;
					crc >>= 1;
					crc |= 0x80;
				}
				else
				{
					crc >>= 1;
				}
				crcbuff >>= 1;
			}
		}
		return crc;
}



//获取mac 地址
 void get_mac_addr(uint8_t *p_mac_addr)
{
		uint32_t error_code;
		ble_gap_addr_t p_mac_addr_t ;
		error_code = sd_ble_gap_addr_get(&p_mac_addr_t);
		//APP_ERROR_CHECK(error_code);
		uint8_t *d = p_mac_addr_t.addr;
		for ( uint8_t i = 6; i >0;)
		{	
			i--;
			p_mac_addr[5-i]= d[i];
		}
}



void User_Get_Addr(void)
{
    get_mac_addr(&system_work.device_mac_addr[0]);

    #if 1
    
    for(uint8_t i = 0; i < 6;i++)
    {
        
        printf("0x%02x : ",system_work.device_mac_addr[i]);
		
    }
    #if 0
    mac_addr[0] = system_work.device_mac_addr[5];
    mac_addr[1] = system_work.device_mac_addr[4];
	mac_addr[2] = system_work.device_mac_addr[3];
	#endif
    
    #endif
    

}





//处理串口数据
void nus_data_handle(uint8_t *data, uint8_t length)
{
	
	uint8_t data_buffer[100];       	//接收数据缓冲区大小
	
	memcpy(data_buffer,data,length);
	//memset(data,0,length);
	
	//printf("------------------------------");
	//答应接收的数据
    #if 0     
    for(uint8_t i = 0; i< length;i++)
    {
        printf("\r\nDATA 0x%02x \r\n",data_buffer[i]);
    }
    #endif
	
	if(data_buffer[0]!= START_FLAG)	
	{
		return;
	}
	else
	{
		Common_Word.Data_Length  = data_buffer[DATA_LENGTH_INDIX_LOW];    //获取数据包长度
		Common_Word.Data_Length = Common_Word.Data_Length>>8;
		Common_Word.Data_Length |= data_buffer[DATA_LENGTH_INDIX_HIGH];
		
		
		
		//printf("DATA LENGHT : %d",(uint8_t)Common_Word.Data_Length);
        
		Common_Word.Common_World = data_buffer[DATA_COMMOND_WORD];	   //获取命令字
		Common_Word.Common_World = Common_Word.Common_World >> 8;
		Common_Word.Common_World |= data_buffer[DATA_COMMOND_WORD +1 ];        
		
		//printf("COMMAND WORLD:  0X%04x",Common_Word.Common_World);
        
		
		
		Common_Word.Device_Type = data_buffer[DATA_DEVICE_TYPE_INDEX];     //获取设备类型
		
	    //memcpy(&Common_Word.MacAddr_Device,&data[DATA_DEVICE_MAC_INDEX],6);  //拷贝mac 地址		 	  
			
		
		
		
		if(data_buffer[Common_Word.Data_Length +2 ]!= Crc8(&data_buffer[1],Common_Word.Data_Length + 1))  //crc8校验
		{
			//#ifdef UART_MASTER_TEST 
			printf(" data_buffer crc %d", data_buffer[Common_Word.Data_Length]);
			
			printf("CRC ERROR");
			//#endif
			return;
		}
		//处理数据内容
		
		if(receive_data_from_app != NULL)
		{
			receive_data_from_app(Common_Word.Common_World,&data_buffer[DATA_CONTENT_INDEX],Common_Word.Data_Length);
		}
	}
}


