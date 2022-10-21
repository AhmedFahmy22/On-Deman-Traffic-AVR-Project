#ifndef EXTINT0_PRIV_H
#define EXTINT0_PRIV_H

#define EXTINT0_SENSE_MODE_FALLING  0
#define EXTINT0_SENSE_MODE_RISING   1
#define EXTINT0_SENSE_MODE_IOC      2
#define EXTINT0_SENSE_MODE_LOW      3

#define GICR *((volatile uint8 *) 0x5B)
#define MCUCR *((volatile uint8 *) 0x55)
#define GIFR *((volatile uint8 *) 0x5A)

#endif
