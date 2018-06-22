#include "Somputon_BLE_DataHandle.h"
#include "System_Variable.h"

#include "NUS_Master_DataHandle.h"
#include "ble_nus.h"





uint8_t SendBuffer[256];
extern uint8_t mac_addr[6];

 
extern void send_data_proc(uint8_t *aSendBuffer,uint16_t len);     //���ͺ���



/**@brief get_real_time_data_cmd     
 *
 *	Function for replying to get real time data.
 *
 * @param[in]   void  
 *
 * @return      void
 */
void get_real_time_data_cmd(void)
{
	uint8_t aSendBuffer[50];
    
    aSendBuffer[0] = START_FLAG;                                //����ͷ
    aSendBuffer[1] = 0x00;                                      //���ݳ���
    aSendBuffer[2] = 12;
    aSendBuffer[3] = PROTOCOL_VERSION;                          //Э��汾��
    aSendBuffer[4] = 0x00;                                      //�豸���� 
    //memcpy(&aSendBuffer[5],&system_work.device_mac_addr,6);     //��ȡmac ��ַ

    aSendBuffer[11] =  (uint8_t)(GET_REAL_TIME_DATA_COMMAND>>8);   //���������
    aSendBuffer[12] =  (uint8_t)GET_REAL_TIME_DATA_COMMAND;        //���������
    aSendBuffer[13] =  0x12;                                       //����         
    aSendBuffer[14] = Crc8(&aSendBuffer[1],13);                    //crc У��

    send_data_proc(aSendBuffer,15);                               //��������
}


uint8_t send_buff[50];

/**@brief clear_history_data_cmd     
 *
 *	Function for replying to the clear history data command from the APP and wouldn't contain any data.
 *
 * @param[in]   void   Point to the time struct data.
 *
 * @return      void
 */
void bond_cmd(void)
{
    uint8_t aSendBuffer[256];

    
    send_buff[0] = START_FLAG;                                //����ͷ
    send_buff[1] = 0x00;                                      //���ݳ���
    send_buff[2] = 11;
    send_buff[3] = PROTOCOL_VERSION;                          //Э��汾��
    send_buff[4] = 0x00;                                      //�豸���� 
    memcpy(&send_buff[5],&system_work.device_mac_addr[0],6);     //��ȡmac ��ַ
	
	
	
    send_buff[11] =  (uint8_t)(BOND_COMMAND_REPLY>>8);         //���������
    send_buff[12] =  (uint8_t)BOND_COMMAND_REPLY;              //���������

    send_buff[13] = Crc8(&send_buff[1],12);               //crc У��

    send_data_proc(send_buff, 14);                       //��������
}

/**@brief clear_history_data_cmd     
 *
 *	Function for replying to the clear history data command from the APP and wouldn't contain any data.
 *
 * @param[in]   void   Point to the time struct data.
 *
 * @return      void
 */

void clear_history_data_cmd(void)
{


}


/**@brief set_device_time_cmd     
 *
 *	Function for setting time.
 *
 * @param[in]   data_info   Point to the time struct data.
 *
 * @return      void
 */
void set_device_time_cmd(uint8_t *data_info)
{



}


/**@brief get_device_time_cmd     
 *
 *	Function for getting time.
 *
 * @param[in]   second   use second to stand for the current time.
 *
 * @return      void
 */
void get_device_time_cmd(uint32_t second)
{


}


/**@brief control_device_cmd     
 *
 *	Function for dealing with control command.
 *
 * @param[in]   ctrl_data   clife control word data
 *
 * @return      void
 */
void control_device_cmd(uint8_t *ctrl_data)
{




}


/**@brief Clife_GetHisData     
 *
 *	Function for dealing with the process of getting history data command.
 *
 * @param[in]   cmd   clife command word 
 * @param[in]   data  clife command word data
 * @param[in]   len   data length
 *
 * @return      void
 */
void Clife_GetHisData(uint16_t cmd, uint8_t* data, uint16_t len)
{
	
	
}


/**@brief Clife_GenerateHisData     
 *
 *	Function for Generating history data to write to the flash.
 *
 * @param[in]   void
 *
 * @return      void
 */
void Clife_GenerateHisData(void)
{



}



//�豸�����Ϻ����������������֤

void AuthInfo_Request(void)
{
    
  
    
}




