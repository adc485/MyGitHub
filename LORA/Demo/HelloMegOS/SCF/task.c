#include "system.h"

  struct  Task      *FirstTask;//头任务指针
  struct  Task      *LastTask; //尾任务指针
  struct  Task   xdata    TaskBuf[TASKS];//任务寄存数组

  struct  DelayTimer  xdata  delaytsak[TIMERS];
  struct  UsartData   usart   ={0};//硬件串口所用数据
  u16     delay_ms=0;//该全局变量会由定时器中断每1ms减一
//************************************************************************************
void   ISR_timer2(void)interrupt  INTERRUPT_TIMER2 
{
    u8	i;
   	u8   *pbuf;

	if(delay_ms) delay_ms--;
  	//用于延时任务********************************************************
   for(i=0;i<TIMERS;i++)
   {  if(delaytsak[i].Delay_ms)
   	  {
	    delaytsak[i].Delay_ms--;
		if(delaytsak[i].Delay_ms==0)
		{
		 AddTask(delaytsak[i].Type,delaytsak[i].Length,delaytsak[i].Data);
		}
      }
   }
	

   	//用于硬件串口接收数据包的结束
	      if(0!=usart.Time) usart.Time--;
	 else if(0!= usart.RXlenth)
	{	  
		 usart.RXbuf[usart.RXlenth]='\0';
	     AddTask(1,usart.RXlenth,usart.RXbuf);//调试指令	
	 	
		pbuf = malloc(UARTLENGTH);
		if(pbuf != NULL) {usart.RXbuf = pbuf;}
		usart.RXlenth=0;
	}

	TF2H=0;
//	TF2L=0;
}
void ISR_uart0(void) interrupt 4 
{ 
    if(RI0) 
	{ 
	   	if(usart.RXlenth<UARTLENGTH)	
		   usart.RXbuf[usart.RXlenth++]=SBUF0;
		usart.Time = 10;

	   RI0 = 0; 
	} 
} 
//添加任务函数*************************************************************************************************
u8   AddTask(u8 Type ,u8  Data,u8  *pData)reentrant
{
   u8   i;

	  EA =0;
	  for(i=0;i<TASKS;i++) //搜索空闲任务结构体
	  {
	     if(TaskBuf[i].Type==0)
		         break;
	  }
	
	  if(i<TASKS)  //
	 {
		  if(FirstTask==NULL)
		   { FirstTask =&TaskBuf[i];
		     LastTask  =&TaskBuf[i];
		    }
		  else
		  {	 LastTask->Next=&TaskBuf[i];
			 LastTask      =&TaskBuf[i];
		   }
	
		  LastTask->Type=Type;
	      LastTask->Data=Data;
		  LastTask->pData=pData;
		  LastTask->Next=NULL;
		  
	  }
	 
	  EA=1;
 	  return   0;
}//

 //添加延时任务***************************************************************************************  
u8    AddDelayTask(u32  t,u8  TaskType ,u8  Length,u8  *TaskData)
{
  u8    i;
	for(i=0;i<TIMERS;i++)
   {  if(delaytsak[i].Delay_ms ==0)
		break;
   }
   
    if(i<TIMERS)
	{ delaytsak[i].Delay_ms =t;
	  delaytsak[i].Type =TaskType;
	  delaytsak[i].Length =Length;
	  delaytsak[i].Data =TaskData;
	  return  1;
	}
	else
	{
	  SaveEventLog(5,TaskType,"delaytask overflow");
	  return  0;
	}
	 return  0;
}  

//重设已创建延时任务时间，为0则取消该任务**************************************************************************************
void   SetDelayTimer(u8 TaskType,u32 newtime)
{
	u8    i;	
	for(i=0;i<TIMERS;i++)
	{
	   if(delaytsak[i].Type==TaskType && delaytsak[i].Delay_ms!=0)
	   {   
		  if(0==newtime)
		  {delaytsak[i].Type =0;
		  }
		  delaytsak[i].Delay_ms =newtime;
	   }
	}
}


//初始化任务，在主循环之前，只执行一次****************************************************************************
void  InitTask(void)
{
	 u16  i;

     PCA0MD    &= ~0x40;	//关闭WDT
	
	 for(i=0;i<0x1000;*(u8 xdata *)i=0,i++);
	 init_sysclk();
	 init_timer2();
     init_port();
	 init_uart0();
	 init_sysconfig();
	 usart.RXbuf=malloc(UARTLENGTH);
	
	 if(SystemParameter.FSFlag ==-1) {FactorySet();}
	 SaveEventLog(1,RSTSRC,"system reset");
      
	 EA=1;
	 LED_OFF();
	 WDG_INIT();
	 AddTask(2 ,0,NULL);
}

//空闲任务，任务队列为空时执行，耗时要尽量的短**************************************************************************************************
 void  IdleTask(void)
 {									
   
 }








