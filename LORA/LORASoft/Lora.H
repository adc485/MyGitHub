#include "reg51.h"
#include "intrins.h"
#include "string.h"

#define LORA_DATA_MAX	128

#define SYS_TIMER_START 	ET0	= 1		
#define SYS_TIMER_STOP		ET0	= 0
#define NO_ASK_NUM	3

//#define RECHARGETIME    66

#define RECHARGETIME    76

#define FOSC            11059200UL
#define BRT2             (65536 - FOSC / 9600 / 4)
#define BRT              (65536 - FOSC / 38400 / 4)

sfr     AUXR        =   0x8e;
sfr     T2H         =   0xd6;
sfr     T2L         =   0xd7;
sfr     S2CON       =   0x9a;
sfr     S2BUF       =   0x9b;
sfr     IE2         =   0xaf;

void UartInit();
void Uart2Init();
void UartSendStr(char *p);
void Uart2SendStr(char *p);
void UartSend(char dat);
void Uart2Send(char dat);

void Lora_Timer_Init(void);

void Lora_Uart_Process(void);
void MCU_Uart_Process(void);
unsigned char CRC8(unsigned char *p, char counter);
unsigned char GetCheckSum_Xor(unsigned char *p,unsigned char len);
void UartSendnum(unsigned char dat[],unsigned char num);
void Delay20ms();
//void Delay2S();
void Delay1S();		//@11.0592MHz
void Lora_Buffer_Analysis();
void Hand_PAYG();


extern unsigned char xdata buffer[LORA_DATA_MAX];
extern unsigned char xdata buffer2[LORA_DATA_MAX];
extern unsigned char wptr;
extern unsigned char wptr2;
extern unsigned char rptr;
extern unsigned char rptr2;
extern unsigned char Lora_Uart_State;
extern unsigned char MCU_Uart_State;
extern unsigned char PaketSize;
extern unsigned char xdata SYS_STATE;
extern unsigned char xdata command[23];
extern unsigned char info_num;   //查询信息条数
extern unsigned char xdata Timer_Counter; //命令超时计数器