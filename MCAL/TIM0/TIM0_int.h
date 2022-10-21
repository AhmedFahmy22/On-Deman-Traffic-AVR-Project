#ifndef  TIM0_INT_H
#define  TIM0_INT_H

#define TIM0_MODE_NORMAL       0
#define TIM0_MODE_CTC          1
#define TIM0_MODE_FAST_PWM     2
#define TIM0_MODE_PHASE_PWM    3

#define TIM0_WF_TOGGLE_PIN                   0
#define TIM0_WF_SET_PIN    	                 1
#define TIM0_WF_CLR_PIN                      2
#define TIM0_WF_SET_CMP_CLR_TOP              3
#define TIM0_WF_SET_TOP_CLR_CMP              4
#define TIM0_WF_SET_UPCOUNT_CLR_DOWNCOUNT    5
#define TIM0_WF_CLR_UPCOUNT_SET_DOWNCOUNT    6
#define TIM0_WF_OFF                          7


void TIM0_voidInit(void);

tenuErrorStatus  TIM0_enuSetTimerValue(uint8 u8ValueCpy);
uint8 TIM0_u8GetTimerValue(void);
tenuErrorStatus  TIM0_enuSetCompareValue(uint8 u8ValueCpy);
void  TIM0_voidEnableOvfInt(void);
void  TIM0_voidDisableOvfInt(void);
void  TIM0_voidEnableCmpInt(void);
void  TIM0_voidDisableCmpInt(void);
tenuErrorStatus  TIM0_enuSetCallBackOvf(pf pfCpy);
tenuErrorStatus  TIM0_enuSetCallBackCmp(pf pfCpy);
tenuErrorStatus  TIM0_enuChangMode(uint8 u8ModeValueCpy);
tenuErrorStatus  TIM0_enuChangeWaveForm(uint8 u8WfModeValueCpy);



#endif