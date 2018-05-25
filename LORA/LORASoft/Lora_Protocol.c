#include "Lora.h"
unsigned char bSynWord;
unsigned char DataSize = 0;
unsigned char PaketSize;
unsigned char Lora_Uart_State;
unsigned char Check_Btye;
unsigned char temp1;

unsigned char bSynWord_MCU;
unsigned char DataSize_MCU;
unsigned char PaketSize_MCU;
unsigned char Check_Btye_MCU;
unsigned char MCU_Uart_State;
unsigned char xdata TX_buf[128];
unsigned char xdata TX_buf2[128];
unsigned char xdata command[23];
unsigned char info_num;   //查询信息条数


typedef struct Oves_cmd
{
		unsigned char PPID[13];
		unsigned char OPID[13];
};


unsigned char code crc_array[256] = {
   0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83,
   0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41, 
   0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e,
   0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc, 
   0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0,
   0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62, 
   0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d,
   0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
   0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5, 
   0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
   0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58,
   0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
   0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6, 
   0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24, 
   0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b,
   0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9, 
   0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f, 
   0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
   0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92,
   0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50, 
   0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c, 
   0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee, 
   0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1, 
   0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73, 
   0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49,
   0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
   0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4,
   0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16, 
   0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a, 
   0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8, 
   0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7,
   0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35,
};
void MCU_Uart_Process(void)
{
	if(bSynWord_MCU == 0)
	{
		buffer[0] = buffer[1];
		buffer[1] = buffer[2];
		buffer[2] = SBUF;
		if(buffer[0] == 0xc5 && buffer[1] == 0x6a && buffer[2] == 0x29)//Lora终端有数据传送过来
		{
			bSynWord_MCU = 1;
		}
	}
	else
	{

		buffer[DataSize_MCU+3] = SBUF;
		PaketSize_MCU = buffer[3];
		DataSize_MCU++;
		if(DataSize_MCU == PaketSize_MCU - 3)
		{
			bSynWord_MCU = 0;
			DataSize_MCU = 0;
			Check_Btye_MCU = CRC8(buffer,PaketSize_MCU - 1);
			if(buffer[PaketSize_MCU - 1] == Check_Btye_MCU)
			{
				MCU_Uart_State = 1;
				SYS_STATE = 0;           //系统收发正常
			}
		}
	}
}
void Lora_Uart_Process(void)
{
	if(bSynWord == 0)
	{	
		buffer2[0] = buffer2[1];
		buffer2[1] = buffer2[2];
		buffer2[2] = S2BUF;
		if(buffer2[0] == 0xaf && buffer2[1] == 0x00 && buffer2[2] == 0x00)//Lora终端有数据传送过来
		{
			bSynWord = 1;
		}
	}
	else
	{
        buffer2[DataSize+3] = S2BUF;
				DataSize++;
				if(DataSize == 8)
				PaketSize = buffer2[10];
         if(DataSize == PaketSize +10)
         {
          bSynWord = 0;
          DataSize = 0;	
					Check_Btye = GetCheckSum_Xor(buffer2,PaketSize + 10);					 
					if(buffer2[PaketSize+11] == Check_Btye)
					{
							Lora_Uart_State = 1;
					}
					else
					{
						P30 = 1;
					}

         }

	}		
}
void Hand_PAYG()
{
	unsigned char i = 0;
	for(i = 0; i < 16; i++)
	UartSend(0x00);
	UartSend(0xc5);
	UartSend(0x6a);
	UartSend(0x29);
	UartSend(0x07);
	UartSend(0x04);
	UartSend(0x01);
	UartSend(0x24);
}
void Lora_Buffer_Analysis()
{
	unsigned char i = 0,j = 0,k = 0,tx_num = 0;
	unsigned char *dest,*src;
	if(buffer2[14] == 0x0E && buffer2[15] == 0xFA)//这是充值命令
	{
		MCU_Uart_State = 0;
		REN = 0;//关闭串口接收中断
		for(i = 0; i < 16; i++)
		{
			UartSend(0x00);
		}
		UartSend(buffer2[11]);
		UartSend(buffer2[12]);
		UartSend(buffer2[13]);
		UartSend(buffer2[14]);
		UartSend(buffer2[15]);
		UartSend(buffer2[16]);
		UartSend(buffer2[17]);
		UartSend(buffer2[18]);
		UartSend(buffer2[19]);
		UartSend(buffer2[20]);
		UartSend(buffer2[21]);
		UartSend(buffer2[22]);
		UartSend(buffer2[23]);
		UartSend(buffer2[24]);
		REN = 1;//打开串口接收中断
		SYS_STATE = 2;
		SYS_TIMER_START;
		do
		{
			//			P30 = ~P30;
			if(MCU_Uart_State ==1)//有充值回复
			{				
							MCU_Uart_State = 0;
							dest = TX_buf2;
							*dest++ = 0xaf;
							*dest++ = 0x00;
							*dest++ = 0x00;
							*dest++ = 0x00;
							*dest++ = 0x00;
							*dest++ = 0x00;
							*dest++ = 0x00;
							*dest++ = 0x02;
							*dest++ = 0x14;
							*dest++ = 0x11;
							*dest++ = buffer[3];					
							for(i = 0; i < buffer[3] ; i++)
							{
								*dest++ = buffer[i];
							}
							*dest++ = GetCheckSum_Xor(TX_buf2, buffer[3] +10);
							*dest++ = 0x3C;
							for( i = 0; i < buffer[3]+ 13 ; i++)
							{
								Uart2Send(TX_buf2[i]);
							}

//					if(buffer[4] == 0xfa && buffer[5] == 0x0a)
//					{
//							//充值成功
//							dest = TX_buf2;
//							*dest++ = 0xaf;
//							*dest++ = 0x00;
//							*dest++ = 0x00;
//							*dest++ = 0x00;
//							*dest++ = 0x00;
//							*dest++ = 0x00;
//							*dest++ = 0x00;
//							*dest++ = 0x02;
//							*dest++ = 0x12;
//							*dest++ = 0x11;
//							*dest++ = buffer[3];					
//							for(i = 0; i < buffer[3] ; i++)
//							{
//								*dest++ = buffer[i];
//							}
//							*dest++ = GetCheckSum_Xor(TX_buf2, tx_num +10);
//							*dest++ = 0x3C;
//							for( i = 0; i < tx_num + 13 ; i++)
//							{
//								Uart2Send(TX_buf2[i]);
//							}
//					}
//					else if(buffer[4] == 0xfa && buffer[5] == 0xa0)
//					{
//							//充值失败
//													dest = TX_buf2;
//							*dest++ = 0xaf;
//							*dest++ = 0x00;
//							*dest++ = 0x00;
//							*dest++ = 0x00;
//							*dest++ = 0x00;
//							*dest++ = 0x00;
//							*dest++ = 0x00;
//							*dest++ = 0x02;
//							*dest++ = 0x12;
//							*dest++ = 0x11;
//							*dest++ = buffer[3];					
//							for(i = 0; i < buffer[3] ; i++)
//							{
//								*dest++ = buffer[i];
//							}
//							*dest++ = GetCheckSum_Xor(TX_buf2, tx_num +10);
//							*dest++ = 0x3C;
//							for( i = 0; i < tx_num + 13 ; i++)
//							{
//								Uart2Send(TX_buf2[i]);
//							}
//					}
//					else if(buffer[4] == 0xff && buffer[5] == 0xee)
//					{
//							//充值密码已使用
//						P31 = 0 ;
//							dest = TX_buf2;
//							*dest++ = 0xaf;
//							*dest++ = 0x00;
//							*dest++ = 0x00;
//							*dest++ = 0x00;
//							*dest++ = 0x00;
//							*dest++ = 0x00;
//							*dest++ = 0x00;
//							*dest++ = 0x02;
//							*dest++ = 0x12;
//							*dest++ = 0x11;
//							*dest++ = buffer[3];					
//							for(i = 0; i < buffer[3] ; i++)
//							{
//								*dest++ = buffer[i];
//							}
//							*dest++ = GetCheckSum_Xor(TX_buf2, tx_num +10);
//							*dest++ = 0x3C;
//							for( i = 0; i < tx_num + 13 ; i++)
//							{
//								Uart2Send(TX_buf2[i]);
//							}
//					}
					break;
			}
			Delay1S();
			k++;

		}while( k < RECHARGETIME);
	}
	else
	{
			tx_num  = 0;
		  dest = TX_buf;
			info_num = 0;
			for(; j < 23; j++)command[j] = 0x00;//格式化命令缓冲区
			for(j = 0; j < PaketSize + 7;j++)
			{
				if(buffer2[j] == 0x3A && buffer2[j+1] == 0xC5 && buffer2[j+2] == 0x6A && buffer2[j+3] == 0x29)
				{		
					command[info_num++] = buffer2[j+5];
					
					switch(buffer2[j+5])
					{
						case 0x00:
						{
							if(buffer2[j+6] == 0x08) //查询电池包温度
							{
									k = 0;
									MCU_Uart_State = 0;//串口没有数据
								do{
										for(i = 0; i < 16; i++)
										UartSend(0x00);
										
										UartSend(0xc5);
										UartSend(0x6a);
										UartSend(0x29);
										UartSend(0x08);
										UartSend(0x00);
										UartSend(0x08);
										UartSend(0x02);
										UartSend(0x48);									
										k++;
									 Delay20ms();
									if(MCU_Uart_State == 1)
									{
										src = buffer;
										*dest++ = 0x3A;tx_num ++;
										for( i = 0; i < buffer[3]; i++)
										{
											*dest++ = *src++;
											 tx_num ++;
										}
										Delay20ms();
										break;
									}
									Delay20ms();
									}while( k < NO_ASK_NUM );
							}
							else if(buffer2[j+6] == 0x09)//读取电池包电压
							{
									k = 0;
									MCU_Uart_State = 0;//串口没有数据
								do{
										for(i = 0; i < 16; i++)
										UartSend(0x00);
										
										UartSend(0xc5);
										UartSend(0x6a);
										UartSend(0x29);
										UartSend(0x08);
										UartSend(0x00);
										UartSend(0x09);
										UartSend(0x02);
										UartSend(0x8c);									
										k++;
									 Delay20ms();
									if(MCU_Uart_State == 1)
									{
										src = buffer;
										*dest++ = 0x3A;tx_num ++;
										for( i = 0; i < buffer[3]; i++)
										{
											*dest++ = *src++;
											 tx_num ++;
										}
										Delay20ms();
										break;
									}
									Delay20ms();
									}while( k < NO_ASK_NUM );
							}
							else if(buffer2[j+6] == 0x0a)
							{
									k = 0;
									MCU_Uart_State = 0;//串口没有数据
								do{
										for(i = 0; i < 16; i++)
										UartSend(0x00);
										
										UartSend(0xc5);
										UartSend(0x6a);
										UartSend(0x29);
										UartSend(0x08);
										UartSend(0x00);
										UartSend(0x0a);
										UartSend(0x02);
										UartSend(0xd9);									
										k++;
									 Delay20ms();
									if(MCU_Uart_State == 1)
									{
										src = buffer;
										*dest++ = 0x3A;tx_num ++;
										for( i = 0; i < buffer[3]; i++)
										{
											*dest++ = *src++;
											 tx_num ++;
										}
										Delay20ms();
										break;
									}
									Delay20ms();
									}while( k < NO_ASK_NUM );
							}
							else if(buffer2[j+6] == 0x3c)
							{
									k = 0;
									MCU_Uart_State = 0;//串口没有数据
								do{
										for(i = 0; i < 16; i++)
										UartSend(0x00);
										
										UartSend(0xc5);
										UartSend(0x6a);
										UartSend(0x29);
										UartSend(0x08);
										UartSend(0x00);
										UartSend(0x3c);
										UartSend(0x02);
										UartSend(0x5e);									
										k++;
									 Delay20ms();
									if(MCU_Uart_State == 1)
									{
										src = buffer;
										*dest++ = 0x3A;tx_num ++;
										for( i = 0; i < buffer[3]; i++)
										{
											*dest++ = *src++;
											 tx_num ++;
										}
										Delay20ms();
										break;
									}
									Delay20ms();
									}while( k < NO_ASK_NUM );
							}
							else if(buffer2[j+6] == 0x3d)
							{
									k = 0;
									MCU_Uart_State = 0;//串口没有数据
								do{
										for(i = 0; i < 16; i++)
										UartSend(0x00);
										
										UartSend(0xc5);
										UartSend(0x6a);
										UartSend(0x29);
										UartSend(0x08);
										UartSend(0x00);
										UartSend(0x3d);
										UartSend(0x02);
										UartSend(0x9a);									
										k++;
									 Delay20ms();
									if(MCU_Uart_State == 1)
									{
										src = buffer;
										*dest++ = 0x3A;tx_num ++;
										for( i = 0; i < buffer[3]; i++)
										{
											*dest++ = *src++;
											 tx_num ++;
										}
										Delay20ms();
										break;
									}
									Delay20ms();
									}while( k < NO_ASK_NUM );
							}
							else if(buffer2[j+6] == 0x3e)
							{
									k = 0;
									MCU_Uart_State = 0;//串口没有数据
								do{
										for(i = 0; i < 16; i++)
										UartSend(0x00);
										
										UartSend(0xc5);
										UartSend(0x6a);
										UartSend(0x29);
										UartSend(0x08);
										UartSend(0x00);
										UartSend(0x3e);
										UartSend(0x02);
										UartSend(0xcf);									
										k++;
									 Delay20ms();
									if(MCU_Uart_State == 1)
									{
										src = buffer;
										*dest++ = 0x3A;tx_num ++;
										for( i = 0; i < buffer[3]; i++)
										{
											*dest++ = *src++;
											 tx_num ++;
										}
										Delay20ms();
										break;
									}
									Delay20ms();
									}while( k < NO_ASK_NUM );
							}
							else if(buffer2[j+6] == 0x3f)
							{
									k = 0;
									MCU_Uart_State = 0;//串口没有数据
								do{
										for(i = 0; i < 16; i++)
										UartSend(0x00);
										
										UartSend(0xc5);
										UartSend(0x6a);
										UartSend(0x29);
										UartSend(0x08);
										UartSend(0x00);
										UartSend(0x3f);
										UartSend(0x02);
										UartSend(0x0b);									
										k++;
									 Delay20ms();
									if(MCU_Uart_State == 1)
									{
										src = buffer;
										*dest++ = 0x3A;tx_num ++;
										for( i = 0; i < buffer[3]; i++)
										{
											*dest++ = *src++;
											 tx_num ++;
										}
										Delay20ms();
										break;
									}
									Delay20ms();
									}while( k < NO_ASK_NUM );
							}
						}break;
						case 0x01:
						{
							k = 0;
							MCU_Uart_State = 0;//串口没有数据
						do{
								for(i = 0; i < 16; i++)
								UartSend(0x00);
								
								UartSend(0xc5);
								UartSend(0x6a);
								UartSend(0x29);
								UartSend(0x07);
								UartSend(0x01);
								UartSend(0x0E);
								UartSend(0x9A);
							  k++;
							 Delay20ms();
							if(MCU_Uart_State == 1)
							{
								src = buffer;
								*dest++ = 0x3A;tx_num ++;
								for( i = 0; i < buffer[3]; i++)
								{
									*dest++ = *src++;
									 tx_num ++;
								}
								Delay20ms();
								break;
							}
							Delay20ms();
							}while( k < NO_ASK_NUM );
						}break;
						case 0x05:
						{ 
							k = 0;
							MCU_Uart_State = 0;
							do{
							for(i = 0; i < 16; i++)
							UartSend(0x00);
							
							UartSend(0xc5);
							UartSend(0x6a);
							UartSend(0x29);
							UartSend(0x06);
							UartSend(0x05);
							UartSend(0xf4);
							Delay20ms();
							Delay20ms();
							if(MCU_Uart_State == 1)
							{
								
							 	src = buffer;
								*dest++ = 0x3A;tx_num ++;
								for( i = 0; i < buffer[3]; i++)
								{
									*dest++ = *src++;
									 tx_num ++;
								}
								Delay20ms();
								break;
							}
							Delay20ms();
							k++;
						}while(k < NO_ASK_NUM);
						}break;
						case 0x06:
						{ 
							k = 0;
							MCU_Uart_State = 0;
							do{
							for(i = 0; i < 16; i++)
							UartSend(0x00);
							
							UartSend(0xc5);
							UartSend(0x6a);
							UartSend(0x29);
							UartSend(0x06);
							UartSend(0x06);
							UartSend(0x16);
							Delay20ms();
							Delay20ms();
							if(MCU_Uart_State == 1)
							{
							 	src = buffer;
								*dest++ = 0x3A;tx_num ++;
								for( i = 0; i < buffer[3]; i++)
								{
									*dest++ = *src++;
									 tx_num ++;
								}
								Delay20ms();
								break;
							}
							Delay20ms();
							k++;
						}while(k < NO_ASK_NUM);
						}break;						
						case 0x07:
						{
							k = 0;
							MCU_Uart_State = 0;
							do{
							for(i = 0; i < 16; i++)
							UartSend(0x00);
							
							UartSend(0xc5);
							UartSend(0x6a);
							UartSend(0x29);
							UartSend(0x06);
							UartSend(0x07);
							UartSend(0x48);
							Delay20ms();
							if(MCU_Uart_State == 1)
							{
									src = buffer;
									*dest++ = 0x3A;tx_num ++;
									for( i = 0; i < buffer[3]; i++)
									{
										*dest++ = *src++;
										 tx_num ++;
									}
								Delay20ms();
								break;
							}
							Delay20ms();
							k++;
						}while(k < NO_ASK_NUM);
						}break;
						case 0x08:
						{
							k = 0;
							MCU_Uart_State = 0;
							do{
							for(i = 0; i < 16; i++)
							UartSend(0x00);
							
							UartSend(0xc5);
							UartSend(0x6a);
							UartSend(0x29);
							UartSend(0x07);
							UartSend(0x08);
							UartSend(0x14);
							UartSend(0xcb);
							Delay20ms();
							if(MCU_Uart_State == 1)
							{
									src = buffer;
									*dest++ = 0x3A;tx_num ++;
									for( i = 0; i < buffer[3]; i++)
									{
										*dest++ = *src++;
										 tx_num ++;
									}
								break;
							}
							k++;
						}while(k < NO_ASK_NUM);
						}break;
						case 0x09:
						{
							k = 0;
							MCU_Uart_State = 0;
							do{
							for(i = 0; i < 16; i++)
							UartSend(0x00);
							
							UartSend(0xc5);
							UartSend(0x6a);
							UartSend(0x29);
							UartSend(0x06);
							UartSend(0x09);
							UartSend(0x57);
							Delay20ms();
							if(MCU_Uart_State == 1)
							{
									src = buffer;
									*dest++ = 0x3A;tx_num ++;
									for( i = 0; i < buffer[3]; i++)
									{
										*dest++ = *src++;
										 tx_num ++;
									}
								break;
							}
							k++;
						}while(k < NO_ASK_NUM);
						}break;
						case 0x0a:
						{
							k = 0;
							MCU_Uart_State = 0;
							do{
							for(i = 0; i < 16; i++)
							UartSend(0x00);
							
							UartSend(0xc5);
							UartSend(0x6a);
							UartSend(0x29);
							UartSend(0x06);
							UartSend(0x0a);
							UartSend(0xb5);
							Delay20ms();
							if(MCU_Uart_State == 1)
							{
								if(buffer[3] == 0x08 && buffer[4] == 0x0a)
								{						
									src = buffer;
									*dest++ = 0x3A;tx_num ++;
									for( i = 0; i < buffer[3]; i++)
									{
										*dest++ = *src++;
										 tx_num ++;
									}

								}
								break;
							}
							k++;
						}while(k < NO_ASK_NUM);
						}break;
						case 0x0b:
						{
							k = 0;
							MCU_Uart_State = 0;
							do{
							for(i = 0; i < 16; i++)
							UartSend(0x00);
							
							UartSend(0xc5);
							UartSend(0x6a);
							UartSend(0x29);
							UartSend(0x06);
							UartSend(0x0b);
							UartSend(0xeb);
							Delay20ms();
							if(MCU_Uart_State == 1)
							{
								if(buffer[3] == 0x08 && buffer[4] == 0x0b)
								{
									src = buffer;
									*dest++ = 0x3A;tx_num ++;
									for( i = 0; i < buffer[3]; i++)
									{
										*dest++ = *src++;
										 tx_num ++;
									}
								}
								break;
							}
							k++;
						}while(k < NO_ASK_NUM);
						}break;
						case 0x0c: //剩余容量
						{
							k = 0;
							MCU_Uart_State = 0;
							do{
							for(i = 0; i < 16; i++)
							UartSend(0x00);
							
							UartSend(0xc5);
							UartSend(0x6a);
							UartSend(0x29);
							UartSend(0x06);
							UartSend(0x0c);
							UartSend(0x68);
							Delay20ms();
							if(MCU_Uart_State == 1)
							{
								if(buffer[3] == 0x08 && buffer[4] == 0x0c)
								{
									src = buffer;
									*dest++ = 0x3A;tx_num ++;
									for( i = 0; i < buffer[3]; i++)
									{
										*dest++ = *src++;
										 tx_num ++;
									}
								}
								break;
							}
							k++;
						}while(k < NO_ASK_NUM);
						}break;
						case 0x0d:
						{
							k = 0;
							MCU_Uart_State = 0;
							do{
							for(i = 0; i < 16; i++)
							UartSend(0x00);
							
							UartSend(0xc5);
							UartSend(0x6a);
							UartSend(0x29);
							UartSend(0x06);
							UartSend(0x0d);
							UartSend(0x36);
							Delay20ms();
								Delay20ms();
							if(MCU_Uart_State == 1)
							{
								if(buffer[3] == 0x08 && buffer[4] == 0x0d)
								{
									src = buffer;
									*dest++ = 0x3A;tx_num ++;
									for( i = 0; i < buffer[3]; i++)
									{
										*dest++ = *src++;
										 tx_num ++;
									}
								}
								break;
							}
						k++;
						}while(k < NO_ASK_NUM);
						}break;
						case 0x0e: //读取设备满足容量 FCC
						{
							k = 0;
							MCU_Uart_State = 0;
							do{
							for(i = 0; i < 16; i++)
							UartSend(0x00);
							
							UartSend(0xc5);
							UartSend(0x6a);
							UartSend(0x29);
							UartSend(0x06);
							UartSend(0x0e);
							UartSend(0xd4);
							Delay20ms();
							if(MCU_Uart_State == 1)
							{
								if(buffer[3] == 0x08 && buffer[4] == 0x0e)
								{
									src = buffer;
									*dest++ = 0x3A;tx_num ++;
									for( i = 0; i < buffer[3]; i++)
									{
										*dest++ = *src++;
										 tx_num ++;
									}
								}
								break;
							}
						k++;
						}while(k < NO_ASK_NUM);
						}break;
						case 0x0f://读取设备累计输出电量
						{
							k = 0;
							MCU_Uart_State = 0;
							do{
							for(i = 0; i < 16; i++)
							UartSend(0x00);
							
							UartSend(0xc5);
							UartSend(0x6a);
							UartSend(0x29);
							UartSend(0x06);
							UartSend(0x0f);
							UartSend(0x8a);
							Delay20ms();
							if(MCU_Uart_State == 1)
							{
								if(buffer[3] == 0x08 && buffer[4] == 0x0f)
								{
									src = buffer;
									*dest++ = 0x3A;tx_num ++;
									for( i = 0; i < buffer[3]; i++)
									{
										*dest++ = *src++;
										 tx_num ++;
									}
								}
								break;
							}
						k++;
						}while(k < NO_ASK_NUM);
						}break;
						case 0x10://读取设备循次数
						{
							k = 0;
							MCU_Uart_State = 0;
							do{
							for(i = 0; i < 16; i++)
							UartSend(0x00);
							
							UartSend(0xc5);
							UartSend(0x6a);
							UartSend(0x29);
							UartSend(0x06);
							UartSend(0x10);
							UartSend(0x56);
							Delay20ms();
							if(MCU_Uart_State == 1)
							{
								if(buffer[3] == 0x08 && buffer[4] == 0x10)
								{
									src = buffer;
									*dest++ = 0x3A;tx_num ++;
									for( i = 0; i < buffer[3]; i++)
									{
										*dest++ = *src++;
										 tx_num ++;
									}
								}
								break;
							}
						k++;
						}while(k < NO_ASK_NUM);
						}break;
						case 0x11://读HUSHTOP参数
						{
							k = 0;
							MCU_Uart_State = 0;
							do{
							for(i = 0; i < 16; i++)
							UartSend(0x00);
							
							UartSend(0xc5);
							UartSend(0x6a);
							UartSend(0x29);
							UartSend(0x06);
							UartSend(0x11);
							UartSend(0x08);
							Delay20ms();
							if(MCU_Uart_State == 1)
							{
								if(buffer[3] == 0x0e && buffer[4] == 0x11)
								{
									src = buffer;
									*dest++ = 0x3A;tx_num ++;
									for( i = 0; i < buffer[3]; i++)
									{
										*dest++ = *src++;
										 tx_num ++;
									}
								}
								break;
							}
						k++;
						}while(k < NO_ASK_NUM);
						}break;		
						case 0x13://读取设备已运行天数 RDB	
						{
							k = 0;
							MCU_Uart_State = 0;
							do{
							for(i = 0; i < 16; i++)
							UartSend(0x00);
							
							UartSend(0xc5);
							UartSend(0x6a);
							UartSend(0x29);
							UartSend(0x06);
							UartSend(0x13);
							UartSend(0xb4);
							Delay20ms();
							if(MCU_Uart_State == 1)
							{
								if(buffer[3] == 0x08 && buffer[4] == 0x13)
								{
									src = buffer;
									*dest++ = 0x3A;tx_num ++;
									for( i = 0; i < buffer[3]; i++)
									{
										*dest++ = *src++;
										 tx_num ++;
									}
								}
								break;
							}
						k++;
						}while(k < NO_ASK_NUM);
						}break;
						case 0x14://读软件版本
						{
							k = 0;
							MCU_Uart_State = 0;
							do{
							for(i = 0; i < 16; i++)
							UartSend(0x00);
							
							UartSend(0xc5);
							UartSend(0x6a);
							UartSend(0x29);
							UartSend(0x06);
							UartSend(0x14);
							UartSend(0x37);
							Delay20ms();
							if(MCU_Uart_State == 1)
							{
								if(buffer[3] == 0x08 && buffer[4] == 0x14)
								{
									src = buffer;
									*dest++ = 0x3A;tx_num ++;
									for( i = 0; i < buffer[3]; i++)
									{
										*dest++ = *src++;
										 tx_num ++;
									}
								}
								break;
							}
						k++;
						}while(k < NO_ASK_NUM);
						}break;							
							default :break;
					}
				}

			}
			dest = TX_buf2;
			*dest++ = 0xaf;
			*dest++ = 0x00;
			*dest++ = 0x00;
			*dest++ = 0x00;
			*dest++ = 0x00;
			*dest++ = 0x00;
			*dest++ = 0x00;
			*dest++ = 0x02;
			*dest++ = 0x14;
			*dest++ = 0x11;
			*dest++ = tx_num;			
			for(i = 0; i < tx_num ; i++)
			{
				*dest++ = TX_buf[i];
			}
			*dest++ = GetCheckSum_Xor(TX_buf2, tx_num +10);
			*dest++ = 0x3C;
			for( i = 0; i < tx_num + 13 ; i++)
			{
				Uart2Send(TX_buf2[i]);
			}
			
//		UartSendStr("这是一帧数据接收包 \r\n");
	}
}
/********************************************************************************
** Name:    CRC8 ??
** Function: 
** Input:   
** Output:   
********************************************************************************/

		
unsigned char CRC8(unsigned char *p, char counter)
 {
    unsigned char crc8 = 0;

    for( ; counter > 0; counter--)

    {
          crc8 = crc_array[crc8^*p]; //????CRC?
           p++;
    }
     return crc8;

 }
 
unsigned char GetCheckSum_Xor(unsigned char *p,unsigned char len)
{
  unsigned char i,Cs,temp;
  Cs = p[1];
  for(i=1;i<len;i++)
  {
    temp = Cs;
    Cs = temp^p[i + 1];
  }
  
  return Cs;
}