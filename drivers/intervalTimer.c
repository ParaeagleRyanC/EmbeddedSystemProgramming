/*
This software is provided for student assignment use in the Department of
Electrical and Computer Engineering, Brigham Young University, Utah, USA.

Users agree to not re-host, or redistribute the software, in source or binary
form, to other persons or other institutions. Users may modify and use the
source code for personal or educational use.

For questions, contact Brad Hutchings or Jeff Goeders, https://ece.byu.edu/
*/

// Provides an API for accessing the three hardware timers that are installed
// in the ZYNQ fabric.

#include "intervalTimer.h"
#include "xil_io.h"
#include "xparameters.h"
#include <stdint.h>
#include <stdio.h>

#define TCSR0_OFFSET 0x00
#define TCSR1_OFFSET 0x10
#define TCR0_OFFSET 0x08
#define TCR1_OFFSET 0x18
#define TLR0_OFFSET 0x04
#define TLR1_OFFSET 0x14

#define ZERO 0x00
#define ONE 0x01
#define TIMER_AMOUNT 0x03
#define CASCADE_VALUE 0x800
#define UDT0_LOW 0xFFD
#define ENT0_HIGH 0x080
#define ENT0_LOW 0xF7F
#define LOAD_LOW 0xFDF
#define LOAD_HIGH 0x020
#define LEFT_SHIFT 31
#define CLOCK_FREQ 100000000

// Helper function to read GPIO registers.
uint32_t timer_readGpioRegister(uint32_t offset, uint32_t timerNumber) {

  // Returns the value at the address for TIMER_0
  if (timerNumber == INTERVAL_TIMER_TIMER_0) {
    return Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + offset);
  }
  // Returns the value at the address for TIMER_1
  else if (timerNumber == INTERVAL_TIMER_TIMER_1) {
    return Xil_In32(XPAR_AXI_TIMER_1_BASEADDR + offset);
  }
  // Returns the value at the address for TIMER_2
  else if (timerNumber == INTERVAL_TIMER_TIMER_2) {
    return Xil_In32(XPAR_AXI_TIMER_2_BASEADDR + offset);
  }
}

// Helper function to write GPIO registers.
void timer_writeGpioRegister(uint32_t offset, uint32_t value,
                             uint32_t timerNumber) {

  // Writes value to the address for TIMER_0
  if (timerNumber == INTERVAL_TIMER_TIMER_0) {
    Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + offset, value);
  }
  // Writes value to the address for TIMER_1
  else if (timerNumber == INTERVAL_TIMER_TIMER_1) {
    Xil_Out32(XPAR_AXI_TIMER_1_BASEADDR + offset, value);
  }
  // Writes value to the address for TIMER_2
  else if (timerNumber == INTERVAL_TIMER_TIMER_2) {
    Xil_Out32(XPAR_AXI_TIMER_2_BASEADDR + offset, value);
  }
}

// You must initialize the timers before you use them the first time.
// It is generally only called once but should not cause an error if it
// is called multiple times.
// timerNumber indicates which timer should be initialized.
// returns INTERVAL_TIMER_STATUS_OK if successful, some other value otherwise.
intervalTimer_status_t intervalTimer_init(uint32_t timerNumber) {

  // write a 0 to the TCSR0 register.
  timer_writeGpioRegister(TCSR0_OFFSET, ZERO, timerNumber);
  // write a 0 to the TCSR1 register.
  timer_writeGpioRegister(TCSR1_OFFSET, ZERO, timerNumber);
  // set the CASC bit high in the TCSR0 register
  timer_writeGpioRegister(TCSR0_OFFSET, CASCADE_VALUE, timerNumber);

  // return success or fail value
  if ((timer_readGpioRegister(TCSR0_OFFSET, timerNumber)) == CASCADE_VALUE) {
    return INTERVAL_TIMER_STATUS_OK;
  } else {
    return INTERVAL_TIMER_STATUS_FAIL;
  }
}

