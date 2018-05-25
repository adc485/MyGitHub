#include "Lora.h"
unsigned int xdata t_Ms = 0;
unsigned char xdata t_S  = 0;
unsigned char xdata SYS_STATE;
unsigned char xdata Timer_Counter;
unsigned char xdata Timer_Info;

void Lora_Timer_Init(void)
{
	  TMOD = 0x00;                               
    TL0 = 0x66;                                 
    TH0 = 0xfc;
    TR0 = 1;                                    
    ET0 = 1;                                    
    EA = 1;

}
void TM0_Isr() interrupt 1 using 1
{
	t_Ms++;
	if(t_Ms >= 250) // one ms
	{
		t_Ms = 0;
		t_S++;
		switch(SYS_STATE)
			{
					case 0 :
					{
						Timer_Counter = 0;
					}break;
					case 1 :
					{
						
					}break;
					case 2 :
					{
						Timer_Counter ++;
					
					}break;
					case 4:
					{
						Timer_Counter ++;
						if(Timer_Counter > 3)
						{
								SYS_STATE = 0x64;//超时请重新发送
						}	
					}
					default: break;

			}
		if(t_S >= 6)		//one S
		{
			t_S = 0 ;

		}
		
	}		
}
void Delay20ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 1;
	j = 216;
	k = 35;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


//void Delay2S()		//@11.0592MHz
//{
//	unsigned char i, j, k;

//	_nop_();
//	_nop_();
//	i = 85;
//	j = 12;
//	k = 155;
//	do
//	{
//		do
//		{
//			while (--k);
//		} while (--j);
//	} while (--i);
//}
void Delay1S()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
//void Delay200ms()		//@11.0592MHz
//{
//	unsigned char i, j, k;

//	_nop_();
//	_nop_();
//	i = 9;
//	j = 104;
//	k = 139;
//	do
//	{
//		do
//		{
//			while (--k);
//		} while (--j);
//	} while (--i);
//}

