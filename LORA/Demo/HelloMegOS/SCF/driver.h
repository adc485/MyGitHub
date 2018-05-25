#ifndef  __DRIVER_H  
#define  __DRIVER_H 

//����ͷ�ļ�*********************************************************************************************************** 
#include <c8051f340.h> 
#include <intrins.h>
//#include <absacc.h>
//#include <stdlib.h>   
#include <stdio.h>    
//�������� **************************************************************************************************************

#ifndef NULL
  #define NULL ((void *) 0)
#endif


#define	  PAGESIZE		  (512) //ҳ�ֽ���0x200==512
#define	  LOCKPAGE	      (50)	 //0~LOCKPAGE��FLASH���������������ٲ�������д
#define   STORPAGE		  (LOCKPAGE+1)	 //ϵͳ����ҳ
#define	  BUFPAGE	      (LOCKPAGE+2)	 //�ݴ�ҳ
#define	  LOGPAGE	      (LOCKPAGE+3)	 //��־ҳ
#define   MAXLOGS		  (250)	 //�����־�� 
#define	  STORSIZE		  (10)	 //�洢�ֽ���

#define UARTLENGTH    64      //
//�������Ͷ���******************************************
typedef   unsigned       char   u8;
typedef   unsigned       int    u16;
typedef   unsigned       long   u32;
typedef     signed       char   s8;
typedef     signed       int    s16;
typedef     signed       long   s32;
typedef   enum {FALSE = 0, TRUE = !FALSE} bool;

//����ṹ��*****************************************

struct  UsartData//����USART�������ݰ�
	{
	 u8  State;   //USART����״̬��־ 
     u8	 Time;    //USART���ռ�ʱ
     u8	 RXlenth; //USART�������ݰ�����
     u8	*RXbuf;	  //USART1 �����������û������ݿռ���׵�ַ
	}; 

struct  EventLog	    //�¼���־
	{
		u16  Number;     //��־���
		u16	 Event;      //�¼����
		u16  Data;	     //�������
		u8  *Brief;		 //���ݼ��
	};
struct  FlashData	  //���ڵ���޸����ݣ�����FLASH��
	{
		u32	 FSFlag;//�Ƿ�Ϊ���س�����һ���ϵ縴λ
		u8   LogAmount;     //��־���� 
	};
	
union  DataConvert	
{
   	u32   Reg32;
	u16   Reg16[2];
	u8    Reg8[4];
};	
	 
//���Ŷ���*******************************************************************************************
sbit        RXD=P0^5;	 //��©���
sbit        TXD=P0^4;	 //�������				   
sbit        LED=P0^3;	 //�������
sbit       BEEP=P1^6;	 //�������


//ȫ�ֱ�������*******************************************************************************************************************
extern  struct  FlashData  code  SystemParameter;//flash����
//��������***************************************************************************************************************** 
//�꺯��
#define   FEED_WDG()   // {PCA0CPH4 = 0x00;}  
#define	  WDG_INIT()   // {PCA0L=0;PCA0H=0;PCA0CPL4=0xFF;PCA0MD |= 0x60;}		
#define   SW_RESET()    {RSTSRC |=0X10;}
#define   LED_ON()	     LED=0
#define   LED_OFF()	     LED=1


//init.c
void   init_sysclk(void);
void   init_timer0(void);
void   init_timer2(void);
void   init_uart0(void);
void   init_port(void);
void   init_sysconfig(void);
//flash.c
void   ErasePage(u8 page);
void   FlashWrite(u16 addr,u8 value);
void   SaveData(u8 page,u16 addr,u8 value);
void   SaveEventLog(u16  Event,u16 Data,u8  *Brief) reentrant;
void   FactorySet(void);

//driver.c
char   putchar (char ch);
void   UartSendStr(u8  *ptr,u8  n);
u8     Stringcmp(u8 *str1,u8 *str2);
void   n2s(u32 n,u8 *s);
u32    s2n(u8 *s);
u32    getn(u8 *ptr,u8 len,u8 m);
u8     getword(u8 *ptr,u8 *buf,u8 n);
#endif//#ifndef  __DRIVER_H 