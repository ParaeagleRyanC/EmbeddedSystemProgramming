
#include "simonControl.h"
#include "buttonHandler.h"
#include "display.h"
#include "flashSequence.h"
#include "globals.h"
#include "simonDisplay.h"
#include "verifySequence.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TURNED_ON true
#define TURNED_OFF false
#define GAME_IS_OVER true
#define GAME_NOT_OVER false

#define STRING_LENGTH 500
#define RESET 0
#define INCREMENT 1
#define START_SEQUENCE 4
#define START_ITERATION_LENGTH 1
#define MESSAGE_DISPLAY_TIME 25
#define YAY_TXT_SIZE 5
#define TRY_AGAIN_TXT_SIZE 2
#define END_GAME_TXT_SIZE 2
#define YAY_X 100
#define YAY_Y 110
#define TRY_AGAIN_X 45
#define TRY_AGAIN_Y 110
#define END_GAME_X 50
#define END_GAME_Y 110
#define SIMON_X 60
#define SIMON_Y 90
#define TOUCH_PLAY_X 80
#define TOUCH_PLAY_Y 140
#define LENGTH_X 105
#define LENGTH_Y 170
#define SIMON_TXT_SIZE 3
#define INTRO 2
#define SIMON_MSG "SIMON SIMON"
#define TOUCH_TO_PLAY_MSG "Touch to Play"
#define YAY_MSG "YAY!"
#define TOUCH_TO_TRY_AGAIN_MSG "Touch to Try Again"
#define ERR_MSG "Error!"

uint8_t controlSequenceArray[GLOBALS_MAX_FLASH_SEQUENCE];
uint16_t msgCounter;
uint16_t sequenceCounter;
uint64_t randomCounter;
bool isGameOver;
bool scEnable;
char string[STRING_LENGTH];

// states for the state machine
static enum simonControl_st_t {
  init_st,
  intro_st,
  touch_to_play_st,
  flash_st,
  verify_st,
  success_st,
  continue_to_play_st,
  end_game_st,
} currentState = init_st;

// a function to generate random sequence and store it in the array
void seqeunceGenerator() {
  srand(randomCounter);
  // iterate through the sequence array and store random value
  for (uint8_t index = RESET; index < sequenceCounter; index++) {
    controlSequenceArray[index] = rand() % SIMON_DISPLAY_REGION_COUNT;
  }
}

// a function to display intro message
void display_intro() {
  display_fillScreen(DISPLAY_BLACK);
  display_setCursor(SIMON_X, SIMON_Y);
  display_setTextSize(SIMON_TXT_SIZE);
  display_println(SIMON_MSG);
  display_setCursor(TOUCH_PLAY_X, TOUCH_PLAY_Y);
  display_setTextSize(INTRO);
  display_println(TOUCH_TO_PLAY_MSG);
  display_setCursor(LENGTH_X, LENGTH_Y);
  sprintf(string, "Length: %d", globals_getSequenceLength());
  display_println(string);
}

// a function to display "YAY!"
void display_yay() {
  display_fillScreen(DISPLAY_BLACK);
  display_setCursor(YAY_X, YAY_Y);
  display_setTextSize(YAY_TXT_SIZE);
  display_println(YAY_MSG);
}

// a function to display "Touch to Try Again"
void display_try_again() {
  display_fillScreen(DISPLAY_BLACK);
  display_setCursor(TRY_AGAIN_X, TRY_AGAIN_Y);
  display_setTextSize(TRY_AGAIN_TXT_SIZE);
  display_println(TOUCH_TO_TRY_AGAIN_MSG);
}

// a function to display last sequence message as the game ends
void display_last_sequence() {
  display_fillScreen(DISPLAY_BLACK);
  display_setCursor(END_GAME_X, END_GAME_Y);
  display_setTextSize(END_GAME_TXT_SIZE);
  sprintf(string, "Last Sequence: %d/%d", globals_getSequenceIterationLength(),
          globals_getSequenceLength());
  display_println(string);
}

// a function that reset things for a new game
void init() {
  msgCounter = RESET;
  sequenceCounter = START_SEQUENCE;
  randomCounter = RESET;
  scEnable = TURNED_OFF;
  isGameOver = GAME_NOT_OVER;
  globals_setSequenceIterationLength(START_ITERATION_LENGTH);
  globals_setSequence(controlSequenceArray, sequenceCounter);
}

// Enables the control state machine.
void simonControl_enable() { scEnable = TURNED_ON; }

// Disables the controll state machine.
void simonControl_disable() { scEnable = TURNED_OFF; }

// If you want to stop the game after a mistake, check this function after each
// tick.
bool simonControl_isGameOver() { return isGameOver; }

// Use this to set the sequence length. This the sequence set by this function
// will only be recognized when the controller passes through its init state.
void simonControl_setSequenceLength(uint16_t length) {}

