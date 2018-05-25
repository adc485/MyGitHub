#include "driver.h"

//********************************************************
//ϵͳʱ�ӳ�ʼ��
//ϵͳʱ����4��ʱ�ӳ˷���Ϊ���룬4��ʱ�ӳ˷������ڲ�ʱ�����ֵΪ���룬��48MHz
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

//timer��ʱ��2��ʼ��,1KHz��ʱ���ж�
void   init_timer2(void)
{
    CKCON |= 0x10;//timer��ʱ��2 ʹ��ϵͳʱ��
	TMR2RLL=0x7f;			 
	TMR2RLH=0x44;

	TMR2L=0x7f;
	TMR2H=0x44;
	ET2=1;
	TMR2CN=0x04;//����timer2  16Ϊ�Զ���װģʽ
}
//����0��ʼ��  115200 8 1 ��
void init_uart0(void) 
{ 
//sbit        RXD=P0^5;	 //��©���
//sbit        TXD=P0^4;	 //�������	
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
//�˿ڳ�ʼ��
void init_port(void)
{
//sbit        LED=P0^3;	 //�������
//sbit       BEEP=P1^6;	 //�������
   
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