/*
This software is provided for student assignment use in the Department of
Electrical and Computer Engineering, Brigham Young University, Utah, USA.

Users agree to not re-host, or redistribute the software, in source or binary
form, to other persons or other institutions. Users may modify and use the
source code for personal or educational use.

For questions, contact Brad Hutchings or Jeff Goeders, https://ece.byu.edu/
*/

#ifndef BUTTONS_H
#define BUTTONS_H

#include "buttons.h"
#include "display.h"
#include "xil_io.h"
#include "xparameters.h"
#include <stdint.h>

#define BASE_PUSH_BTN_ADDR XPAR_PUSH_BUTTONS_BASEADDR
#define BUTTONS_INIT_STATUS_OK 1
#define BUTTONS_INIT_STATUS_FAIL 0
#define BUTTONS_BTN0_MASK 0x1
#define BUTTONS_BTN1_MASK 0x2
#define BUTTONS_BTN2_MASK 0x4
#define BUTTONS_BTN3_MASK 0x8
#define TRI_VALUE 0xF
#define TRI_OFFSET 0x04
#define DATA_OFFSET 0x0
#define BTNS_ALL_ON 0xF
#define BTNS_ALL_OFF 0x0

#define BTN0_X DISPLAY_WIDTH * 0.75
#define BTN1_X DISPLAY_WIDTH * 0.5
#define BTN2_X DISPLAY_WIDTH * 0.25
#define BTN3_X 0x0
#define RECT_Y 0x0
#define RECT_WIDTH DISPLAY_WIDTH / 4
#define RECT_HIEGHT DISPLAY_HEIGHT / 2
#define X_CURSOR 18
#define Y_CURSOR 50
#define TEXT_SIZE 2
#define TEXT0 "BTN0"
#define TEXT1 "BTN1"
#define TEXT2 "BTN2"
#define TEXT3 "BTN3"

// Helper function to read GPIO registers.
int32_t buttons_readGpioRegister(int32_t offset) {
  return Xil_In32(BASE_PUSH_BTN_ADDR + offset);
}

// Helper function to write GPIO registers.
void buttons_writeGpioRegister(int32_t offset, int32_t value) {
  Xil_Out32(BASE_PUSH_BTN_ADDR + offset, value); // Writes value to the address.
}

// declaration of buttons_test function
void buttons_test(int8_t currentBtn, int8_t tempBtn);

// Initializes the button driver software and hardware.
// Returns one of the defined status values (above).
int32_t buttons_init() {
  // Call write function
  buttons_writeGpioRegister(TRI_OFFSET, TRI_VALUE);
  // Check if initialization is successful
  if (buttons_readGpioRegister(TRI_OFFSET) == TRI_VALUE) {
    return BUTTONS_INIT_STATUS_OK;
  } else {
    return BUTTONS_INIT_STATUS_FAIL;
  }
}

// Returns the current value of all 4 buttons as the lower 4 bits of the
// returned value. bit3 = BTN3, bit2 = BTN2, bit1 = BTN1, bit0 = BTN0.
int32_t buttons_read() { return buttons_readGpioRegister(DATA_OFFSET); }

// Runs a test of the buttons. As you push the buttons, graphics and messages
// will be written to the LCD panel. The test will until all 4 pushbuttons are
// simultaneously pressed.
void buttons_runTest() {
  int8_t currentBtn = 0x0;
  int8_t tempBtn = 0x0;

  display_init();
  display_fillScreen(DISPLAY_BLACK);

  // continue running until all buttons are pressed
  while (buttons_read() != BTNS_ALL_ON) {
    currentBtn = buttons_read();

    // check if current button is different from previous buttom
    if (currentBtn != tempBtn) {
      buttons_test(currentBtn, tempBtn);
    }

    tempBtn = currentBtn;
  }

  // turn off the screen (go black) before terminating
  buttons_test(BTNS_ALL_OFF, tempBtn);

  return;
}

void buttons_test(int8_t currentBtn, int8_t tempBtn) {

  int8_t tempValue = (currentBtn ^ tempBtn);

  // check if the button changed value for BTN0
  if ((tempValue & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) {
    // bitwise AND with current button value
    int8_t newTempValue = tempValue & currentBtn;
    // update screen if button is pressed
    if ((newTempValue & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) {
      display_fillRect(BTN0_X, RECT_Y, RECT_WIDTH, RECT_HIEGHT, DISPLAY_YELLOW);
      display_setCursor((BTN0_X + X_CURSOR), Y_CURSOR);
      display_setTextColor(DISPLAY_BLACK);
      display_setTextSize(TEXT_SIZE);
      display_println(TEXT0);
    }
    // else draw it black
    else {
      display_fillRect(BTN0_X, RECT_Y, RECT_WIDTH, RECT_HIEGHT, DISPLAY_BLACK);
    }
  }

  // check if the button changed value for BTN1
  if ((tempValue & BUTTONS_BTN1_MASK) == BUTTONS_BTN1_MASK) {
    // bitwise AND with current button value
    int8_t newTempValue = tempValue & currentBtn;
    // update screen if button is pressed
    if ((newTempValue & BUTTONS_BTN1_MASK) == BUTTONS_BTN1_MASK) {
      display_fillRect(BTN1_X, RECT_Y, RECT_WIDTH, RECT_HIEGHT, DISPLAY_GREEN);
      display_setCursor((BTN1_X + X_CURSOR), Y_CURSOR);
      display_setTextColor(DISPLAY_BLACK);
      display_setTextSize(TEXT_SIZE);
      display_println(TEXT1);
    }
    // else draw it black
    else {
      display_fillRect(BTN1_X, RECT_Y, RECT_WIDTH, RECT_HIEGHT, DISPLAY_BLACK);
    }
  }

  // check if the button changed value for BTN2
  if ((tempValue & BUTTONS_BTN2_MASK) == BUTTONS_BTN2_MASK) {
    // bitwise and with current button value
    int8_t newTempValue = tempValue & currentBtn;
    // update screen if button is pressed
    if ((newTempValue & BUTTONS_BTN2_MASK) == BUTTONS_BTN2_MASK) {
      display_fillRect(BTN2_X, RECT_Y, RECT_WIDTH, RECT_HIEGHT, DISPLAY_RED);
      display_setCursor((BTN2_X + X_CURSOR), Y_CURSOR);
      display_setTextColor(DISPLAY_BLACK);
      display_setTextSize(TEXT_SIZE);
      display_println(TEXT2);
    }
    // else draw it black
    else {
      display_fillRect(BTN2_X, RECT_Y, RECT_WIDTH, RECT_HIEGHT, DISPLAY_BLACK);
    }
  }

  // check if the button changed value for BTN3
  if ((tempValue & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) {
    // bitwise and with current button value
    int8_t newTempValue = tempValue & currentBtn;
    // update screen if button is pressed
    if ((newTempValue & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) {
      display_fillRect(BTN3_X, RECT_Y, RECT_WIDTH, RECT_HIEGHT, DISPLAY_BLUE);
      display_setCursor((BTN3_X + X_CURSOR), Y_CURSOR);
      display_setTextColor(DISPLAY_BLACK);
      display_setTextSize(TEXT_SIZE);
      display_println(TEXT3);
    }
    // else draw it black
    else {
      display_fillRect(BTN3_X, RECT_Y, RECT_WIDTH, RECT_HIEGHT, DISPLAY_BLACK);
    }
  }

  return;
}

#endif