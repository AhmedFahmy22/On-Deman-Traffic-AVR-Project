#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_Math.h"
#include "GIE_int.h"
#include "GIE_priv.h"

void GIE_voidEnable(void)
{
  SET_BIT(SREG,7);
}
void GIE_voidDisable(void)
{
  CLR_BIT(SREG,7);
}
