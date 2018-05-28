#include "T-SlaverV1.h"

unsigned char bSynWord;
unsigned char DataSize = 0;
unsigned char Check_Btye_Xor;
unsigned char Uart2_RX_State;
unsigned char PaketSize_PTC;

unsigned char xdata mac_temp[27];
int Remaining_Days;

unsigned char code Remaining_PAYG_Days[] = {0xC5, 0x6a, 0x29, 0x06, 0x05, 0xf4};
unsigned char code Commond_PPID       [] = {0xC5, 0x6a, 0x29, 0x07, 0x08, 0x14, 0xcb};
unsigned char code Mac_Set_OK					[] = {0xaf, 0xaf, 0xaf, 0x06, 0x00, 0x6c};
unsigned char xdata Slaver_mac[27];
unsigned char xdata Master_mac[27];
unsigned char set_mac_flag;

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
				if((Uart2_Buffer[0] == 0xAF)&&(Uart2_Buffer[1] == 0xAF))//PPID SAVE MAC
				{
							set_mac_flag = 3;
							strncpy(mac_temp,Uart2_Buffer,27);
							mac_temp[0] = 0xc5;
							mac_temp[1] = 0x6a;
							mac_temp[2] = 0x29;
					    mac_temp[26] = CRC8(mac_temp , mac_temp[3] - 1);
							P30 =~ P30;
//					U2R_OFF_IRQ;
				}
				if( (Uart2_Buffer[0] == 0xc5) && (Uart2_Buffer[1] == 0x6a) && (Uart2_Buffer[2] == 0x29) )
				{
						if(Uart2_Buffer[4] == 0x05)//Remaining_Days
						{Uart2_RX_State = 1;}
						if(Uart2_Buffer[4] == 0x08) 
						{
							{Uart2_RX_State = 3;}
						}		
				}
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
	//Save Mac

	//send command Remaining_Days
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
				return 2;
			}

	else
	{
#ifdef MAC_PRINT		
		Slaver_Read_Mac(MAC_ADDR, Slaver_mac, 27);
		PrintString1_num(Slaver_mac, 27);
#else

#endif
		Debug_print("Communicate EEROR-0\r\n");
		return -1;
	}
	U2R_ON_IRQ;
	DATA_PIN_RX;
}
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Run()运行电器

  Description:    // 获取运行权限

  Calls:          // 

  Input:          // 

  Output:         // 
	
  Return:         // 返回剩余天数

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/19
*************************************************/
int Run()
{
	int temp;
	unsigned char Cycle_times = 3;
	for(Cycle_times = 3 ;Cycle_times < CYCLE_TIMES_MAX  ;Cycle_times++)
	{
		temp = Get_Remaining_Days(GUIDE_TIMES,Cycle_times);
		if(temp == 2)
		return 2;
		
	}
#ifdef MAC_PRINT	
	Slaver_Read_Mac(MAC_ADDR, Slaver_mac, 27);
  PrintString1_num(Slaver_mac, 27);
#else

#endif	
	Debug_print("Communicate EEROR-1\r\n"); 
	return -1;
}
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Slaver_Process处理通讯结果

  Description:    // 处理通讯结果

  Calls:          // 

  Input:          // days  CAMP剩余天数

  Output:         // 
	
  Return:         // NO

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/19
*************************************************/
void Slaver_Process(int days)
{
	
	unsigned char delays = 0;
		if( days == 2 )//成功得到充值天数
		{
			if(Remaining_Days > 0)
			{
#ifdef MAC_PRINT					
				Slaver_Read_Mac(MAC_ADDR, Slaver_mac, 27);
				PrintString1_num(Slaver_mac, 27);
#else

#endif
				TURN_ON_LOAD;
				Debug_print("Open+++ Day > 0\r\n");
			}
			else if(Remaining_Days == 0)
			{
				Debug_print("Open+++ Day == 0\r\n");
			}
			else if(Remaining_Days < 0)
			{
				UartSend(Uart2_Buffer[5]);
				UartSend(Uart2_Buffer[6]);
				Debug_print("Open+++ Day < 0\r\n");
			}
			else
			{
				Debug_print("ERROR-2\r\n");
			}
//			P30 = ~P30;
		}
		else
		{
#ifdef MAC_PRINT	
			Slaver_Read_Mac(MAC_ADDR, Slaver_mac, 27);
		  PrintString1_num(Slaver_mac, 27);
#else

#endif
			Debug_print("Communicate EEROR-2\r\n");	
		}
#ifndef DEVELOP_MODEL
			for(delays = 0; delays < SYS_SLEEP_TIME; delays++)
				Delay1000000ms();	
				
#else
		_nop_();


#endif

	_nop_();
	_nop_();
}
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Mac_process处理MAC

  Description:    // 处理通讯结果

  Calls:          // 

  Input:          // days  CAMP剩余天数

  Output:         // 
	
  Return:         // NO

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/25
*************************************************/
void Mac_process(unsigned char num)
{	
	unsigned char  k,i,j;
	
	//Master Mac recive

	//Save Mac
	if(set_mac_flag  == 3)
	{
			k = num;
		do{
				EA = 0;
				Slaver_Write_Mac(MAC_ADDR, mac_temp, 27);
				Slaver_Read_Mac(MAC_ADDR, Slaver_mac, 27);
				EA =1;
			if((Slaver_mac[0] == 0xc5) && (Slaver_mac[1] == 0x6a) && (Slaver_mac[2] == 0x29) && (Slaver_mac[24] == 0x3c) && (Slaver_mac[25] == 0x3c))
			{	
				U2R_OFF_IRQ;
				DATA_PIN_TX;
				set_mac_flag = 0;
				Debug_print("Mac Save OK -\r\n");
				PrintString1("Mac Save OK -\r\n");
				for (i = 0; i < 5; i++)
				{
					for(j = 0; j < 2; j++)
					{
						Uart2Send(0xAA);
						Uart2Send(0xAA);
						Uart2Send(0xAA);
						Uart2Send(0xC0);
					}
					PrintString2_num(Mac_Set_OK, 6);
					Delay1000ms();
				}
				break;
			}
			else
			{
				Debug_print("Mac ERROR - 0\r\n");
				PrintString1("Mac ERROR - 0\r\n");
			}
		}while(k --);
	}
}
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Achieve_master_mac

  Description:    // 上电获取Master Mac

  Calls:          // 

  Input:          // unsigned char delay_num 查询主机等待时间

  Output:         // 
	
  Return:         // 0 Sucess  0 faild

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/27
*************************************************/
unsigned char Achieve_master_mac(unsigned char delay_num)
{
	unsigned char k , j, i;
	//Initialization Master Mac0
	for (i = 0 ; i < 27 ;i++)
	{
		Master_mac[i] = 0xAA;
	}
	k = 0;
	do{
			U2R_ON_IRQ;
			DATA_PIN_TX;
			Delay1ms();
			for(i = 0; i < 2; i++)
			{
				Uart2Send(0xAA);
				Uart2Send(0xAA);
				Uart2Send(0xAA);
				Uart2Send(0xC0);
			}
			PrintString2_num(Commond_PPID, 8);
			DATA_PIN_RX;
			Delay1ms();
			for(j = 0; j < k + 1; j++)
			{
					Delay100ms();
			}
			if(Uart2_RX_State == 3)
			{
				strncpy (Master_mac, Uart2_Buffer, 27);
				PrintString1_num(Uart2_Buffer,27);
				Uart2_RX_State = 0;
				break;
			}
		}while(k ++ < delay_num);
		Slaver_Read_Mac(MAC_ADDR, Slaver_mac, 27);
		if(0 == strncmp(Slaver_mac,Master_mac,27))
		{
				PrintString1_num(Slaver_mac,27);
				PrintString1("Master Slaver Mac is Same\r\n");
			  return 0;
		}
		else
		{
				PrintString1_num(Slaver_mac,27);
				PrintString1("Master Slaver Mac is Difference\r\n");
				TURN_OFF_LOAD;
				return 1;
		}
		
}