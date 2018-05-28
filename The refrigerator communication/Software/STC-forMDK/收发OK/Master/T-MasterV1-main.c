#include "T-MasterV1.h"



extern unsigned char Check_Btye_Xor;
void T_Master_SYSInit(void)
{
	STCUart1Init(); //Chat to Camp
	STCUart2Init(); 
	/*设置为开漏模式*/
	P1M0 = 0xff;
	P1M1 = 0xff; //0xff 4302接收  0x00 4450发射
}

void main()//Camp C5,6A,29,06,05,f4
{
	unsigned i;
	T_Master_SYSInit();
	DATA_PIN_TX;
	PrintString1("STC8F2K32S4 Master For CAMP Test Prgramme!\r\n");
	PrintString2("STC8F2K32S4 Master For PTC Test Prgramme!\r\n"); 
	DATA_PIN_RX; 	
	while(1)
	{
		
		if(Uart2_RX_State == 1)
		{	
			Uart2_RX_State = 0;
			U2R_OFF_IRQ;
			U1R_ON_IRQ;
			DATA_PIN_TX;
					for(i = 0; i < 16; i++)
					UartSend(0x00);
					PrintString1_num(Uart2_Buffer, Uart2_Buffer[3]);						
					Delay20ms();
					Delay20ms();
				if(Uart1_RX_State == 1)
				{
					Uart1_RX_State = 0;
					DATA_PIN_TX;
					Delay1ms();
					Send_PREMABLE_CODE(3);				
					PrintString2_num(Uart1_Buffer,Uart1_Buffer[3]);
					Delay1ms();
					DATA_PIN_RX;
				}
				U2R_ON_IRQ;
				DATA_PIN_RX;
        Uart2_RX_State = 0;
	}

	}
}


