#include "driver.h"
struct  FlashData  code  SystemParameter _at_ (STORPAGE*PAGESIZE);//flash����
//**********************************************************************************************************
void  ErasePage(u8 page)	
{
       EA=0;
	   FLKEY = 0xA5;
	   FLKEY = 0xF1;
       PSCTL = 0x03;//����FLASH�������� ����FLASHд
	   *(u8 xdata *)(page*PAGESIZE)=0xff;
	   PSCTL = 0x00;//
	   EA=1;
}
void   FlashWrite(u16 addr,u8 value)							 //FlashWrite() called by .lib
{
	 while(value!=*(u8 code *)addr)
	{
	   EA=0;
       PSCTL = 0x01;//����FLASH�������� ����FLASHд
	   FLKEY = 0xA5;
	   FLKEY = 0xF1;
	   *(u8 xdata *)addr=value;
	   PSCTL = 0x00;//
	   EA=1;
	}


}
//***************************************************************************************************
void  SaveData(u8 page,u16 addr,u8 value)
{
	u16   i;
	u16   dadd;//Ŀ���ַ��Դ��ַ
   	u8    buf[STORSIZE];
   
	
	dadd=page*PAGESIZE;
	if(value==((u8 code *)dadd)[addr])  return;

	//��������ҳ����������
   	for(i=0;i<STORSIZE;i++)
	{
	  buf[i]=((u8 code *)dadd)[i];
	}
	//��������ҳ
	ErasePage(page);
	//��������ҳ����������ҳ
	for(i=0;i<STORSIZE;i++)
	{
		if(addr==i)FlashWrite(dadd,value);
	    else FlashWrite(dadd,buf[i]);
		dadd++;	
	}
}
//�����¼���־*******************************************************************************************
void  SaveEventLog(u16  Event,u16 Data,u8  *Brief) reentrant
{
   u16   dadd;//Ŀ���ַ
   struct  EventLog    log;
   struct  EventLog code  *plog=(struct  EventLog code *)(LOGPAGE*PAGESIZE);
   u8   i;
 
	  for(i=0;plog->Event != 0xffff;i++,plog++);
	 
  	   log.Number= i;
	   log.Event = Event;
	   log.Data  = Data;
	   log.Brief = Brief;
	
	  
	   dadd=(i *sizeof(struct  EventLog))+(LOGPAGE*PAGESIZE);//Ŀ���ַ
	   for(i=0;i<sizeof(struct  EventLog);i++)
	   {
		 	FlashWrite(dadd+i,((u8 *)&log)[i]);
	   }

}//

////��������******************************************************************************
void   FactorySet(void)
{
    u8  i;	
	u16   dadd;//Ŀ���ַ

	ErasePage(STORPAGE);

	dadd=(STORPAGE*PAGESIZE);//Ŀ���ַ
	for(i=0;i<sizeof(struct  FlashData);i++)
	{
	   FlashWrite(dadd+i,0);
	}
}


