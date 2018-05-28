#include "T-MasterV1.h"
//#include "T-MasterV1_Uart.h"

bit busy1;
unsigned char RX1_Cnt;
unsigned char TX1_Cnt;
unsigned char xdata Uart1_Buffer[UART1_RICEIVE_MAX];
unsigned char bSynWord_MCU;
unsigned char DataSize_MCU;
unsigned char PaketSize_MCU;
unsigned char Check_Btye_MCU;

bit busy2;
unsigned char RX2_Cnt;
unsigned char TX2_Cnt;
unsigned char DataSize_PTC;
unsigned char PaketSize_PTC;
unsigned char xdata Uart2_Buffer[UART2_RICEIVE_MAX];
/************************************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // STCUart1Init

  Description:    // Uart1 Init P30=RxD P31=TxD

  Calls:          // System init

  Input:          // BRT is 波特率

  Output:         // Non
	
  Return:         // Non

  Others:         // 在头文件定义BRT波特率
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/03/27
****************************************************************************/
void STCUart1Init(void)
{
    SCON = 0x50;
    TMOD = 0x00;
    TL1 = BRT;							/*设置波特率*/
    TH1 = BRT >> 8;					
    TR1 = 1;
		AUXR |= 0x40;		
		AUXR &= 0xFE;		
    TX1_Cnt = 0x00;
    RX1_Cnt = 0x00;
    busy1 = 0;
}
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // STCUart1Init

  Description:    // Uart2 Init P10=RxD P11=TxD

  Calls:          // System init

  Input:          // BRT is 波特率

  Output:         // Non
	
  Return:         // Non

  Others:         // 在头文件定义BRT波特率
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/03/27
*************************************************/
void STCUart2Init(void)
{
    S2CON = 0x50;
    T2L = BRT2;
    T2H = BRT2 >> 8;
    AUXR |= 0x14;
    TX2_Cnt = 0x00;
    RX2_Cnt = 0x00;
    busy2 = 0;
	
		IE2 = 0x01;
		EA = 1;
		ES |= 1;
		EA |= 1;
}
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // PrintString1

  Description:    // Send char string by Uart1

  Calls:          // System init

  Input:          // unsigned char 

  Output:         // Non
	
  Return:         // Non

  Others:         // Stop in /0
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/03/27
*************************************************/
void PrintString1(unsigned char *puts) //发送一个字符串
{
    for (; *puts != 0;  puts++)     //遇到停止符0结束
    {
        SBUF = *puts;
        busy1 = 1;
        while(busy1);
    }
}
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // PrintString1

  Description:    // Send char string by Uart1

  Calls:          // System init

  Input:          // unsigned char ;Send num

  Output:         // Non
	
  Return:         // Non

  Others:         // Stop in /0
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/16
*************************************************/
//void PrintString1_num(unsigned char *puts, unsigned char num) //发送一个字符串
//{
//	unsigned char i;
//    for (i = 0; i < num;  i++)     //遇到停止符0结束
//    {
////        SBUF = *puts++;
////        busy1 = 1;
////        while(busy1);
//				UartSend(*puts++);
//    }
//}
void PrintString1_num( unsigned char *str, unsigned int strlen) 
{  
  unsigned int k = 0 ;  
  do  
 {  
  UartSend(*(str + k)); 
  k++; 
 }  
   while (k < strlen);  
} 
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Debug_print

  Description:    // prin debug msg

  Calls:          // debug molde

  Input:          // unsigned char 

  Output:         // Non
	
  Return:         // Non

  Others:         // Stop in /0
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/24
*************************************************/
void Debug_print(unsigned char *puts) //发送一个字符串
{
	#ifndef DEVELOP_MODEL
		
	#else
			for (; *puts != 0;  puts++)     //遇到停止符0结束
			{
					SBUF = *puts;
					busy1 = 1;
					while(busy1);
			}
	#endif
}

/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // PrintString2

  Description:    // Send char string by Uart2

  Calls:          // System init

  Input:          // unsigned char 

  Output:         // Non
	
  Return:         // Non

  Others:         // Stop in /0
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/03/27
*************************************************/
void PrintString2(unsigned char *puts) //发送一个字符串
{
    for (; *puts != 0;  puts++)     //遇到停止符0结束
    {
        S2BUF = *puts;
        busy2 = 1;
        while(busy2);
    }
}
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // PrintString2

  Description:    // Send char string by Uart2

  Calls:          // System init

  Input:          // unsigned char ;Send num

  Output:         // Non
	
  Return:         // Non

  Others:         // Stop in /0
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/13
*************************************************/
//void PrintString2_num(unsigned char *puts, unsigned char num) //发送一个字符串
//{
//	unsigned char i;
//    for (i = 0; i < num ;  i++)     //遇到停止符0结束
//    {
//        S2BUF = *puts++;
//        busy2 = 1;
//        while(busy2);
//    }
//}
void PrintString2_num( unsigned char *str, unsigned int strlen) 
{  
  unsigned int k = 0 ;  
  do  
 {  
  Uart2Send(*(str + k)); 
  k++; 
 }  
   while (k < strlen);  
} 
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Uart2Send

  Description:    // Send char string by Uart2

  Calls:          // System init

  Input:          // unsigned char 

  Output:         // Non
	
  Return:         // Non

  Others:         // Stop in /0
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/03/29
*************************************************/
void Uart2Send(unsigned char dat)
{
    while (busy2);
    busy2 = 1;
    S2BUF = dat;while (busy2);
}
//void Uart2Send( unsigned char ch)  
//{  

//   S2BUF=ch;  
//   while ((S2CON & 0x02)== 0);  
//   S2CON &= ~0x02; ;  
//}  
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // UartSend

  Description:    // Send char string by Uart1

  Calls:          // System init

  Input:          // unsigned char 

  Output:         // Non
	
  Return:         // Non

  Others:         // Stop in /0
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/03/29
*************************************************/
//void UartSend(unsigned char dat)
//{
//    while (busy1);
//    busy1 = 1;
//    SBUF = dat;
//}
void UartSend( unsigned char ch)  
{  

   SBUF=ch;  
   while (TI== 0);  
   TI= 0 ;  
}  
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // STCUart2_Interrupt

  Description:    // Uart2 Interrupt Program

  Calls:          // CPU

  Input:          // Non

  Output:         // Non
	
  Return:         // Non

  Others:         // 串口2中断程序
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/03/27
*************************************************/
void STCUart2_Interrupt() interrupt 8 using 1
{
    if (S2CON & 0x02)
    {
        S2CON &= ~0x02; /**/
        busy2 = 0;
    }
    if (S2CON & 0x01)/*判断是否有中断产生*/
    {
//        S2CON &= ~0x01;
//        Uart2_Buffer[RX2_Cnt] = S2BUF;  
//				if(++RX2_Cnt >= UART2_RICEIVE_MAX)   RX2_Cnt = 0;    //防溢出
			S2CON &= ~0x01;
			 Master_Uart_Process();
    }
}

/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // STCUart1_Interrupt

  Description:    // Uart1 Interrupt Program

  Calls:          // CPU

  Input:          // Non

  Output:         // Non
	
  Return:         // Non

  Others:         // 串口1中断程序
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/03/27
*************************************************/
void STCUart1_Interrupt() interrupt 4 using 1
{
    if (TI)
    {
        TI = 0;
        busy1 = 0;
    }
    if (RI)
    {							
        RI = 0;
//        Uart1_Buffer[RX1_Cnt] = SBUF;
//				if(++RX1_Cnt >= UART1_RICEIVE_MAX)   RX1_Cnt = 0;    //防溢出
			Master_Uart2_Process();
    }
}

