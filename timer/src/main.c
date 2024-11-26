/*****************************************************************************
 *
 * Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * Use of the Software is limited solely to applications:
 * (a) running on a Xilinx device, or
 * (b) that interact with a Xilinx device through a bus or interconnect.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name of the Xilinx shall not be used
 * in advertising or otherwise to promote the sale, use or other dealings in
 * this Software without prior written authorization from Xilinx.
 *
 ******************************************************************************/

/*
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

// #include "../../timer_bsp/ps7_cortexa9_0/include/sleep.h"
// #include "../../timer_bsp/ps7_cortexa9_0/include/xil_exception.h"
#include "../../timer_bsp/ps7_cortexa9_0/include/xil_printf.h"
#include "../../timer_bsp/ps7_cortexa9_0/include/xparameters.h"
#include "../../timer_bsp/ps7_cortexa9_0/include/xscugic.h"
#include "intrupt.h"
#include "timer.h"

#define TIMER_DEVICE_ID XPAR_XSCUTIMER_0_DEVICE_ID
#define INTC_DEVICE_ID XPAR_SCUGIC_SINGLE_DEVICE_ID
#define TIMER_IRPT_INTR 29U

#define TIMER_LOAD_VALUE 0xFFFFFFF

int ScuTimerIntrExample(XScuGic *IntcInstancePtr, u16 TimerIntrId);

static void TimerIntrHandler(void *CallBackRef);

static int TimerSetupIntrSystem(XScuGic *IntcInstancePtr, u16 TimerIntrId);

// static void TimerDisableIntrSystem(XScuGic *IntcInstancePtr, u16
// TimerIntrId);

XScuGic IntcInstance; /* Interrupt Controller Instance */

volatile int TimerExpired;

volatile int counter;

int main(void) {
  int Status;

  xil_printf("SCU Timer Interrupt Example Test \r\n");

  Status = ScuTimerIntrExample(&IntcInstance, TIMER_IRPT_INTR);
  if (Status != XST_SUCCESS) {
    xil_printf("SCU Timer Interrupt Example Test Failed\r\n");
    return XST_FAILURE;
  }

  xil_printf("Successfully ran SCU Timer Interrupt Example Test\r\n");
  return XST_SUCCESS;
}

int ScuTimerIntrExample(XScuGic *IntcInstancePtr, u16 TimerIntrId) {
  int Status;
  int LastTimerExpired = 0;

  Status = TimerSetupIntrSystem(IntcInstancePtr, TimerIntrId);
  if (Status != XST_SUCCESS) {
    return XST_FAILURE;
  }
  scutmr_set_autoload(1);

  scutmr_set_load(TIMER_LOAD_VALUE);

  scutmr_set_enable(1);

  while (1) {

    while (TimerExpired == LastTimerExpired) {
    }

    xil_printf("counter: %d\r\n", counter);
    LastTimerExpired = TimerExpired;

    if (TimerExpired == 13) {
      scutmr_set_enable(0);
      break;
    }
  }
  scugic_dist_clear_enable(TimerIntrId);
  // TimerDisableIntrSystem(IntcInstancePtr, TimerIntrId);

  return 0;
}

