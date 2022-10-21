#include "../../LIB/STD_Types.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "LED_int.h"
#include "LED_cfg.h"
#include "LED_priv.h"

tenuErrorStatus LED_enuON(uint8 u8LedIndxCpy)		
{
	tenuErrorStatus enuErrorStateLoc = E_OK;
	if(u8LedIndxCpy<0||u8LedIndxCpy>=LED_MAX_NUM)
	{
		enuErrorStateLoc = E_NOK_PARAM_OUT_OF_RANGE;
	}
	else
	{
		DIO_enuSetPinValue(au8LedPins[u8LedIndxCpy].u8LedPin,1);
	}
	return enuErrorStateLoc;
}

tenuErrorStatus LED_enuOFF(uint8 u8LedIndxCpy)	
{
	tenuErrorStatus enuErrorStateLoc = E_OK;
	if(u8LedIndxCpy<0||u8LedIndxCpy>=LED_MAX_NUM)
	{
		enuErrorStateLoc = E_NOK_PARAM_OUT_OF_RANGE;
	}
	else
	{
		DIO_enuSetPinValue(au8LedPins[u8LedIndxCpy].u8LedPin,0);
	}
	return enuErrorStateLoc;
}

tenuErrorStatus LED_enuTOGGLE(uint8 u8LedIndxCpy)	
{
	tenuErrorStatus enuErrorStateLoc = E_OK;
	uint8 u8PinValueLoc;
	if(u8LedIndxCpy<0||u8LedIndxCpy>=LED_MAX_NUM)
	{
		enuErrorStateLoc = E_NOK_PARAM_OUT_OF_RANGE;
	}
	else
	{
		DIO_enuGetPinValue(au8LedPins[u8LedIndxCpy].u8LedPin, &u8PinValueLoc);
		switch(u8PinValueLoc)
		{
			case 0:
			LED_enuON(u8LedIndxCpy);
			break;
			case 1:
			LED_enuOFF(u8LedIndxCpy);
			break;
		}
	}
	return enuErrorStateLoc;
}
