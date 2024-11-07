#ifndef TIMER_H_
#define TIMER_H_
#include "../../timer_bsp/ps7_cortexa9_0/include/xparameters.h"
#include "../../timer_bsp/ps7_cortexa9_0/include/xscutimer_hw.h"
#include <stdint.h>
#define SCUTIMER_BASEADDR XPAR_XSCUTIMER_0_BASEADDR
// #define SCUTIMER_BASEADDR XPAR_XSCUTIMER_0_BASEADDR
// #define XSCUTIMER_LOAD_OFFSET		0x00U /**< Timer Load Register
// */ #define XSCUTIMER_COUNTER_OFFSET	0x04U /**< Timer Counter Register */
// #define XSCUTIMER_CONTROL_OFFSET	0x08U /**< Timer Control Register */
// #define XSCUTIMER_ISR_OFFSET		0x0CU /**< Timer Interrupt

void scutmr_set_autoload(uint32_t val);
void scutmr_set_load(uint32_t val);
void scutmr_set_enable(uint32_t val);
void scutmr_set_enable_interrupt(uint32_t val);
#endif // TIMER_H_
