#include "T-MasterV1.h"

unsigned char bSynWord;
unsigned char DataSize = 0;
unsigned char Check_Btye_Xor;
unsigned char Uart2_RX_State;
unsigned char Uart1_RX_State;
extern unsigned char PaketSize_PTC;

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
		}
	}
}
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Master_Uart_Process

  Description:    // 数据处理串口

  Calls:          // 

  Input:          // 

  Output:         // 
	
  Return:         // 

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/13
*************************************************/
void Master_Uart2_Process(void)
{
			if(bSynWord_MCU == 0)
			{ 
  			
				 Uart1_Buffer[0] = Uart1_Buffer[1];
				 Uart1_Buffer[1] = Uart1_Buffer[2];
			   Uart1_Buffer[2] = SBUF;
				if(Uart1_Buffer[0] == 0xc5 && Uart1_Buffer[1] == 0x6A && Uart1_Buffer[2] == 0x29)//
				{	
					bSynWord_MCU = 1;
				}
			}
			else
			{		
				
				Uart1_Buffer[DataSize_MCU+3] = SBUF;
				PaketSize_MCU = Uart1_Buffer[3];
						DataSize_MCU++;
				if(DataSize_MCU >= PaketSize_MCU - 3)
				{
					bSynWord_MCU = 0;
					DataSize_MCU = 0;
					Check_Btye_MCU = CRC8(Uart1_Buffer,PaketSize_MCU - 1);
					if(Uart1_Buffer[PaketSize_MCU - 1] == Check_Btye_MCU)
					{	
						P34 = ~P34;
						Uart1_RX_State = 1;
						U1R_OFF_IRQ;
					}
				}
			}
}
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Send_PREMABLE_CODE

  Description:    // 发送引导码

  Calls:          // 

  Input:          // unsigned char num 引导码循环次数

  Output:         // 
	
  Return:         // 

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/16
*************************************************/
void Send_PREMABLE_CODE(unsigned char num)
{
	unsigned char i;
	for(i = 0; i < num; i++)
	{
		Uart2Send(0xAA);
		Uart2Send(0xAA);
		Uart2Send(0xAA);
		Uart2Send(0xC0);
	}
}