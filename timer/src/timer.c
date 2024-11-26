#include "timer.h"
#include "../../timer_bsp/ps7_cortexa9_0/include/xscugic.h"

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

void scugic_dist_set_enable(uint32_t interrupt_id) {

  // Distributor register. Set-Enable. (ARM Cortex Technical Reference Manual)
  uint32_t *addr = (uint32_t *)(XPAR_PS7_INTC_DIST_0_S_AXI_BASEADDR +
                                XSCUGIC_ENABLE_SET_OFFSET);
  *addr = 0x1U << interrupt_id;
}

void scugic_dist_clear_enable(uint32_t interrupt_id) {

  // Distributor register. Clear-Enable. (ARM Cortex Technical Reference Manual)
  uint32_t *addr = (uint32_t *)(XPAR_PS7_INTC_DIST_0_S_AXI_BASEADDR +
                                XSCUGIC_DISABLE_OFFSET);
  // xil_printf("set-enable: %d\r\n",
  //            *((uint32_t *)XPAR_PS7_INTC_DIST_0_S_AXI_BASEADDR +
  //              XSCUGIC_ENABLE_SET_OFFSET) &&
  //                (0x1U << interrupt_id));
  *addr = 0x1U << interrupt_id;
  // xil_printf("set-enable: %d\r\n",
  //            *((uint32_t *)XPAR_PS7_INTC_DIST_0_S_AXI_BASEADDR +
  //              XSCUGIC_ENABLE_SET_OFFSET) &&
  //                (0x1U << interrupt_id));
}
