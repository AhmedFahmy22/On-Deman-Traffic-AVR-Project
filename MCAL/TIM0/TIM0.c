#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_Math.h"

#include "TIM0_int.h"
#include "TIM0_cfg.h"
#include "TIM0_priv.h"

pf TIM0_pfOvf ;
pf TIM0_pfCmp ;

void TIM0_voidInit(void)
{
#if   TIM0_MODE   == TIM0_MODE_NORMAL  
		CLR_BIT(TCCR0 ,6);
		CLR_BIT(TCCR0 ,3);  
#elif TIM0_MODE   == TIM0_MODE_CTC 
		CLR_BIT(TCCR0 ,6);
		SET_BIT(TCCR0 ,3);      
#elif TIM0_MODE   == TIM0_MODE_FAST_PWM
		SET_BIT(TCCR0 ,6);
		SET_BIT(TCCR0 ,3);  
#elif TIM0_MODE   == TIM0_MODE_PHASE_PWM 
		SET_BIT(TCCR0 ,6);
		CLR_BIT(TCCR0 ,3);
#endif
		
TIM0_enuChangeWaveForm(TIM0_WF_MODE);

TCCR0 &=0b11111000;
TCCR0 |=TIM0_PRESCALLER;
}

tenuErrorStatus  TIM0_enuSetTimerValue(uint8 u8ValueCpy)
{
	tenuErrorStatus enuErrorStateLoc = E_OK;
	if(u8ValueCpy<0||u8ValueCpy>255)
	{
		enuErrorStateLoc = E_NOK_PARAM_OUT_OF_RANGE;
	}
	else
	{
		TCNT0 = u8ValueCpy;
	}
	return enuErrorStateLoc;
}
uint8 TIM0_u8GetTimerValue(void)
{
	return TCNT0 ;
}
tenuErrorStatus  TIM0_enuSetCompareValue(uint8 u8ValueCpy)
{
	tenuErrorStatus enuErrorStateLoc = E_OK;
	if(u8ValueCpy<0||u8ValueCpy>255)
	{
		enuErrorStateLoc = E_NOK_PARAM_OUT_OF_RANGE;
	}
	else
	{
		OCR0 = u8ValueCpy;
	}
	return enuErrorStateLoc;
}
void  TIM0_voidEnableOvfInt(void)
{
	SET_BIT(TIMSK, 0);
}
void  TIM0_voidDisableOvfInt(void)
{
	CLR_BIT(TIMSK, 0);
}
void  TIM0_voidEnableCmpInt(void)
{
	SET_BIT(TIMSK , 1);
}
void  TIM0_voidDisableCmpInt(void)
{
	CLR_BIT(TIMSK , 1) ;
}
tenuErrorStatus  TIM0_enuSetCallBackOvf(pf pfCpy)
{
	tenuErrorStatus enuErrorStateLoc = E_OK;
	if(pfCpy == NULL_PTR)
	{
		enuErrorStateLoc = E_NOK_PARAM_NULL_POINTER;
	}
	else
	{
		TIM0_pfOvf = pfCpy;
	}
	return enuErrorStateLoc;
}
tenuErrorStatus  TIM0_enuSetCallBackCmp(pf pfCpy)
{
	tenuErrorStatus enuErrorStateLoc = E_OK;
	if(pfCpy == NULL_PTR)
	{
		enuErrorStateLoc = E_NOK_PARAM_NULL_POINTER;
	}
	else
	{
		TIM0_pfCmp = pfCpy;
	}
	return enuErrorStateLoc;
}
tenuErrorStatus  TIM0_enuChangMode(uint8 u8ModeValueCpy)
{
	tenuErrorStatus enuErrorStateLoc = E_OK;
	switch(u8ModeValueCpy)
	{
		case TIM0_MODE_NORMAL:
		CLR_BIT(TCCR0 ,6);
		CLR_BIT(TCCR0 ,3);
		break ;
		case TIM0_MODE_CTC:
		CLR_BIT(TCCR0 ,6);
		SET_BIT(TCCR0 ,3);
		break ;
		case TIM0_MODE_FAST_PWM:
		SET_BIT(TCCR0 ,6);
		SET_BIT(TCCR0 ,3);
		break ;		
		case TIM0_MODE_PHASE_PWM:
		SET_BIT(TCCR0 ,6);
		CLR_BIT(TCCR0 ,3);
		break ;	
		default :
		/* normal mode*/
		enuErrorStateLoc = E_NOK_PARAM_OUT_OF_RANGE;
		CLR_BIT(TCCR0 ,6);
		CLR_BIT(TCCR0 ,3);		
	}
	return enuErrorStateLoc;
}
tenuErrorStatus  TIM0_enuChangeWaveForm(uint8 u8WfModeValueCpy)
{
	tenuErrorStatus enuErrorStateLoc = E_OK;
	switch(u8WfModeValueCpy)
	{
		case TIM0_WF_TOGGLE_PIN:
		SET_BIT(TCCR0 , 4);
		CLR_BIT(TCCR0 , 5);
		break ;
		case TIM0_WF_SET_PIN:
		SET_BIT(TCCR0 , 4);
		SET_BIT(TCCR0 , 5);
		break ;
		case TIM0_WF_CLR_PIN:
		CLR_BIT(TCCR0 , 4);
		SET_BIT(TCCR0 , 5);
		break ;		
		case TIM0_WF_SET_CMP_CLR_TOP:
		SET_BIT(TCCR0 , 4);
		SET_BIT(TCCR0 , 5);
		break ;		
		case TIM0_WF_SET_TOP_CLR_CMP:
		CLR_BIT(TCCR0 , 4);
		SET_BIT(TCCR0 , 5);
		break ;		
		case TIM0_WF_SET_UPCOUNT_CLR_DOWNCOUNT:
		SET_BIT(TCCR0 , 4);
		SET_BIT(TCCR0 , 5);
		break ;		
		case TIM0_WF_CLR_UPCOUNT_SET_DOWNCOUNT:
		CLR_BIT(TCCR0 , 4);
		SET_BIT(TCCR0 , 5);
		break ;
		default :
		/*No PWM generated*/
		enuErrorStateLoc = E_NOK_PARAM_OUT_OF_RANGE;
		CLR_BIT(TCCR0 , 4);
		CLR_BIT(TCCR0 , 5);
	}	
	return enuErrorStateLoc;
}
/*ISR OVF*/
void __vector_11 (void) __attribute__((signal ,used));
void __vector_11 (void)
{
	TIM0_pfOvf();
}

/*ISR CMP*/
void __vector_10 (void) __attribute__((signal ,used));
void __vector_10 (void)
{
	TIM0_pfCmp();
}



