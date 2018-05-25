#ifndef  __SYSTEM_H  
#define  __SYSTEM_H 

//����ͷ�ļ�*********************************************************************************************************** 
#include "driver.h"
//�������� **************************************************************************************************************
#define   TASKS         20	  //��Ϣ�������
#define	  DATAS	        20	  //��̬�ڴ����
#define	  DLENGTH       64	  //��̬�ڴ���ֽ���

#define	  TIMERS	    (20)	  //��ʱ������
//����ṹ��*****************************************

struct  Task
	{
	        u8   Type ; //�����������
		    u8   Data;  //��Ч���ݳ���
		    u8  *pData; //��Ӧ��������õ��������׵�ַ,
		struct   Task   *Next; //ָ����һ������
	};

struct  DelayTimer
	{
	    u32  Delay_ms;	 //��ʱ����
		u8   Type ;      //�����������
		u8   Length;     //��Ч���ݳ���
		u8  *Data;       //��Ӧ��������õ��������׵�ַ,
	};

struct  Shellcmd//Shellָ��
	{
     u16   Num;    //ָ���
	 u8	 *Cmd;	   //ָ��
	 u8  *Brief;   //ָ���Ҫ˵��
	}; 

//ȫ�ֱ�������*******************************************************************************************************************
extern  u16     delay_ms;//��ȫ�ֱ������ɶ�ʱ���ж�ÿ1ms��һ�����������ʱ
extern  struct  UsartData  usart;//Ӳ��������������
extern  struct  Task      *FirstTask;//ͷ����ָ��
extern  struct  Task      *LastTask; //β����ָ��
//��������***************************************************************************************************************** 
//�꺯��
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