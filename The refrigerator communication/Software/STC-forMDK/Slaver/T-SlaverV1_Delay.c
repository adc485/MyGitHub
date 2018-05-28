#include "T-SlaverV1.h"
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
void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;


	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void Delay1000000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 167;
	j = 181;
	k = 160;
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

