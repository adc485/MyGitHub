#include "apply.h"
									    
#define   ShellcmdN     6

struct  Shellcmd  code	  ShellcmdList[ShellcmdN]={
	 { 0,"help",    "display command list"},
	 { 1,"reset",   "reset the systerm"},
	 { 2,"version", "display the version of systerm"},
	 { 3,"freset",  "Factory reset"},
	 { 4,"log",     "display the log list"},
	 { 5,"elog",    "erasure log"},
     };

u8    shell_getcmd(u8 *cmd,u8 length)
{
	 u8   i;
	 u8    string[11]={0};

	getword(cmd,string,1);
	length=length;
	if(*cmd>='0'&&*cmd<='9') 
	{  
	   return (s2n(string));
	}
	else
	{  	
		 for(i=0;i<ShellcmdN;i++)
		 {
			if(0==Stringcmp(string,ShellcmdList[i].Cmd))
			{ 
			 return  ShellcmdList[i].Num;
			}
		 }
	 }
	 return  0xff;
}

void   Shell(u8  *cmd,u8 length)
{
  
    u8   n;
	printf("\n\ryou input cmd is>>%s",cmd); //
	n=shell_getcmd(cmd,length);

		  switch (n)
		  {
			case  0: help();   break;
			case  1: SW_RESET();   break;		
			case  2: version();	   break;
			case  3: FactorySet();   break;
			case  4: log();   break;
			case  5: ErasePage(LOGPAGE);
					 ErasePage(LOGPAGE+1);
					 ErasePage(LOGPAGE+2);
					 ErasePage(LOGPAGE+3);
					 printf("\n\rerasure log success"); //
					break;

			//调用未用函数，防止连接警告
			case  254:                                   
					   SaveData(0,0,0); 
					   SetDelayTimer(0,0);
					 
					  break;
			default: printf("\n\rinput cmd unknown!\n\rinput \"help\"for command list."); break;	// 
		  }
	printf("\n\rplease input cmd>>"); //
	 
}



void   help(void)
{
	u8   i;

    printf("\r\nAll the shell command as follow：");
	printf("\r\nNum  Command     Brief");
	 for(i=0;i<ShellcmdN;i++)
	 {
	   printf("\r\n%03d  ",ShellcmdList[i].Num);
	   printf("%-10s  ",ShellcmdList[i].Cmd);
	   printf("%s",ShellcmdList[i].Brief);
	 }
	printf("\r\nyou can input <Command> or <Num> direct");
}


  void   version(void)
{
   printf("\r\n  project: Hello MsgOS -51");
   printf("\r\n software: V1.0");
   printf("\r\n      MCU: C8051F340");
   printf("\r\n   author: hou jin yu");
   printf("\r\n     time: 2013.12.29");
}
//日志显示**************************************************************************************************
void   log(void)
{
   struct  EventLog code  *plog=(struct  EventLog code *)(LOGPAGE*PAGESIZE);
   printf("\n\rNum   Event Data  Brief");
   	while(plog->Event != 0xffff)
   {
	 printf("\n\r%-5d %-5d %-5d %s",plog->Number,plog->Event,plog->Data,plog->Brief);
	 plog++;
   }
}









