#include "system.h"
u8    xdata    databuf[DATAS][DLENGTH];
u8    xdata    databufflag[DATAS]={0};
//动态分配内存*******************************************************************************************
void *malloc(u8 length) reentrant
 {
	 u8    i;

	length=length;
	EA=0;

	  for(i=0;i<DATAS;i++) 
	  {
        if(databufflag[i]==0)
		{	
		    EA=1; 
		   	return   (&databuf[i][0]);
		}
	  }
	  SaveEventLog(5,length,"malloc failed");
     EA=1; 
	 return   NULL;
 }
//释放内存*************************************************************************************************************
void  free(void *p)
{
    u8    i;

  if(p==NULL)	return;
  for(i=0;i<DATAS;i++) 
  {
    if(p==(&databuf[i][0]))
	{
	  databufflag[i]=0;
	  break;
	}
  }
}