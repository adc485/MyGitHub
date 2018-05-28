#include "STC8F32S4.h"
#include "intrins.h"
#include "string.h"
#include "T-SlaverV1_Uart.h"
#include "T-SlaverV1_Check.h"
#include "T-SlaverV1_Protocol.h"
#include "T-SlaverV1_Delay.h"
#include "T-SlaverV1_Mac.h"


#define  	MAC_ADDR					0x0400
#define 	MAC_LEN						500
#define 	CYCLE_TIMES_MAX		30
#define 	GUIDE_TIMES				2
#define   SYS_SLEEP_TIME		10    //SYS_SLEEP_TIME/20 = MIN 
#define		DEVELOP_MODEL   //开发模式
#define 	MAC_PRINT			
//turn on/off Load instrument
#define 		TURN_ON_LOAD			P14 = 0
#define		  TURN_OFF_LOAD			P14 = 1
extern unsigned char xdata tee[];
extern unsigned char xdata tww[16];