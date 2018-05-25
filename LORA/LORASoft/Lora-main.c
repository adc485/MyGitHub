
#include "Lora.h"




void main()
{
		SYS_STATE = 0;
		UartInit();
    Uart2Init();
    IE2 = 0x01;
    EA = 1;
	  ES |= 1;
    EA |= 1;
		Lora_Timer_Init();
		SYS_TIMER_STOP;
    Uart2SendStr("U2art Test1!\r\n");
		UartSendStr("Uart Test LORAV1.0 !\r\n");
    while (1)
    {	 
				if(Lora_Uart_State == 1)
				{
					Lora_Buffer_Analysis();
					Lora_Uart_State = 0;				
				}
				if(MCU_Uart_State ==1)
				{
					MCU_Uart_State = 0;
					switch(buffer[4])
					{
		  			case 0x01:
						{
							UartSendStr("Command OPID 0x01: !");
							UartSend(buffer[5]);
							UartSend(buffer[6]);
						}
						case 0x04:
						{
							Hand_PAYG();
						}break;
						case 0x05:
						{
							UartSendStr("Command 0x05: !");
							UartSend(buffer[5]);
							UartSend(buffer[6]);
						}
						case 0xfa:
						{
						
							SYS_STATE = 3;
						}
						default: break;
					}
				}
    }
}


