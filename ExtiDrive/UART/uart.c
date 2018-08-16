/****************************************Copyright (c)****************************************************
**                                 http://www.OpenMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           uart.c
** Last modified Date:  2014-04-18
`** Last Version:        V1.1
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          OpenMCU
** Created date:        2010-05-10
** Version:             V1.07
** Descriptions:        ��дʾ������
**
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#include "lpc17xx.h"                              /* LPC17xx definitions    */
#include "uart.h"

#define FOSC                        12000000                            /*  ����Ƶ��                  */
#define FCCLK                      (FOSC  * 8)                          /*  ��ʱ��Ƶ��<=100Mhz          */
                                                                        /*  FOSC��������                */
#define FCCO                       (FCCLK * 3)                          /*  PLLƵ��(275Mhz~550Mhz)      */
                                                                        /*  ��FCCLK��ͬ���������ż���� */
#define FPCLK                      (FCCLK / 4)                          /*  ����ʱ��Ƶ��,FCCLK��1/2��1/4*/
                                                                        /*  ����FCCLK��ͬ               */

#define UART0_BPS     9600                                             /* ����0ͨ�Ų�����             */
#define UART2_BPS     9600                                             /* ����2ͨ�Ų�����             */
/*********************************************************************************************************
** Function name:       UART0_Init
** Descriptions:        ��Ĭ��ֵ��ʼ������0�����ź�ͨѶ����������Ϊ8λ����λ��1λֹͣλ������żУ��
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void UART0_Init (void)
{
	uint16_t usFdiv;
	/* UART0 */
	LPC_PINCON->PINSEL0 |= (1 << 4);             /* Pin P0.2 used as TXD0 (Com0) */
	LPC_PINCON->PINSEL0 |= (1 << 6);             /* Pin P0.3 used as RXD0 (Com0) */

	LPC_UART0->LCR  = 0x83;                      /* �������ò�����               */
	usFdiv = (FPCLK / 16) / UART0_BPS;           /* ���ò�����                   */
	LPC_UART0->DLM  = usFdiv / 256;
	LPC_UART0->DLL  = usFdiv % 256; 
	LPC_UART0->LCR  = 0x03;                      /* ����������                   */
	LPC_UART0->FCR  = 0x06; 				   
}

/*********************************************************************************************************
** Function name:       UART0_SendByte
** Descriptions:        �Ӵ���0��������
** input parameters:    data: ���͵�����
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int UART0_SendByte (int ucData)
{
	while (!(LPC_UART0->LSR & 0x20));
    return (LPC_UART0->THR = ucData);
}

/*********************************************************************************************************
** Function name:       UART0_GetChar
** Descriptions:        �Ӵ���0��������
** input parameters:    ��
** output parameters:   ��
** Returned value:      ���յ�������
*********************************************************************************************************/
int UART0_GetChar (void) 
{
  	while (!(LPC_UART0->LSR & 0x01));
  	return (LPC_UART0->RBR);
}

/*********************************************************************************************************
** Function name:       UART0_SendString
** Descriptions:	    	�򴮿ڷ����ַ���
** input parameters:    s:   Ҫ���͵��ַ���ָ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void UART0_SendString (unsigned char *s) 
{
  	while (*s != 0) 
	{
   		UART0_SendByte(*s++);
	}
}

/*********************************************************************************************************
** Function name:       UART2_Init
** Descriptions:        ��Ĭ��ֵ��ʼ������2�����ź�ͨѶ����������Ϊ8λ����λ��1λֹͣλ������żУ��
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void UART2_Init (void)
{
	uint16_t usFdiv;
	/* UART2 */
	LPC_PINCON->PINSEL0 |= (1 << 20);             /* Pin P0.10 used as TXD2 (Com2) */
	LPC_PINCON->PINSEL0 |= (1 << 22);             /* Pin P0.11 used as RXD2 (Com2) */

	LPC_SC->PCONP = LPC_SC->PCONP|(1<<24);	      /*��UART2��Դ����λ	           */

	LPC_UART2->LCR  = 0x83;                       /* �������ò�����                */
	usFdiv = (FPCLK / 16) / UART2_BPS;            /* ���ò�����                    */
	LPC_UART2->DLM  = usFdiv / 256;
	LPC_UART2->DLL  = usFdiv % 256; 
	LPC_UART2->LCR  = 0x03;                       /* ����������                    */
	LPC_UART2->FCR  = 0x07;
	NVIC_EnableIRQ(UART2_IRQn);                   /* ��NVIC��ʹ���ж�             */  
  LPC_UART2->IER = 0x01;                        /* ʹ�ܽ����ж�                 */
}

/*********************************************************************************************************
** Function name:       UART2_SendByte
** Descriptions:        �Ӵ���2��������
** input parameters:    data: ���͵�����
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int UART2_SendByte (int ucData)
{
	while (!(LPC_UART2->LSR & 0x20));
    return (LPC_UART2->THR = ucData);
}

/*********************************************************************************************************
** Function name:       UART2_GetChar
** Descriptions:        �Ӵ���2��������
** input parameters:    ��
** output parameters:   ��
** Returned value:      ���յ�������
*********************************************************************************************************/
int UART2_GetChar (void) 
{
  	while (!(LPC_UART2->LSR & 0x01));
  	return (LPC_UART2->RBR);
}

/*********************************************************************************************************
** Function name:       UART2_SendString
** Descriptions:        UART2_SendString
** input parameters:    s:   Ҫ���͵��ַ���ָ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void UART2_SendString (unsigned char *s) 
{
  	while (*s != 0) 
	{
   		UART2_SendByte(*s++);
	}
}
