
#include "verifySequence.h"
#include "buttonHandler.h"
#include "display.h"
#include "globals.h"
#include "simonDisplay.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define TURNED_ON true
#define TURNED_OFF false
#define COMPLETE true
#define NOT_COMPLETE false
#define IS_TIME_OUT true
#define NOT_TIME_OUT false
#define PLAYER_IS_SMART false
#define PLAYER_NOT_SMART true
#define RESET 0
#define TIME_OUT 25
#define ERR_MSG "ERROR!"

bool vsEnable;
bool verifyIsComplete;
bool isTimeOut;
bool playIsNotSmart;
uint8_t sequenceIndex;
uint16_t timeOutCounter;

// states for the state machine
static enum verifySequence_st_t {
  init_st,
  wait_touch_st,
  verify_st,
  finish_st,
} currentState = init_st;

// State machine will run when enabled.
void verifySequence_enable() { vsEnable = TURNED_ON; }

// This is part of the interlock. You disable the state-machine and then enable
// it again.
void verifySequence_disable() { vsEnable = TURNED_OFF; }

// Used to detect if there has been a time-out error.
bool verifySequence_isTimeOutError() { return isTimeOut; }

// Used to detect if the user tapped the incorrect sequence.
bool verifySequence_isUserInputError() { return playIsNotSmart; }

// Used to detect if the verifySequence state machine has finished verifying.
bool verifySequence_isComplete() { return verifyIsComplete; }

// // Place this function before the tick() function in the file to keep the
// // compiler happy. All printed messages for states are provided here.
// #define INIT_ST_MSG "init_state\n"
// #define WAIT_TOUCH_ST_MSG "wait_touch_st\n"
// #define VERIFY_ST_MSG "verify_st\n"
// #define FINISH_ST_MSG "finish_st\n"
// This is a debug state print routine. It will print the names of the states
// each time tick() is called. It only prints states if they are different than
// the previous state.
// static void vsDebugStatePrint() {
//   static enum verifySequence_st_t previousState;
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
//     case wait_touch_st:
//       printf(WAIT_TOUCH_ST_MSG);
//       break;
//     case verify_st:
//       printf(VERIFY_ST_MSG);
//       break;
//     case finish_st:
//       printf(FINISH_ST_MSG);
//       break;
//     }
//   }
// }

// Standard init function.
void verifySequence_init() { currentState = init_st; }

// Standard tick function.
void verifySequence_tick() {

  // print the current state on the terminal
  // vsDebugStatePrint();

  // transition first
  switch (currentState) {
  case init_st:
    // if verify sequence enable flag is high, go to wait_touch_st
    if (vsEnable) {
      buttonHandler_enable();
      timeOutCounter = RESET;
      currentState = wait_touch_st;
    }
    break;

  case wait_touch_st:
    // if a release is detected, go to verify_st
    if (buttonHandler_releaseDetected())
      currentState = verify_st;
    // if no input is detected for too long, go to finish_st
    else if (timeOutCounter >= TIME_OUT) {
      buttonHandler_disable();
      isTimeOut = IS_TIME_OUT;
      verifyIsComplete = COMPLETE;
      display_fillScreen(DISPLAY_BLACK);
      currentState = finish_st;
    }
    break;

  case verify_st:
    // if the player tapped the right color, increment the sequence index
    if (globals_getSequenceValue(sequenceIndex) ==
        buttonHandler_getRegionNumber()) {
      sequenceIndex++;
      // if sequence index matches iteration length plus 1
      // we are done so go to finish_st
      if (sequenceIndex == globals_getSequenceIterationLength()) {
        verifyIsComplete = COMPLETE;
        simonDisplay_eraseAllButtons();
        currentState = finish_st;
      }
      // otherwise go back to wait_touch_st
      else {
        timeOutCounter = RESET;
        buttonHandler_enable();
        currentState = wait_touch_st;
      }
    }
    // if the tapped the wrong color, go to finish_st
    else {
      playIsNotSmart = PLAYER_NOT_SMART;
      verifyIsComplete = COMPLETE;
      simonDisplay_eraseAllButtons();
      currentState = finish_st;
    }
    break;

  case finish_st:
    // wait till the flag is lowered then go to init_st
    if (!vsEnable)
      currentState = init_st;
    break;

  default:
    printf(ERR_MSG);
    break;
  }

  // then actions
  switch (currentState) {

  // reset things here
  case init_st:
    vsEnable = TURNED_OFF;
    isTimeOut = NOT_TIME_OUT;
    playIsNotSmart = PLAYER_IS_SMART;
    verifyIsComplete = NOT_COMPLETE;
    timeOutCounter = RESET;
    sequenceIndex = RESET;
    break;

  // increment timeOutCounter
  case wait_touch_st:
    timeOutCounter++;
    break;

  case verify_st:
    buttonHandler_disable();
    break;

  case finish_st:
    break;

  default:
    printf(ERR_MSG);
    break;
  }
}