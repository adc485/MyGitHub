#include "T-SlaverV1.h"



extern unsigned char Check_Btye_Xor;
unsigned char text_one[40] = {0xAA, 0xAA, 0xAA, 0xC0, 0xAA, 0xAA, 0xAA, 
	0xc5, 0x6a, 0x29, 0x06, 0x05, 0xf4, 0xCF, 0xFF, 0xEA, 0xAA, 0xCE, 
	0xEE, 0x13, 0x44, 0xFE, 0xEF, 0x15, 0x51, 0x23,0x32, 0x12, 0x77, 
0xFE, 0x4E, 0xE5, 0x6E, 0x1E, 0xE7, 0xE2, 0xEA, 0xA1, 0x21, 0xFA
};
void T_Master_SYSInit(void)
{
	STCUart1Init(); //Chat to Camp
	STCUart2Init(); 
	/*设置为开漏模式*/
	P1M0 = 0xff;
	P1M1 = 0x00; 
}


void main(void)
{
	int i = 0;
	T_Master_SYSInit();
	PrintString1("STC8F2K32S4 Slaver Test Prgramme!\r\n");
	PrintString2("STC8F2K32S4 Slaver Test Prgramme!\r\n");  
	while(1)
	{
			i = Get_Remaining_Days(2,2);//C5 6A 29 08 05 48 04 3B   1096
			if (i > 0)
			{
					PrintString1("Open+++++++++++++++++++++++++\r\n");
					P30 = ~P30;
//									P31 = ~P31;
					PrintString1_num(Uart2_Buffer, Uart2_Buffer[3]);
					//打开冰箱
			}
			else
			{
				PrintString1("Close--------------------------\r\n"); //
			}
			Delay100ms();
	}
}
