/*****************************************************************************
 * DRV_Timer.h
 *****************************************************************************/

#ifndef __DRV_TIMER_H__
#define __DRV_TIMER_H__

int32_t ExecTimer(void);

int32_t GetgTmzC(void);
float32_t GetgTmz1Sec(void);
void ISR_Timer(unsigned int id, void* arg);

uint32_t DRV_Timer_Init(void);

#endif /* __DRV_TIMER_H__ */
