#include "STC8F32S4.h"

#define FOSC            11059200UL
#define BRT2             (65536 - FOSC / 1200 / 4)
#define BRT              (65536 - FOSC / 38400 / 4)

#define UART1_RICEIVE_MAX		128								/*串口1接收缓冲区大小*/
#define UART2_RICEIVE_MAX		128									/*串口2接收缓冲区大小*/


#define DATA_PIN_RX	P1M1 = 0xff
#define DATA_PIN_TX P1M1 = 0

#define U1R_ON_IRQ 		        SCON |= 0x10
#define U1R_OFF_IRQ 		     	SCON &= ~0x10

#define U2R_ON_IRQ 				    S2CON |= 0x10  
#define U2R_OFF_IRQ 					S2CON &= ~0x10 

extern bit busy1;
extern unsigned char RX1_Cnt;
extern unsigned char TX1_Cnt;
extern unsigned char xdata Uart1_Buffer[UART1_RICEIVE_MAX];


extern bit busy2;
extern unsigned char RX2_Cnt;
extern unsigned char TX2_Cnt;
extern unsigned char xdata Uart2_Buffer[UART2_RICEIVE_MAX];





void PrintString1(unsigned char *puts);
void PrintString2(unsigned char *puts);
void STCUart1Init(void);
void STCUart2Init(void);
void Uart2Send(unsigned char dat);
void UartSend(unsigned char dat);
void PrintString1_num(unsigned char *puts,unsigned int len);
void PrintString2_num(unsigned char *puts,unsigned int len);
