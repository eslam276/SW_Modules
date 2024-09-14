
#include "CAN_interface.h"
#include "main.h"

CAN_HandleTypeDef hcan1;

void CAN1_TX(void)
{
	CAN_TxHeaderTypeDef CAN_TX_Data ;

//	char Local_message[] = {'h','e','l' , 'l' , 'o'};
//	char Local_TranmitMSG [50];
	uint32_t Local_u32MailBox ;
	CAN_TX_Data.StdId = 0x65D;
	CAN_TX_Data.IDE = CAN_ID_STD ;
	CAN_TX_Data.RTR = CAN_RTR_DATA ;
	CAN_TX_Data.DLC = 8 ;

	if ( HAL_CAN_AddTxMessage(&hcan1 , &CAN_TX_Data ,(uint8_t*) "Hi Eslam" ,&Local_u32MailBox ) != HAL_OK )
	{
		Error_Handler();
	}

	/* Wait as long as the message is pending */
	while(HAL_CAN_IsTxMessagePending(&hcan1, Local_u32MailBox) == 1);

//	sprintf(Local_TranmitMSG , "Message transmitted\r\n");
//	HAL_UART_Transmit(&huart2, Local_TranmitMSG, strlen(Local_TranmitMSG), HAL_MAX_DELAY);

}
