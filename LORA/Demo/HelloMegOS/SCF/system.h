#ifndef  __SYSTEM_H  
#define  __SYSTEM_H 

//包含头文件*********************************************************************************************************** 
#include "driver.h"
//常数定义 **************************************************************************************************************
#define   TASKS         20	  //消息队列深度
#define	  DATAS	        20	  //动态内存块数
#define	  DLENGTH       64	  //动态内存块字节数

#define	  TIMERS	    (20)	  //延时任务数
//定义结构体*****************************************

struct  Task
	{
	        u8   Type ; //具体任务代号
		    u8   Data;  //有效数据长度
		    u8  *pData; //对应任务可能用到的数据首地址,
		struct   Task   *Next; //指向下一个任务
	};

struct  DelayTimer
	{
	    u32  Delay_ms;	 //延时计数
		u8   Type ;      //具体任务代号
		u8   Length;     //有效数据长度
		u8  *Data;       //对应任务可能用到的数据首地址,
	};

struct  Shellcmd//Shell指令
	{
     u16   Num;    //指令号
	 u8	 *Cmd;	   //指令
	 u8  *Brief;   //指令简要说明
	}; 

//全局变量声明*******************************************************************************************************************
extern  u16     delay_ms;//该全局变量会由定时器中断每1ms减一，用于任务记时
extern  struct  UsartData  usart;//硬件串口所用数据
extern  struct  Task      *FirstTask;//头任务指针
extern  struct  Task      *LastTask; //尾任务指针
//函数声明***************************************************************************************************************** 
//宏函数
#define   DELAY_MS(t)      {delay_ms=t;while(delay_ms); }
//main.c
u8    AddTask(u8 Type ,u8  Data,u8  *pData)reentrant;
void  InitTask(void);
void  IdleTask(void);
//system.c
void  Timer2_INT();// interrupt	K_T0 
u8    AddDelayTask(u32  t,u8  TaskType ,u8  Length,u8  *TaskData);
void  SetDelayTimer(u8 TaskType,u32 newtime);
void   ISR_timer0(void);// interrupt  1 ;


//memory.c
void  *malloc(u8 length) reentrant;
void   free(void *p);
//shell.c
void   Shell(u8  *cmd,u8 length);
void   help(void);
void   version(void);
void   log(void);
u8     shell_getcmd(u8 *cmd,u8 length);
#endif//#ifndef   __SYSTEM_H