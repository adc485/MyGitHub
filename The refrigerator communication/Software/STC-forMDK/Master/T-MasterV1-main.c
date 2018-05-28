#include "T-MasterV1.h"

sbit INT0 = 0xB2;

extern unsigned char Check_Btye_Xor;
void T_Master_SYSInit(void)
{
	STCUart1Init(); //Chat to Camp
	STCUart2Init(); 
	/*设置为开漏模式*/
	P1M0 = 0xff;
	P1M1 = 0xff; //0xff 4302接收  0x00 4450发射
	
	//INT0
	 IT0 = 0;                                  
   EX0 = 1;  
	
	//PPID
	Find_mac(30);
}

void main()//Camp C5,6A,29,06,05,f4
{
	//Master ok;
	T_Master_SYSInit();
	DATA_PIN_TX;
	PrintString1("STC8F2K32S4 Master For CAMP Test Prgramme!\r\n");
	PrintString2("STC8F2K32S4 Master For PTC Test Prgramme!\r\n"); 
	DATA_PIN_RX; 	
	ENABLE_RX;
	P34 = 0;
	//ENABLE USB 
//	P3M0 = 0xFF;                                //??P0.0~P0.7??????
//  P3M1 = 0xFF;
	//ENABLE USB 
	while(1)
	{
		Master_Process(2);
	}
	//Test
//	  P3M0 = 0xFF;                                //??P0.0~P0.7??????
//    P3M1 = 0xFF;
//	while(1);
}
void INT0_Isr() interrupt 0 using 1
{
    if (INT0)                                
    {
			Delay200ms();
			if(P32 == 1)
        Set_mac = 1;                          
    }
    else
    {
			Delay1000ms();
			if(P32 == 0)
			{
        Set_mac = 2;     
				
			}				
    }
}


