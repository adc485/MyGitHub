//#define MAX_RXNUM	32
extern unsigned char Uart2_RX_State;
extern unsigned char Uart1_RX_State;
extern unsigned char DataSize_MCU;
extern unsigned char bSynWord_MCU;
extern unsigned char PaketSize_MCU;
extern unsigned char Check_Btye_MCU;
extern unsigned char Set_mac;

void Master_Uart_Process(void);
void Master_Uart2_Process(void);
void Master_Process(unsigned char num);
void Find_mac(unsigned char k);