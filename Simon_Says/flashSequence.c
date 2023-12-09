
#include "flashSequence.h"
#include "globals.h"
#include "simonDisplay.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>

#define RESET 0
#define OFFSET_BY_ONE 1
#define TURNED_ON true
#define TURNED_OFF false
#define COMPLETE true
#define NOT_COMPLETE false
#define FLASH_DELAY 3
#define ERR_MSG "ERROR!"

bool fsEnable;
bool flashIsComplete;
uint16_t iterationCounter;
uint8_t delayCounter;

// states for the state machine
static enum flashSequence_st_t {
  init_st,
  draw_st,
  erase_st,
  finish_st,
} currentState = init_st;

// Turns on the state machine. Part of the interlock.
void flashSequence_enable() { fsEnable = TURNED_ON; }

// Turns off the state machine. Part of the interlock.
void flashSequence_disable() { fsEnable = TURNED_OFF; }

// Other state machines can call this to determine if this state machine is
// finished.
bool flashSequence_isComplete() { return flashIsComplete; }

// // Place this function before the tick() function in the file to keep the
// // compiler happy. All printed messages for states are provided here.
// #define INIT_ST_MSG "init_state\n"
// #define DRAW_ST_MSG "draw_st\n"
// #define ERASE_ST_MSG "erase_st\n"
// #define FINISH_ST_MSG "finish_st\n"
// // This is a debug state print routine. It will print the names of the states
// // each time tick() is called. It only prints states if they are different
// than
// // the previous state.
// static void fsDebugStatePrint() {
//   static enum flashSequence_st_t previousState;
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
//     case draw_st:
//       printf(DRAW_ST_MSG);
//       break;
//     case erase_st:
//       printf(ERASE_ST_MSG);
//       break;
//     case finish_st:
//       printf(FINISH_ST_MSG);
//       break;
//     }
//   }
// }

// Standard init function.
void flashSequence_init() { currentState = init_st; }

void flashSequence_tick() {

  // print the current state on the terminal
  // fsDebugStatePrint();

  // transition first
  switch (currentState) {

  case init_st:
    // if flashSequenceEnable flag is raised high, go to draw_st
    if (fsEnable)
      currentState = draw_st;
    break;

  case draw_st:
    // if delayCounter reaches max value, draw the square, reset counter then go
    // to erase_st
    if (delayCounter == FLASH_DELAY) {
      simonDisplay_drawSquare(globals_getSequenceValue(iterationCounter),
                              SIMON_DISPLAY_DRAW);
      delayCounter = RESET;
      currentState = erase_st;
    }
    // otherwise stay here
    else
      currentState = draw_st;
    break;

  case erase_st:
    // if delayCounter reaches max value and iterationCounter matches
    // iterationLength erase the square, increment iterationLength, reset
    // counter and set flashIsComplete to true
    if (delayCounter == FLASH_DELAY &&
        iterationCounter ==
            globals_getSequenceIterationLength() - OFFSET_BY_ONE) {
      simonDisplay_drawSquare(globals_getSequenceValue(iterationCounter),
                              SIMON_DISPLAY_ERASE);
      delayCounter = RESET;
      flashIsComplete = COMPLETE;
      currentState = finish_st;
    }
    // if delayCounter reaches max value but iterationCounter does not match
    // iterationLength erase the square, increment iterationCounter, reset
    // counter then go back to draw_st
    else if (delayCounter == FLASH_DELAY &&
             iterationCounter != globals_getSequenceIterationLength()) {
      simonDisplay_drawSquare(globals_getSequenceValue(iterationCounter),
                              SIMON_DISPLAY_ERASE);
      iterationCounter++;
      delayCounter = RESET;
      currentState = draw_st;
    }
    break;

  case finish_st:
    // if flashSequenceEnable flag is lowered, set flashIsComplete to true and
    // stay in this state
    if (!fsEnable) {
      flashIsComplete = COMPLETE;
      currentState = finish_st;
    }
    // otherwise go to init_st
    else
      currentState = init_st;
    break;

  default:
    printf(ERR_MSG);
    break;
  }

  // then actions
  switch (currentState) {

  // set flashIsComplete to false and iterationCounter to 0
  case init_st:
    flashIsComplete = NOT_COMPLETE;
    iterationCounter = RESET;
    break;

  // increment delayCounter
  case draw_st:
    delayCounter++;
    break;

  // increment delayCounter
  case erase_st:
    delayCounter++;
    break;

  case finish_st:
    break;

  default:
    printf(ERR_MSG);
    break;
  }
}