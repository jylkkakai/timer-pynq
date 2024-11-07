#include "timer.h"

void scutmr_set_autoload(uint32_t val) {
  volatile uint32_t *addr =
      (volatile uint32_t *)(SCUTIMER_BASEADDR + XSCUTIMER_CONTROL_OFFSET);
  if (val)
    *addr |= XSCUTIMER_CONTROL_AUTO_RELOAD_MASK;
  else
    *addr &= ~XSCUTIMER_CONTROL_AUTO_RELOAD_MASK;
}

void scutmr_set_load(uint32_t val) {
  volatile uint32_t *addr =
      (volatile uint32_t *)(SCUTIMER_BASEADDR + XSCUTIMER_LOAD_OFFSET);
  *addr = val;
}

void scutmr_set_enable(uint32_t val) {
  volatile uint32_t *addr =
      (volatile uint32_t *)(SCUTIMER_BASEADDR + XSCUTIMER_CONTROL_OFFSET);

  if (val)
    *addr |= XSCUTIMER_CONTROL_ENABLE_MASK;
  else
    *addr &= ~XSCUTIMER_CONTROL_ENABLE_MASK;
}
void scutmr_set_enable_interrupt(uint32_t val) {
  volatile uint32_t *addr =
      (volatile uint32_t *)(SCUTIMER_BASEADDR + XSCUTIMER_CONTROL_OFFSET);

  if (val)
    *addr |= XSCUTIMER_CONTROL_IRQ_ENABLE_MASK;
  else
    *addr &= ~XSCUTIMER_CONTROL_IRQ_ENABLE_MASK;
}