// This is a convenience function that initializes all interval timers.
// Simply calls intervalTimer_init() on all timers.
// returns INTERVAL_TIMER_STATUS_OK if successful, some other value otherwise.
intervalTimer_status_t intervalTimer_initAll() {

  // loop 3 times to initialize three timers
  for (uint8_t i = ZERO; i < TIMER_AMOUNT; i++) {
    intervalTimer_init(i);
  }
}

// This function starts the interval timer running.
// If the interval timer is already running, this function does nothing.
// timerNumber indicates which timer should start running.
void intervalTimer_start(uint32_t timerNumber) {

  // get a new value by setting ENT0 high then write to the register
  uint32_t valueToStart =
      (timer_readGpioRegister(TCSR0_OFFSET, timerNumber) | ENT0_HIGH);
  timer_writeGpioRegister(TCSR0_OFFSET, valueToStart, timerNumber);
}

// This function stops a running interval timer.
// If the interval time is currently stopped, this function does nothing.
// timerNumber indicates which timer should stop running.
void intervalTimer_stop(uint32_t timerNumber) {

  // get a new value by setting CASC high then write to the register
  uint32_t valueToStop =
      (timer_readGpioRegister(TCSR0_OFFSET, timerNumber) & (CASCADE_VALUE));
  timer_writeGpioRegister(TCSR0_OFFSET, valueToStop, timerNumber);
}

// This function is called whenever you want to reuse an interval timer.
// For example, say the interval timer has been used in the past, the user
// will call intervalTimer_reset() prior to calling intervalTimer_start().
// timerNumber indicates which timer should reset.
void intervalTimer_reset(uint32_t timerNumber) {

  // write a 0 into the TLR0 register
  timer_writeGpioRegister(TLR0_OFFSET, ZERO, timerNumber);

  // get a new value by setting LOAD high then write to the register
  uint32_t valueAfterLoadHigh =
      (timer_readGpioRegister(TCSR0_OFFSET, timerNumber) | LOAD_HIGH);
  timer_writeGpioRegister(TCSR0_OFFSET, valueAfterLoadHigh, timerNumber);

  // write a 0 into the TLR1 register
  timer_writeGpioRegister(TLR1_OFFSET, ZERO, timerNumber);

  // get a new value by setting LOAD high then write to the register
  valueAfterLoadHigh =
      (timer_readGpioRegister(TCSR1_OFFSET, timerNumber) | LOAD_HIGH);
  timer_writeGpioRegister(TCSR1_OFFSET, valueAfterLoadHigh, timerNumber);

  // re-initialize timer
  intervalTimer_init(timerNumber);
}

// Convenience function for intervalTimer_reset().
// Simply calls intervalTimer_reset() on all timers.
void intervalTimer_resetAll() {

  // loop 3 times to reset three timers
  for (uint8_t i = ZERO; i < TIMER_AMOUNT; i++) {
    intervalTimer_reset(i);
  }
}

// Runs a test on a single timer as indicated by the timerNumber argument.
// Returns INTERVAL_TIMER_STATUS_OK if successful, something else otherwise.
intervalTimer_status_t intervalTimer_test(uint32_t timerNumber) { return 0; }

// Convenience function that invokes test on all interval timers.
// Returns INTERVAL_TIMER_STATUS_OK if successful, something else otherwise.
intervalTimer_status_t intervalTimer_testAll() { return 0; }

// Use this function to ascertain how long a given timer has been running.
// Note that it should not be an error to call this function on a running timer
// though it usually makes more sense to call this after intervalTimer_stop()
// has been called. The timerNumber argument determines which timer is read.
double intervalTimer_getTotalDurationInSeconds(uint32_t timerNumber) {

  // get left 32 bits
  uint64_t leftBits = timer_readGpioRegister(TCR1_OFFSET, timerNumber)
                      << LEFT_SHIFT;
  // get right 32 bits
  uint64_t rightBits = timer_readGpioRegister(TCR0_OFFSET, timerNumber);
  // combine left and right bits
  uint64_t allBits = leftBits | rightBits;
  // get duration in second by cast allBits to double and dividing by the clock
  // frequency
  double durationInSeconds = (double)allBits / CLOCK_FREQ;

  return durationInSeconds;
}
