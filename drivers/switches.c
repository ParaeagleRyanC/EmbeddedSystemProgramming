/*
This software is provided for student assignment use in the Department of
Electrical and Computer Engineering, Brigham Young University, Utah, USA.

Users agree to not re-host, or redistribute the software, in source or binary
form, to other persons or other institutions. Users may modify and use the
source code for personal or educational use.

For questions, contact Brad Hutchings or Jeff Goeders, https://ece.byu.edu/
*/

#ifndef SWITCHES_H
#define SWITCHES_H

#include "switches.h"
#include "leds.h"
#include "xil_io.h"
#include "xparameters.h"
#include <stdint.h>

#define BASE_SWTC_ADDR XPAR_SLIDE_SWITCHES_BASEADDR
#define SWITCHES_INIT_STATUS_OK 1
#define SWITCHES_INIT_STATUS_FAIL 0
#define SWITCHES_SW0_MASK 0x1
#define SWITCHES_SW1_MASK 0x2
#define SWITCHES_SW2_MASK 0x4
#define SWITCHES_SW3_MASK 0x8
#define TRI_VALUE 0xF
#define TRI_OFFSET 0x04
#define DATA_OFFSET 0x0
#define LED_OFF 0x0

// Helper function to read GPIO registers.
int32_t switches_readGpioRegister(int32_t offset) {
  return Xil_In32(BASE_SWTC_ADDR + offset); // Returns the value at the address.
}

// Helper function to write GPIO registers.
void switches_writeGpioRegister(int32_t offset, int32_t value) {
  Xil_Out32(BASE_SWTC_ADDR + offset, value); // Writes value to the address.
}

// Initializes the SWITCHES driver software and hardware.
// Returns one of the STATUS values defined above.
int32_t switches_init() {
  // call write function
  switches_writeGpioRegister(TRI_OFFSET, TRI_VALUE);
  // Check if initialization is successful
  if (switches_readGpioRegister(TRI_OFFSET) == TRI_VALUE) {
    return SWITCHES_INIT_STATUS_OK;
  } else {
    return SWITCHES_INIT_STATUS_FAIL;
  }
}

// Returns the current value of all 4 switches as the lower 4 bits of the
// returned value. bit3 = SW3, bit2 = SW2, bit1 = SW1, bit0 = SW0.
int32_t switches_read() { return switches_readGpioRegister(DATA_OFFSET); }

// Runs a test of the switches. As you slide the switches, LEDs directly above
// the switches will illuminate. The test will run until all switches are slid
// upwards. When all 4 slide switches are slid upward, this function will
// return.
void switches_runTest() {

  switches_init();
  leds_init(1);

  // continue running until all switched are flipped
  while (switches_read() != TRI_VALUE) {
    leds_write(switches_read());
  }

  leds_write(LED_OFF);

  return;
}

#endif