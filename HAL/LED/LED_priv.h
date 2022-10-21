#ifndef DIO_PRIV_H
#define DIO_PRIV_H

typedef struct {
	uint8 u8LedPin;
}tstrLedCfg;

extern tstrLedCfg au8LedPins[LED_MAX_NUM];

#endif
