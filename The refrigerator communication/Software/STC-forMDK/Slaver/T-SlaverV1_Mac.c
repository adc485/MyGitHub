#include "T-SlaverV1.h"


//???????11.0592MHz

//sfr     IAP_DATA    =   0xC2;
//sfr     IAP_ADDRH   =   0xC3;
//sfr     IAP_ADDRL   =   0xC4;
//sfr     IAP_CMD     =   0xC5;
//sfr     IAP_TRIG    =   0xC6;
//sfr     IAP_CONTR   =   0xC7;

#define WT_30M          0x80
#define WT_24M          0x81
#define WT_20M          0x82
#define WT_12M          0x83
#define WT_6M           0x84
#define WT_3M           0x85
#define WT_2M           0x86
#define WT_1M           0x87

void IapIdle()
{
    IAP_CONTR = 0;                              
    IAP_CMD = 0;                                
    IAP_TRIG = 0;                               
    IAP_ADDRH = 0x80;                           
    IAP_ADDRL = 0;
}

unsigned char IapRead(int addr)
{
    unsigned char dat;

    IAP_CONTR = WT_12M;                         
    IAP_CMD = 1;                                
    IAP_ADDRL = addr;                          
    IAP_ADDRH = addr >> 8;                     
    IAP_TRIG = 0x5a;                           
    IAP_TRIG = 0xa5;                            
    _nop_();
    dat = IAP_DATA;                            
    IapIdle();                                

    return dat;
}
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // IapProgram 

  Description:    // write mem 1byte

  Calls:          // System init

  Input:          // iint addr, unsigned char dat

  Output:         // Non
	
  Return:         // Non

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/23
*************************************************/
void IapProgram(int addr, unsigned char dat)
{
    IAP_CONTR = WT_12M;                        
    IAP_CMD = 2;                               
    IAP_ADDRL = addr;                           
    IAP_ADDRH = addr >> 8;                     
    IAP_DATA = dat;                             
    IAP_TRIG = 0x5a;                            
    IAP_TRIG = 0xa5;                          
    _nop_();
    IapIdle();                                
}
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // IapErase

  Description:    // Erase mem

  Calls:          // System init

  Input:          // int addr,

  Output:         // Non
	
  Return:         // Non

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/23
*************************************************/
void IapErase(int addr)
{
    IAP_CONTR = WT_12M;                        
    IAP_CMD = 3;                           
    IAP_ADDRL = addr;                         
    IAP_ADDRH = addr >> 8;                  
    IAP_TRIG = 0x5a;                         
    IAP_TRIG = 0xa5;                           
    _nop_();                                    
    IapIdle();                                 
}

/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Slaver_Write_Mac

  Description:    // Write Mac

  Calls:          // System init

  Input:          // int addr, unsigned char *dat, int num

  Output:         // Non
	
  Return:         // Non

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/23
*************************************************/
void Slaver_Write_Mac(int addr, unsigned char *dat, int num)
{
	unsigned char Clean_num;
	for(Clean_num = 0; Clean_num < num; Clean_num++)
	{
		IapErase(addr + Clean_num);
	}
	for(Clean_num = 0; Clean_num < num; Clean_num++)
	{
		IapProgram(addr +Clean_num,*dat++);
	}
}
/*************************************************
	Copyright (C), 2016-2018, Omnivoltaic Energy Solutions Tech. Co., Ltd.
	
  Function:       // Slaver_Read_Mac

  Description:    // Read Mac

  Calls:          // System init

  Input:          // int addr, unsigned char *dat, int num

  Output:         // Non
	
  Return:         // Non

  Others:         // 
	
	Author:      		// Liu Rongkun(Micheal)
	
	Data:						// 2018/04/23
*************************************************/
void Slaver_Read_Mac(int addr, unsigned char *dat, int num)
{
	unsigned char Read_num;
	for(Read_num = 0; Read_num < num; Read_num++)
	{
		dat[Read_num] = IapRead(addr++);
	}
}
