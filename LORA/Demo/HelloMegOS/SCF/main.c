#include "apply.h"

//********************************************************************
void  main(void)
{
	InitTask();
    while(1)
	  {
         FEED_WDG();
		 if(FirstTask != NULL)//检查是否有任务
		 { 	  
			  LED_ON();
			  switch (FirstTask->Type)
			  {
			  	//case   0: break;//此任务必须为空
				
				case   1: Shell(FirstTask->pData,FirstTask->Data); 
			   			  free(FirstTask->pData);
						  break;
				case   2:printf("Hello MsgOS\r\n");
						 AddDelayTask(1000*2,2 ,0,NULL);
				         break;
				default:SaveEventLog(5,FirstTask->Type,"error Task");break;
			  }
			  EA=0;
			  FirstTask->Type=0;	//释放已完成的任务结构体
			  FirstTask=FirstTask->Next;
			  EA=1;
			  LED_OFF();
		  }
		 else
		 {
		   IdleTask();//空闲任务
		 }

	  }
  
}