#include "T-MasterV1.h"

unsigned char bSynWord;
unsigned char DataSize = 0;
unsigned char Check_Btye_Xor;
unsigned char Uart2_RX_State;
unsigned char Uart1_RX_State;
extern unsigned char PaketSize_PTC;

unsigned char Set_mac;
unsigned char code Find_PPID[8] = {0xc5, 0x6a, 0x29, 0x07, 0x08, 0x14, 0xcb};
unsigned char xdata Sava_Mac_Msg[27];

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
		 if( (Uart2_Buffer[0] == 0xAF) && (Uart2_Buffer[1] == 0xAF) && (Uart2_Buffer[2] == 0xAF) )
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
				if( (Uart2_Buffer[0] == 0xAF) && (Uart2_Buffer[1] == 0xAF) && (Uart2_Buffer[2] == 0xAF) )
				 {
	
						Uart2_RX_State = 9;
				 }
				else
				{
					Uart2_RX_State = 1;
				}
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
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Master_Process

  Description:    // 主机处理

  Calls:          // 

  Input:          // unsigned char num 引导码循环次数

  Output:         // 
	
  Return:         // 

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/24
*************************************************/
void Master_Process(unsigned char num)
{
	unsigned char i;
	 if(Uart2_RX_State == 1)
		{	
//			P30 = 1;
			P34 = 0;
			Uart2_RX_State = 0;
			U2R_OFF_IRQ;
			U1R_ON_IRQ;
			DATA_PIN_TX;
					for(i = 0; i < 16; i++)
					UartSend(0x00);
					PrintString1_num(Uart2_Buffer, Uart2_Buffer[3]);						
					Delay20ms();
					Delay20ms();
								Delay20ms();
								Delay20ms();

				if(Uart1_RX_State == 1)
				{
					Uart1_RX_State = 0;
					DATA_PIN_TX;
					Delay1ms();
					Send_PREMABLE_CODE(num);				
					PrintString2_num(Uart1_Buffer,Uart1_Buffer[3]);
					Delay1ms();
					DATA_PIN_RX;
				}
				U2R_ON_IRQ;
				DATA_PIN_RX;
        Uart2_RX_State = 0;
		}
		if(Uart2_RX_State == 9)
		{
			P34 = 1;
			Uart2_RX_State = 0;
			U2R_ON_IRQ;
			DATA_PIN_RX;
		}
		if(Set_mac == 2)
		{
			Set_mac = 0;
			i = 0;
			U2R_OFF_IRQ;
			DATA_PIN_TX;
			do{
				
					SET_MAC_LED = ~SET_MAC_LED;	
					Send_PREMABLE_CODE(num);				
					PrintString2_num(Sava_Mac_Msg,27);	
					Delay20ms();					
					if(P32 == 1)//松手
					{
						DATA_PIN_RX;
						U2R_ON_IRQ;
						SET_MAC_LED = 1;
						break;
					}
				}while(P32 == 0);
		}
}
//0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 
//C5 6A 29 1B 08 14 30 33 41 48 31 38 30 32 30 30 30 30 30 32 3C 3C 3C 3C 3C 3C A0 
void Find_mac(unsigned char k)
{
	unsigned char i,j,delay;
	for( j = 0; j < k; j++)
	{
				for(i = 0; i < 16; i++)
				UartSend(0x00);
				PrintString1_num(Find_PPID, 7);		
				for( delay = 0; delay < j + 2; delay++)
				{
					Delay20ms();
				}
				if((Uart1_RX_State == 1) && (Uart1_Buffer[25] == 0x3c))
				{
					Sava_Mac_Msg[0] = 0xAF;
					Sava_Mac_Msg[1] = 0xAF;
					Sava_Mac_Msg[2] = 0xAF;
					for( i = 3; i < 26; i++ )
					{
						Sava_Mac_Msg[i] = Uart1_Buffer[i];
					}
					Sava_Mac_Msg[26] = CRC8(Sava_Mac_Msg, Sava_Mac_Msg[3] - 1 );
					SET_MAC_LED = 0;
					Uart1_RX_State = 0;
						break;
				}
	}
	SET_MAC_LED = 1;
	Debug_print("Find_PPID_NO_ANSWER !\r\n");
	
}