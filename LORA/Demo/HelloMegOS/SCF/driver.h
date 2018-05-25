#ifndef  __DRIVER_H  
#define  __DRIVER_H 

//包含头文件*********************************************************************************************************** 
#include <c8051f340.h> 
#include <intrins.h>
//#include <absacc.h>
//#include <stdlib.h>   
#include <stdio.h>    
//常数定义 **************************************************************************************************************

#ifndef NULL
  #define NULL ((void *) 0)
#endif


#define	  PAGESIZE		  (512) //页字节数0x200==512
#define	  LOCKPAGE	      (50)	 //0~LOCKPAGE的FLASH将被保护，不能再擦除和烧写
#define   STORPAGE		  (LOCKPAGE+1)	 //系统参量页
#define	  BUFPAGE	      (LOCKPAGE+2)	 //暂存页
#define	  LOGPAGE	      (LOCKPAGE+3)	 //日志页
#define   MAXLOGS		  (250)	 //最大日志数 
#define	  STORSIZE		  (10)	 //存储字节数

#define UARTLENGTH    64      //
//数据类型定义******************************************
typedef   unsigned       char   u8;
typedef   unsigned       int    u16;
typedef   unsigned       long   u32;
typedef     signed       char   s8;
typedef     signed       int    s16;
typedef     signed       long   s32;
typedef   enum {FALSE = 0, TRUE = !FALSE} bool;

//定义结构体*****************************************

struct  UsartData//用于USART接收数据包
	{
	 u8  State;   //USART接收状态标志 
     u8	 Time;    //USART接收计时
     u8	 RXlenth; //USART接收数据包长度
     u8	*RXbuf;	  //USART1 接收数据所用缓存数据空间的首地址
	}; 

struct  EventLog	    //事件日志
	{
		u16  Number;     //日志编号
		u16	 Event;      //事件编号
		u16  Data;	     //相关数据
		u8  *Brief;		 //内容简介
	};
struct  FlashData	  //各节点可修改数据，存于FLASH中
	{
		u32	 FSFlag;//是否为下载程序后第一次上电复位
		u8   LogAmount;     //日志数量 
	};
	
union  DataConvert	
{
   	u32   Reg32;
	u16   Reg16[2];
	u8    Reg8[4];
};	
	 
//引脚定义*******************************************************************************************
sbit        RXD=P0^5;	 //开漏输出
sbit        TXD=P0^4;	 //推挽输出				   
sbit        LED=P0^3;	 //推挽输出
sbit       BEEP=P1^6;	 //推挽输出


//全局变量声明*******************************************************************************************************************
extern  struct  FlashData  code  SystemParameter;//flash参量
//函数声明***************************************************************************************************************** 
//宏函数
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