#include "lpc17xx.h"                              /* LPC17xx definitions    */
#include "uart.h"
#include "can.h"

volatile unsigned char UART2_BUF; 
void UART2_IRQHandler(void)
{
    uint32_t flag;
    flag  = LPC_UART2->IIR;                                             /* ��ȡ(���)�ж��ж�״̬       */
    flag &= 0x0F;
   
    if((flag == 0X04) && (LPC_UART2->LSR & 0X01)) {                     /* ����ǽ����жϣ�����������   */
        UART2_BUF = LPC_UART2->RBR;                                     /* ��ȡ����                     */
//        UART2_SendByte (UART2_BUF);                                     /* ���ڻ�������                 */           
    }
		CAN_waitReady(CAN1); 
		if (CAN_TxRdy[CAN1]) 
		{                                              /* ʹ�ÿ�����1����              */
        CAN_TxRdy[CAN1] = 0; 
				CAN_TxMsg[CAN1].data[0] =  UART2_BUF;                          /* �������                     */
        CAN_send (CAN1, &CAN_TxMsg[CAN1]);                          /* ��������                     */
		}
}

/*********************************************************************************************************
** Functoin name:       CAN_IRQHandler
** Descriptions:        CAN�жϷ������
** input paraments:     ��
** output paraments:    ��    
** Returned values:     ��
*********************************************************************************************************/
void CAN_IRQHandler (void)  
{
  volatile uint32_t icr;
                                                                      
  icr = LPC_CAN1->ICR;               	//��ȡ�ж���Ϣ  ��ȡ����                                                                            
//	icr = LPC_CAN2->ICR;                //��ȡ�ж���Ϣ  ��ȡ����   
	
  if (icr & (1 << 0))  								//�����ж�
	{                          
    CAN_recive(CAN1, &CAN_RxMsg[CAN1]);  //��ȡ����   
		UART2_SendByte (CAN_RxMsg[CAN1].data[0]); 		
    CAN_RxRdy[CAN1] = 1;              //��λ���ձ�־                           
  }
  if (icr & (1 << 1)) 								//������1�������   
	{                           				                      
		CAN_TxRdy[CAN1] = 1;  						//��λ���ͱ�־ 
  }
}