// Place this function before the tick() function in the file to keep the
// compiler happy. All printed messages for states are provided here.
// #define INIT_ST_MSG "init_state\n"
// #define INTRO_ST_MSG "intro_st\n"
// #define TOUCH_TO_PLAY_ST_MSG "touch_to_play_st\n"
// #define FLASH_ST_MSG "flash_st\n"
// #define VERIFY_ST_MSG "verify_st\n"
// #define SUCCESS_ST_MSG "success_st\n"
// #define CONTINUE_TO_PLAY_ST_MSG "continue_to_play_st\n"
// #define END_GAME_ST_MSG "end_game_st\n"
// This is a debug state print routine. It will print the names of the states
// each time tick() is called. It only prints states if they are different
// than the previous state.
// static void scDebugStatePrint() {
//   static enum simonControl_st_t previousState;
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
//     case intro_st:
//       printf(INTRO_ST_MSG);
//       break;
//     case touch_to_play_st:
//       printf(TOUCH_TO_PLAY_ST_MSG);
//       break;
//     case flash_st:
//       printf(FLASH_ST_MSG);
//       break;
//     case verify_st:
//       printf(VERIFY_ST_MSG);
//       break;
//     case success_st:
//       printf(SUCCESS_ST_MSG);
//       break;
//     case continue_to_play_st:
//       printf(CONTINUE_TO_PLAY_ST_MSG);
//       break;
//     case end_game_st:
//       printf(END_GAME_ST_MSG);
//       break;
//     }
//   }
// }

// Used to init the state machine. Always provided though it may not be
// necessary.
void simonControl_init() { currentState = init_st; }

// Standard tick function.
void simonControl_tick() {

  // print the current state on the terminal
  // scDebugStatePrint();

  // increment the random counter each tick
  randomCounter++;

  // transition first
  switch (currentState) {
  case init_st:
    // go to intro state if simon control enable flag is raised
    if (scEnable) {
      init();
      currentState = intro_st;
    }
    break;

  case intro_st:
    currentState = touch_to_play_st;
    break;

  case touch_to_play_st:
    // go to flash state if the screen is touched
    // otherwise stay here
    if (display_isTouched()) {
      flashSequence_enable();
      seqeunceGenerator();
      globals_setSequence(controlSequenceArray, sequenceCounter);
      display_fillScreen(DISPLAY_BLACK);
      currentState = flash_st;
    }
    break;

  case flash_st:
    // if flash is complete, go to verify state
    if (flashSequence_isComplete()) {
      flashSequence_disable();
      verifySequence_enable();
      simonDisplay_drawAllButtons();
      currentState = verify_st;
    }
    break;

  case verify_st:
    // if there is a time out error or input error, go to end game state
    if (verifySequence_isTimeOutError() || verifySequence_isUserInputError()) {
      verifySequence_disable();
      msgCounter = RESET;
      isGameOver = GAME_IS_OVER;
      display_last_sequence();
      currentState = end_game_st;
    }
    // check if verify is complete
    else if (verifySequence_isComplete()) {
      verifySequence_disable();
      // if iteration length is less than sequence length
      // increment the interation length and go back to flash state
      if (globals_getSequenceIterationLength() < globals_getSequenceLength()) {
        flashSequence_enable();
        globals_setSequenceIterationLength(
            globals_getSequenceIterationLength() + INCREMENT);
        display_fillScreen(DISPLAY_BLACK);
        currentState = flash_st;
      }
      // otherwise the player succeeded so go to success state
      else {
        display_yay();
        currentState = success_st;
      }
    }
    break;

  case success_st:
    // display the messgae for a couple seconds
    if (msgCounter < MESSAGE_DISPLAY_TIME)
      currentState = success_st;
    // once reached desired display time, go to continue_to_play_st
    else {
      msgCounter = RESET;
      display_try_again();
      currentState = continue_to_play_st;
    }
    break;

  case continue_to_play_st:
    // if the screen is touched, go to flash state to keep playing
    if (display_isTouched()) {
      sequenceCounter++;
      flashSequence_enable();
      seqeunceGenerator();
      globals_setSequence(controlSequenceArray, sequenceCounter);
      display_fillScreen(DISPLAY_BLACK);
      globals_setSequenceIterationLength(1);
      currentState = flash_st;
    }
    // if screen is not touched and message has been displayed for long enough
    // go to end game state
    else if (!display_isTouched() && msgCounter == MESSAGE_DISPLAY_TIME) {
      msgCounter = RESET;
      isGameOver = GAME_IS_OVER;
      display_last_sequence();
      currentState = end_game_st;
    }
    break;

  case end_game_st:
    // display the messgae for a couple seconds
    if (msgCounter < MESSAGE_DISPLAY_TIME)
      currentState = end_game_st;
    // wait till simon control enable flag is lowered
    // then go to intro state
    else if (!scEnable) {
      init();
      currentState = intro_st;
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

  case intro_st:
    display_intro();
    break;

  case touch_to_play_st:
    break;

  case flash_st:
    break;

  case verify_st:
    break;

  case success_st:
    msgCounter++;
    break;

  case continue_to_play_st:
    msgCounter++;
    break;

  case end_game_st:
    msgCounter++;
    break;

  default:
    printf(ERR_MSG);
    break;
  }
}