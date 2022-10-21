#include "../LIB/STD_Types.h"
#include "../LIB/BIT_Math.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXTINT0/EXTINT0_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/TIM0/TIM0_int.h"

#include "../HAL/LED/LED_int.h"

#define CAR_GREEN 	0
#define CAR_YELLOW 	1
#define CAR_RED 	2
#define PED_GREEN 	3
#define PED_YELLOW 	4
#define PED_RED 	5

uint32 u32OvrFlCntr=0;
uint32 u32PressCntr=0;
uint8 u8PedMode=0;
uint8 u8Led_6=1;

void Tim0_OvF(void);
void AppIsr(void);

void appStart(void)
{
	DIO_voidInit();
	EXTINT0_voidInit();
	DIO_enuSetPinValue(26,1);
	EXTINT0_enuSetCallBack(AppIsr);
	EXTINT0_voidEnable();
	GIE_voidEnable();
	TIM0_voidInit();
	TIM0_enuSetCallBackOvf(Tim0_OvF);
	TIM0_voidEnableOvfInt();
	while (1)
	{
		if(u32OvrFlCntr==0)
		{
			LED_enuON(CAR_GREEN);
			LED_enuON(PED_RED);
		}
		else if(u32OvrFlCntr==19530)
		{
			LED_enuOFF(CAR_GREEN);
			LED_enuOFF(PED_RED);
			LED_enuON(CAR_YELLOW);
			LED_enuON(PED_YELLOW);
		}
		else if(u32OvrFlCntr == 39060)
		{
			LED_enuOFF(CAR_YELLOW);
			LED_enuOFF(PED_YELLOW);
			LED_enuON(PED_GREEN);
			LED_enuON(CAR_RED);
		}
		else if(u32OvrFlCntr==58590)
		{
			LED_enuOFF(PED_GREEN);
			LED_enuOFF(CAR_RED);

			u8PedMode=0;
			u32PressCntr=0;
			u32OvrFlCntr=0;
		}
	}
}

void AppIsr(void)
{
	if(u8PedMode == 0)
	{
		u8PedMode=1;
	}
}

void Tim0_OvF(void)
{
	DIO_enuGetPinValue(26,&u8Led_6);
	if(u8Led_6==0)
	{
		u32PressCntr++;
	}
	if((u8PedMode==1)&&(u32PressCntr<3906)&&(u32PressCntr>10))
	{
		if(u32OvrFlCntr<19530)
		{
			u32OvrFlCntr=0;
		}
		else if((u32OvrFlCntr>19530)&&(u32OvrFlCntr<39060))
		{
			u32OvrFlCntr=19530;
		}

		u8PedMode=2;
		TIM0_enuSetTimerValue(0);
	}
	if((u32OvrFlCntr==23436)||(u32OvrFlCntr==27342)||(u32OvrFlCntr==31248)||(u32OvrFlCntr==35154))
	{
		LED_enuTOGGLE(CAR_YELLOW);
		LED_enuTOGGLE(PED_YELLOW);
	}
	u32OvrFlCntr++;
}
