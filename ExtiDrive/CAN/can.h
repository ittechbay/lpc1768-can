/****************************************Copyright (c)****************************************************
**                                 http://www.openmcu.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           can.h
** Last modified Date:  2012-07-23
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          openmcu
** Created date:        2012-07-23
** Version:             V1.00
** Descriptions:        ��дʾ������
**
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef _CAN_H_
#define _CAN_H_

#include <lpc17xx.h>
/*********************************************************************************************************
**      ��س�������               
*********************************************************************************************************/
#define CAN1             0                                              /*  ��·ѡ��CAN1                */
#define CAN2             1                                              /*  ��·ѡ��CAN2                */

#define STANDARD_FORMAT  0                                              /*  ��׼֡                      */
#define EXTENDED_FORMAT  1                                              /*  ��չ֡                      */

#define DATA_FRAME       0                                              /*  ����֡                      */
#define REMOTE_FRAME     1                                              /*  Զ��֡                      */

#define  PCLK            (100000000UL/4)                                /*  ����ʱ��Ƶ��                */

#define ACCF_OFF				0x01
#define ACCF_BYPASS				0x02
#define ACCF_ON					0x00
#define ACCF_FULLCAN			0x04

/* This number applies to all FULLCAN IDs, explicit STD IDs, group STD IDs, 
explicit EXT IDs, and group EXT IDs. */ 
#define ACCF_IDEN_NUM			1

/* Identifiers for FULLCAN, EXP STD, GRP STD, EXP EXT, GRP EXT */
#define FULLCAN_ID				0x100



/*********************************************************************************************************
**      ֡��ʽ����               
*********************************************************************************************************/
typedef struct  {
  unsigned int   id;                                                    /*  29/11 λ��ʶ��              */
  unsigned char  data[8];                                               /*  8�ֽ����ݳ�                 */
  unsigned char  len;                                                   /*  ���ݳ��ֽ���                */
  unsigned char  format;                                                /*  0 - ��׼֡, 1- ��չ֡       */
  unsigned char  type;                                                  /*  0 - ����֡, 1 - Զ��֡      */
} CAN_FRAME;

/*********************************************************************************************************
**      �����ӿڶ���               
*********************************************************************************************************/
void CAN_setup         (uint32_t ctrl);                                /*  ����CAN������                */
void CAN_start         (uint32_t ctrl);                                /*  ����CAN������                */
void CAN_waitReady     (uint32_t ctrl);                                /*  �ȴ����;���                 */
void CAN_send          (uint32_t ctrl, CAN_FRAME *msg);                /*  ����CAN����                  */
void CAN_recive        (uint32_t ctrl, CAN_FRAME *msg);                /*  ����CAN����                  */

extern CAN_FRAME       CAN_TxMsg[2];                                   /* ���ͻ�����                    */
extern CAN_FRAME       CAN_RxMsg[2];                                   /* ���ջ�����                    */                                
extern unsigned int    CAN_TxRdy[2];                                   /* ���Ϳ��ñ�ʶ                  */
extern unsigned int    CAN_RxRdy[2];                                   /* ������ɱ�ʶ                  */

#endif 
/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/
