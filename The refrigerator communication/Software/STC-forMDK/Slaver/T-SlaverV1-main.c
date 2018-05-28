#include "T-SlaverV1.h"

sbit INT0 = 0xB2;

extern unsigned char Check_Btye_Xor;
unsigned char xdata tww[16];
void T_Master_SYSInit(void)
{
	TURN_OFF_LOAD;
	STCUart1Init(); //Chat to Camp
	STCUart2Init(); 
	/*设置为开漏模式*/
	P1M0 = 0xff;
	P1M1 = 0x00; 
	TURN_OFF_LOAD;
	//Slaver_Read_Mac();
	
	//INT0                              
}


void main(void)
{
	int delays;
	T_Master_SYSInit();
	P34 = 0;
	PrintString1("STC8F2K32S4 Slaver Test Prgramme!\r\n");
	PrintString2("STC8F2K32S4 Slaver Test Prgramme!\r\n");  
	while(1)
	{
			if(0 == Achieve_master_mac(10))
			{
				Slaver_Process(Run());
			}
			Mac_process(10);
#ifndef DEVELOP_MODEL
						U2R_ON_IRQ;
						DATA_PIN_RX;
			for(delays = 0; delays < SYS_SLEEP_TIME; delays++)
				Delay1000000ms();	
				
#else
		_nop_();


#endif
	}
}

	