extern XScuGic_Config XScuGic_ConfigTable[XPAR_SCUGIC_NUM_INSTANCES];
static int TimerSetupIntrSystem(XScuGic *IntcInstancePtr, u16 TimerIntrId) {

  XScuGic_Config *IntcConfig;

  uint32_t Int_Id = 29;
  /*
   * Initialize the interrupt controller driver so that it is ready to
   * use.
   */
  // IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
  IntcConfig = &XScuGic_ConfigTable[0];
  if (NULL == IntcConfig) {
    return XST_FAILURE;
  }

  // XScuGic_VectorTableEntry HandlerTable[XSCUGIC_MAX_NUM_INTR_INPUTS];
  // xil_printf("IntcConfig->CpuBaseAddress: %p\r\n",

#if 1
  IntcInstancePtr->IsReady = 0U;
  IntcInstancePtr->Config = IntcConfig;

  IntcInstancePtr->Config->HandlerTable[Int_Id].CallBackRef = IntcInstancePtr;

  // xil_printf("DistBaseAddress: %p\r\n",
  //            IntcInstancePtr->Config->DistBaseAddress);
  xil_printf("CpuBaseAddress: %p\r\n", IntcInstancePtr->Config->CpuBaseAddress);

  // XScuGic_Stop(IntcInstancePtr);
  // DistributorInit(IntcInstancePtr, 1); // IntcConfig->CpuBaseAddress);
  // XScuGic_DistWriteReg(IntcInstancePtr, XSCUGIC_DIST_EN_OFFSET, 0U)C;

  // scugic_dist_reg_enable(void);
  // XScuGic_DistWriteReg(IntcInstancePtr, XSCUGIC_DIST_EN_OFFSET,
  //                      XSCUGIC_EN_INT_MASK);
  // u32 RegValue;
  // RegValue = XScuGic_DistReadReg(IntcInstancePtr, XSCUGIC_DIST_EN_OFFSET);
  // if ((RegValue & XSCUGIC_EN_INT_MASK) == 0U) {
  //   xil_printf("reg_value: %d\r\n", (RegValue & XSCUGIC_EN_INT_MASK));
  //   // DoDistributorInit(InstancePtr, CpuID);
  //   return 1;
  // }

  // CPUInitialize(IntcInstancePtr);
  // XScuGic_CPUWriteReg(IntcInstancePtr, XSCUGIC_CPU_PRIOR_OFFSET, 0xF0U);
  // XScuGic_CPUWriteReg(IntcInstancePtr, XSCUGIC_CONTROL_OFFSET, 0x07U);
  //
  // InstancePtr->IsReady = XIL_COMPONENT_IS_READY;
#else
  // Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig, 0);
  // if (Status != XST_SUCCESS) {
  //   return XST_FAILURE;
  // }

#endif
  // Xil_ExceptionInit();

  /*
   * Connect the interrupt controller interrupt handler to the hardware
   * interrupt handling logic in the processor.
   */
  Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
                               (Xil_ExceptionHandler)XScuGic_InterruptHandler,
                               IntcInstancePtr);
  // Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
  //                              (Xil_ExceptionHandler)TimerIntrHandler,
  //                              IntcInstancePtr);
  // Xil_ExceptionRegisterHandler(5, (Xil_ExceptionHandler)TimerIntrHandler,
  // NULL);
  /*
   * Connect the device driver handler that will be called when an
   * interrupt for the device occurs, the handler defined above performs
   * the specific interrupt processing for the device.
   */
  // Status = XScuGic_Connect(IntcInstancePtr, TimerIntrId,
  //                          (Xil_ExceptionHandler)TimerIntrHandler, 0);
  // if (Status != XST_SUCCESS) {
  //   return Status;
  // }
  IntcInstancePtr->Config->HandlerTable[TimerIntrId].Handler =
      (Xil_ExceptionHandler)TimerIntrHandler;
  IntcInstancePtr->Config->HandlerTable[TimerIntrId].CallBackRef = 0;
  /*
   * Enable the interrupt for the device.
   */
  // xil_printf("IntcConfig->DistBaseAddress: %p\r\n",
  //            IntcConfig->DistBaseAddress);
  // XScuGic_Enable(IntcInstancePtr, 29);
  scugic_dist_set_enable(Int_Id);
  // // XScuGic_DistWriteReg(basraddr, offset, data);
  // XScuGic_Enable(IntcInstancePtr, TimerIntrId);

  /*
   * Enable the timer interrupts for timer mode.
   */
  scutmr_set_enable_interrupt(1);

  /*
   * Enable interrupts in the Processor.
   */
  enable_intrupt();
  return XST_SUCCESS;
}

static void TimerIntrHandler(void *CallBackRef) {

  counter++;
  TimerExpired++;
  if (TimerExpired == 13) {
    scutmr_set_autoload(0);
  }
}

/*****************************************************************************/
/**
 *
 * This function disables the interrupts that occur for the device.
 *
 * @param	IntcInstancePtr is the pointer to the instance of XScuGic
 *		driver.
 * @param	TimerIntrId is the Interrupt Id for the device.
 *
 * @return	None.
 *
 * @note		None.
 *
 ******************************************************************************/
// static void TimerDisableIntrSystem(XScuGic *IntcInstancePtr, u16 TimerIntrId)
// {
//   /*
//    * Disconnect and disable the interrupt for the Timer.
//    */
//   scugic_dist_clear_enable(TimerIntrId);
// }
