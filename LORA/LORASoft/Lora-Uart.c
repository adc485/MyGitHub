#include "Lora.h"

bit busy2;
unsigned char wptr2;
unsigned char rptr2;
unsigned char xdata buffer2[LORA_DATA_MAX];

bit busy;
unsigned char wptr;
unsigned char rptr;
unsigned char xdata buffer[LORA_DATA_MAX];

void Uart_to_Lora() interrupt 8 using 1
{
    if (S2CON & 0x02)
    {
        S2CON &= ~0x02;
        busy2 = 0;
    }
    if (S2CON & 0x01)//
    {
        S2CON &= ~0x01;
//        buffer2[wptr2++] = S2BUF;
				Lora_Uart_Process();
        wptr2 &= 0x0f;
    }
}
void Uart_to_Mcu() interrupt 4 using 1
{
    if (TI)
    {
        TI = 0;
        busy = 0;
    }
    if (RI)
    {
        RI = 0;
//        buffer[wptr++] = SBUF;
				MCU_Uart_Process();
        wptr &= 0x0f;
    }
}

void UartInit()
{
    SCON = 0x50;
    TMOD = 0x00;
    TL1 = BRT;
    TH1 = BRT >> 8;
    TR1 = 1;
		AUXR |= 0x40;		
		AUXR &= 0xFE;		
    wptr = 0x00;
    rptr = 0x00;
    busy = 0;
}


void Uart2Init()
{
    S2CON = 0x50;
    T2L = BRT2;
    T2H = BRT2 >> 8;
    AUXR |= 0x14;
    wptr2 = 0x00;
    rptr2 = 0x00;
    busy2 = 0;
}

void UartSend(char dat)
{
    while (busy);
    busy = 1;
    SBUF = dat;
}


void Uart2Send(char dat)
{
    while (busy2);
    busy2 = 1;
    S2BUF = dat;
}

void UartSendStr(char *p)
{
    while (*p)
    {
        UartSend(*p++);
    }
}


void Uart2SendStr(char *p)
{
    while (*p)
    {
        Uart2Send(*p++);
    }
}
//void UartSendnum(unsigned char dat[],unsigned char num)
//{
//		unsigned char i=0;
//    for(i = 0; i < num; i++)
//			UartSend(dat[i]);
//}
