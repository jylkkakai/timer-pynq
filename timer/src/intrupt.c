#include "intrupt.h"

// https://www.realdigital.org/doc/0376ae33249c443cda242c37e99e4daf
void enable_intrupt(void) {

  uint32_t cpsr_val = 0;

  asm("mrs %0, cpsr\n" : "=r"(cpsr_val)); // get current cpsr value

  cpsr_val &= ~(0xFF); // clear lower 8 bits
  cpsr_val |= 0x5F;    // set all bits but 'T' and 'I' bit

  asm("msr cpsr, %0\n" : : "r"(cpsr_val)); // writeback modified value

  return;
}
void disable_intrupt(void) {

  uint32_t cpsr_val = 0;

  asm("mrs %0, cpsr\n" : "=r"(cpsr_val)); // get current cpsr

  cpsr_val &= ~(0xFF); // clear lower 8 bits
  cpsr_val |= 0xDF;    // set all bits but the 'T' bit

  asm("msr cpsr, %0\n" : : "r"(cpsr_val)); // writeback modified value

  return;
}
