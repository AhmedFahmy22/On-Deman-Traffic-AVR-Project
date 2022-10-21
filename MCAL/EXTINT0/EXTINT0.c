#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_Math.h"
#include "EXTINT0_int.h"
#include "EXTINT0_cfg.h"
#include "EXTINT0_priv.h"

pf x;

void EXTINT0_voidInit(void)
{
  #if EXTINT0_SENSE_MODE == EXTINT0_SENSE_MODE_FALLING
  SET_BIT(MCUCR,1);
  CLR_BIT(MCUCR,0);

  #elif EXTINT0_SENSE_MODE == EXTINT0_SENSE_MODE_RISING
  SET_BIT(MCUCR,1);
  SET_BIT(MCUCR,0);

  #elif EXTINT0_SENSE_MODE == EXTINT0_SENSE_MODE_IOC
  CLR_BIT(MCUCR,1);
  SET_BIT(MCUCR,0);

  #else
  CLR_BIT(MCUCR,1);
  CLR_BIT(MCUCR,0);

  #endif
  EXTINT0_voidDisable();
  SET_BIT(GIFR,6); //Clear flag
}

void EXTINT0_voidEnable(void)
{
  SET_BIT(GICR,6);
}

void EXTINT0_voidDisable(void)
{
  CLR_BIT(GICR,6);
}

tenuErrorStatus EXTINT0_enuSetCallBack(pf y)
{
  tenuErrorStatus enuErrorStateLoc = E_OK;
  if(y == NULL_PTR)
  {
	  enuErrorStateLoc = E_NOK_PARAM_NULL_POINTER;
  }
  else
  {
	  x=y;
  }
  return enuErrorStateLoc;
}

void __vector_1(void) __attribute__((signal,used)); // Must for any ISR
void __vector_1(void)
{
  /*any variable used here should be volatile*/
  x();
}
