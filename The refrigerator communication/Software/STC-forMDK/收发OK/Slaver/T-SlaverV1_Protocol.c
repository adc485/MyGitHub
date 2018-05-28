#include "T-SlaverV1.h"

unsigned char bSynWord;
unsigned char DataSize = 0;
unsigned char Check_Btye_Xor;
unsigned char Uart2_RX_State;
unsigned char PaketSize_PTC;


unsigned char Remaining_PAYG_Days[] = {0xC5, 0x6a, 0x29, 0x06, 0x05, 0xf4};
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Master_Uart_Process

  Description:    // 主机接收串口处理函数

  Calls:          // 

  Input:          // 

  Output:         // 
	
  Return:         // 

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/03/29
*************************************************/
void Master_Uart_Process(void)
{
	if(bSynWord == 0)
	{
		Uart2_Buffer[0] = Uart2_Buffer[1];
		Uart2_Buffer[1] = Uart2_Buffer[2];
		Uart2_Buffer[2] = S2BUF;
		 if( (Uart2_Buffer[0] == 0xc5) && (Uart2_Buffer[1] == 0x6a) && (Uart2_Buffer[2] == 0x29) )
		 {
				bSynWord = 1;
		 }
		 else
		 {

			}
	}
	else
	{
		Uart2_Buffer[DataSize+3] = S2BUF;
		PaketSize_PTC = Uart2_Buffer[3];
		DataSize++;
		if(DataSize >= PaketSize_PTC - 3)
		{				
			bSynWord = 0;
			DataSize = 0;
			Check_Btye_Xor = CRC8(Uart2_Buffer, PaketSize_PTC -1 );
			if(Uart2_Buffer[PaketSize_PTC - 1] == Check_Btye_Xor)
			{
				Uart2_RX_State = 1;
				U2R_OFF_IRQ;
			}
			else
			{
				Uart2_RX_State = 2;
			}
			
		}
	}
}
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Get_Remaining_Days获取CAMP剩余天数

  Description:    // 获取CAMP剩余天数

  Calls:          // 

  Input:          // num引导吗次数  timesec等待数据反馈多少秒

  Output:         // 
	
  Return:         // 返回剩余天数

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/17
*************************************************/
int Get_Remaining_Days(unsigned char num,unsigned char timesec)
{
	
	unsigned char i, j;
	int Remaining_Days;
	U2R_ON_IRQ;
	DATA_PIN_TX;
	Delay1ms();
	for(i = 0; i < num; i++)
	{
		Uart2Send(0xAA);
		Uart2Send(0xAA);
		Uart2Send(0xAA);
		Uart2Send(0xC0);
	}
	PrintString2_num(Remaining_PAYG_Days, 7);
	DATA_PIN_RX;
	Delay1ms();
	for(j = 0; j < timesec; j++)
	{
		Delay100ms();
	}
	if(Uart2_RX_State == 1)
	{
			Uart2_RX_State = 0;
			Remaining_Days = Uart2_Buffer[5] * 256 + Uart2_Buffer[6];
			return Remaining_Days;
	}
	else
	{
		return -1;
	}
}