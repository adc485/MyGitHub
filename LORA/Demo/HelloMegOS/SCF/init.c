#include "driver.h"

//********************************************************
//系统时钟初始化
//系统时钟以4倍时钟乘法器为输入，4倍时钟乘法器以内部时钟最大值为输入，即48MHz
void init_sysclk(void)
{                         
   u8  i;
   OSCICN |= 0x03; // Configure internal oscillator for	  its maximum frequency
   CLKMUL=0x00;
   CLKMUL |=0x80;
   for(i=0;i<200;i++);
   CLKMUL |=0xc0;
   while(!(CLKMUL&0x20));
   CLKSEL |=0x03;

   RSTSRC  |= 0x04; // Enable missing clock detector
}

//timer定时器2初始化,1KHz定时器中断
void   init_timer2(void)
{
    CKCON |= 0x10;//timer定时器2 使用系统时钟
	TMR2RLL=0x7f;			 
	TMR2RLH=0x44;

	TMR2L=0x7f;
	TMR2H=0x44;
	ET2=1;
	TMR2CN=0x04;//开启timer2  16为自动重装模式
}
//串口0初始化  115200 8 1 无
void init_uart0(void) 
{ 
//sbit        RXD=P0^5;	 //开漏输出
//sbit        TXD=P0^4;	 //推挽输出	
   	P0MDOUT   |= 0x10;

    SCON0 = 0x10; // SCON0: 8-bit variable bit rate
	CKCON |=  0x08;
  	TH1 =0x30;
    TL1 = TH1;                          // init Timer1
    TMOD &= ~0xf0;                      // TMOD: timer 1 in 8-bit autoreload
    TMOD |=  0x20;
    TR1 = 1;                            // START Timer1
    TI0 = 0;                            // Indicate TX0 ready
    ES0  = 1;	//ENable Uart Interrupt(Optional)
} 

void init_sysconfig(void)
{
   u16  i;
   VDM0CN |=0x80;
   for(i=0;i<40000;i++);
   RSTSRC  |= 0x02; //
   PFE0CN=0x20;
}

//********************************************************
//端口初始化
void init_port(void)
{
//sbit        LED=P0^3;	 //推挽输出
//sbit       BEEP=P1^6;	 //推挽输出
   
    P0MDOUT   |= 0x08;
    P0SKIP    |= 0xCF;

	P1MDOUT   |= 0xC0;
	P1MDIN   &= ~0x20;
	P1SKIP    |= 0x30;
    

    XBR0      = 0x03;
    XBR1      = 0x40;

	IT01CF    = 0x01;

	BEEP=0;
   
}