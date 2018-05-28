#define MAX_RXNUM	32
extern unsigned char Uart2_RX_State;
extern unsigned char xdata mac_temp[27];
extern unsigned char code Commond_PPID[];
extern unsigned char xdata Master_mac[27];
extern unsigned char xdata Slaver_mac[27];
void Master_Uart_Process(void);
int Get_Remaining_Days(unsigned char num,unsigned char timesec);
int Run();
void Slaver_Process(int days);

void Mac_process(unsigned char num);

unsigned char Achieve_master_mac(unsigned char delay_num);