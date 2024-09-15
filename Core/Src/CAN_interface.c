
#include "CAN_interface.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

CAN_HandleTypeDef hcan1;
extern UART_HandleTypeDef huart2 ;

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


void CAN1_RX(void)
{
	CAN_RxHeaderTypeDef LOCAL_ReceivedMsg ;
	char Local_RXMSG [50];

	uint8_t LOCAL_au8ReceivedData[9] = " ";

	while (HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0) == 0 );

	if(	HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &LOCAL_ReceivedMsg, LOCAL_au8ReceivedData) != HAL_OK)
	{
		Error_Handler();
	}

	sprintf(Local_RXMSG , "Message received : %s \r\n" ,LOCAL_au8ReceivedData );
	HAL_UART_Transmit(&huart2,(uint8_t*) Local_RXMSG, strlen(Local_RXMSG), HAL_MAX_DELAY);

}


void CAN_FilterConfig(void)
{
	CAN_FilterTypeDef LOCAL_FilterConfig =
	{
			.FilterActivation = CAN_FILTER_ENABLE ,
			.FilterBank = 0 ,
			.FilterFIFOAssignment = CAN_RX_FIFO0 ,
			.FilterMaskIdHigh = 0 ,
			.FilterMaskIdLow = 0 ,
			.FilterMode = CAN_FILTERMODE_IDMASK ,
			.FilterScale = CAN_FILTERSCALE_32BIT
	};



	if(	HAL_CAN_ConfigFilter(&hcan1, &LOCAL_FilterConfig) != HAL_OK)
	{
		Error_Handler();
	}

}























