#include "T-MasterV1.h"
#include "T-MasterV1_Delay.h"
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Delay1ms

  Description:    // @11.0592MHz Delay 1ms

  Calls:          // 

  Input:          // 

  Output:         // Non
	
  Return:         // Non

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/13
*************************************************/
void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Delay1ms

  Description:    // @11.0592MHz Delay 20ms

  Calls:          // 

  Input:          // 

  Output:         // Non
	
  Return:         // Non

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/13
*************************************************/
void Delay20ms()		//@11.0592MHz
{
	unsigned char i, j, k;


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
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Delay1ms

  Description:    // @11.0592MHz Delay 500ms

  Calls:          // 

  Input:          // 

  Output:         // Non
	
  Return:         // Non

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/13
*************************************************/
void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Delay1ms

  Description:    // @11.0592MHz Delay 1000ms

  Calls:          // 

  Input:          // 

  Output:         // Non
	
  Return:         // Non

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/13
*************************************************/
void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;


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
