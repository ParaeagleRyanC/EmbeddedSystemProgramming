
#include "buttonHandler.h"
#include "display.h"
#include "simonDisplay.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define ADC_MAX 1
#define RESET 0
#define TURNED_ON true
#define TURNED_OFF false
#define RELEASED true
#define NOT_RELEASED false
#define ERR_MSG "ERROR!"

bool bhEnable;
bool btnReleased;
uint8_t adcCounter;
uint8_t regionNumber;

// variables to store touch data
int16_t x, y;
uint8_t z;

// states for the state machine
static enum buttonHandler_st_t {
  init_st,
  wait_for_touch_st,
  adc_settle_st,
  touched_st,
  released_st,
} currentState = init_st;

// Get the simon region numbers. See the source code for the region numbering
// scheme.
uint8_t buttonHandler_getRegionNumber() { return regionNumber; }

// Turn on the state machine. Part of the interlock.
void buttonHandler_enable() { bhEnable = TURNED_ON; }

// Turn off the state machine. Part of the interlock.
void buttonHandler_disable() { bhEnable = TURNED_OFF; }

// The only thing this function does is return a boolean flag set by the
// buttonHandler state machine. To wit: Once enabled, the buttonHandler
// state-machine first waits for a touch. Once a touch is detected, the
// buttonHandler state-machine computes the region-number for the touched area.
// Next, the buttonHandler state-machine waits until the player removes their
// finger. At this point, the state-machine should set a bool flag that
// indicates the the player has removed their finger. Once the buttonHandler()
// state-machine is disabled, it should clear this flag.
// All buttonHandler_releasedDetected() does is return the value of this flag.
// As such, the body of this function should only contain a single line of code.
// If this function does more than return a boolean set by the buttonHandler
// state machine, you are going about this incorrectly.
bool buttonHandler_releaseDetected() {
  if (btnReleased)
    return RELEASED;
  return NOT_RELEASED;
}

// Let you know that the buttonHander is waiting in the interlock state.
bool buttonHandler_isComplete() { return buttonHandler_releaseDetected(); }

// // Place this function before the tick() function in the file to keep the
// // compiler happy. All printed messages for states are provided here.
// #define INIT_ST_MSG "init_state\n"
// #define WAIT_FOR_TOUCH_ST_MSG "wait_for_touch_st\n"
// #define ADC_SETTLE_ST_MSG "adc_settle_st\n"
// #define TOUCHED_ST_MSG "touched_st\n"
// #define RELEASED_ST_MSG "released_st\n"
// // This is a debug state print routine. It will print the names of the states
// // each time tick() is called. It only prints states if they are different
// than
// // the previous state.
// static void bhDebugStatePrint() {
//   static enum buttonHandler_st_t previousState;
//   static bool firstPass = true;
//   // Only print the message if:
//   // 1. This the first pass and the value for previousState is unknown.
//   // 2. previousState != currentState - this prevents reprinting the same
//   state
//   // name over and over.
//   if (previousState != currentState || firstPass) {
//     firstPass = false; // previousState will be defined, firstPass is false.
//     previousState =
//         currentState;       // keep track of the last state that you were in.
//     switch (currentState) { // This prints messages based upon the state that
//                             // you were in.
//     case init_st:
//       printf(INIT_ST_MSG);
//       break;
//     case wait_for_touch_st:
//       printf(WAIT_FOR_TOUCH_ST_MSG);
//       break;
//     case adc_settle_st:
//       printf(ADC_SETTLE_ST_MSG);
//       break;
//     case touched_st:
//       printf(TOUCHED_ST_MSG);
//       break;
//     case released_st:
//       printf(RELEASED_ST_MSG);
//       break;
//     }
//   }
// }

// Standard init function.
void buttonHandler_init() {
  currentState = init_st;
  display_init();
  display_fillScreen(DISPLAY_BLACK);
}

// Standard tick function.
void buttonHandler_tick() {

  // print the current state on the terminal
  // bhDebugStatePrint();

  // transition first
  switch (currentState) {

  case init_st:
    // if buttonHandlerEnable flag is raised high, go to wait_for_touch_st
    if (bhEnable)
      currentState = wait_for_touch_st;
    // otherwise stay here
    else
      currentState = init_st;
    break;

  case wait_for_touch_st:
    // if display is touched, reset the adc counter and go to adc_settle_st
    if (display_isTouched()) {
      adcCounter = RESET;
      currentState = adc_settle_st;
    }
    // otherwise stay here
    else
      currentState = wait_for_touch_st;
    break;

  case adc_settle_st:
    // if the counter is less than max value, stay here
    if (adcCounter < ADC_MAX)
      currentState = adc_settle_st;
    // if display is touched and counter has reached max value, go to touched_st
    else if (display_isTouched() && adcCounter == ADC_MAX)
      currentState = touched_st;
    // if display is not touched and counter has reached max value, go back to
    // wait_for_touch_st
    else if (!display_isTouched() && adcCounter == ADC_MAX)
      currentState = wait_for_touch_st;
    break;

  case touched_st:
    // if the button handler enable flag is lowered, go back to init_st
    if (!bhEnable)
      currentState = init_st;
    // wait until touch is released then go to released_st
    // undraw the square and redraw the button as we go to released_st
    else if (!display_isTouched()) {
      simonDisplay_drawSquare(regionNumber, SIMON_DISPLAY_ERASE);
      simonDisplay_drawButton(regionNumber, SIMON_DISPLAY_DRAW);
      btnReleased = RELEASED;
      currentState = released_st;
    }
    break;

  case released_st:
    // if buttonHandlerEnable flag is lowered, set btnReleased to false and go
    // to init_st
    if (!bhEnable) {
      btnReleased = NOT_RELEASED;
      currentState = init_st;
    }
    break;

  default:
    printf(ERR_MSG);
    break;
  }

  // then actions
  switch (currentState) {
  case init_st:
    break;
  case wait_for_touch_st:
    break;
  case adc_settle_st:
    adcCounter++;
    break;
  case touched_st:
    display_getTouchedPoint(&x, &y, &z);
    regionNumber = simonDisplay_computeRegionNumber(x, y);
    simonDisplay_drawSquare(regionNumber, SIMON_DISPLAY_DRAW);
    break;
  case released_st:
    break;

  default:
    printf(ERR_MSG);
    break;
  }
}

// Allows an external controller to notify the buttonHandler that a time-out has
// occurred.
void buttonHandler_timeOutOccurred() {}
