#include "apply.h"

//********************************************************************
void  main(void)
{
	InitTask();
    while(1)
	  {
         FEED_WDG();
		 if(FirstTask != NULL)//����Ƿ�������
		 { 	  
			  LED_ON();
			  switch (FirstTask->Type)
			  {
			  	//case   0: break;//���������Ϊ��
				
				case   1: Shell(FirstTask->pData,FirstTask->Data); 
			   			  free(FirstTask->pData);
						  break;
				case   2:printf("Hello MsgOS\r\n");
						 AddDelayTask(1000*2,2 ,0,NULL);
				         break;
				default:SaveEventLog(5,FirstTask->Type,"error Task");break;
			  }
			  EA=0;
			  FirstTask->Type=0;	//�ͷ�����ɵ�����ṹ��
			  FirstTask=FirstTask->Next;
			  EA=1;
			  LED_OFF();
		  }
		 else
		 {
		   IdleTask();//��������
		 }

	  }
  
}