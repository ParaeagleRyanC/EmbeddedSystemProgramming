#include "ticTacToeControl.h"
#include "buttons.h"
#include "display.h"
#include "minimax.h"
#include "ticTacToeDisplay.h"
#include <stdio.h>

#define ADC_COUNTER_MAX_VALUE 1
#define BOSS_OR_ROOKIE_MAX_VALUE 60
#define INSTRUCTION_MAX_VALUE 40
#define RESET_TO_ZERO 0
#define TEXT_SIZE 2
#define START_NEW_GAME 0x1
#define LINE_1_X 30
#define LINE_1_Y 80
#define LINE_2_X 120
#define LINE_2_Y 100
#define LINE_3_X 30
#define LINE_3_Y 120
#define LINE_4_X 90
#define LINE_4_Y 140
#define DRAW_SHAPE false
#define PLAYER_ASSIGNED true
#define ERR_MSG "FAILED!"
#define SQUARE_USED "Square used, pick another square!\n"
#define INSTRUCTION_LINE_1 "Touch board to play X"
#define INSTRUCTION_LINE_2 "---or---"
#define INSTRUCTION_LINE_3 "wait for the computer"
#define INSTRUCTION_LINE_4 "and play O."

static uint8_t adcCounter;
static uint8_t bossOrRookieCounter;
static uint8_t instructionCounter;
static uint8_t row;
static uint8_t column;
static bool rookieIsX;
static bool playerAssigned;
static bool validSquare;
static minimax_board_t myBoard;

// print instruction on the screen
void printInstruction() {
  display_setTextColor(DISPLAY_GREEN);
  display_setTextSize(TEXT_SIZE);
  display_setCursor(LINE_1_X, LINE_1_Y);
  display_println(INSTRUCTION_LINE_1);
  display_setCursor(LINE_2_X, LINE_2_Y);
  display_println(INSTRUCTION_LINE_2);
  display_setCursor(LINE_3_X, LINE_3_Y);
  display_println(INSTRUCTION_LINE_3);
  display_setCursor(LINE_4_X, LINE_4_Y);
  display_println(INSTRUCTION_LINE_4);
}

// remove instruction from the screen
void eraseInstruction() {
  display_setTextColor(DISPLAY_BLACK);
  display_setTextSize(TEXT_SIZE);
  display_setCursor(LINE_1_X, LINE_1_Y);
  display_println(INSTRUCTION_LINE_1);
  display_setCursor(LINE_2_X, LINE_2_Y);
  display_println(INSTRUCTION_LINE_2);
  display_setCursor(LINE_3_X, LINE_3_Y);
  display_println(INSTRUCTION_LINE_3);
  display_setCursor(LINE_4_X, LINE_4_Y);
  display_println(INSTRUCTION_LINE_4);
}

// check if the square the player chose is used already
bool isSquareUsed(uint8_t row, uint8_t column) {
  // check if the square is empty
  if (myBoard.squares[row][column] == MINIMAX_EMPTY_SQUARE)
    return false;
  return true;
}

// clear the board by drawing
void clearBoard() {
  // iterate through each sqaure
  for (uint8_t row = RESET_TO_ZERO; row < MINIMAX_BOARD_ROWS; row++) {
    for (uint8_t column = RESET_TO_ZERO; column < MINIMAX_BOARD_COLUMNS;
         column++) {
      // if the square is X, call the drawX funtion
      if (myBoard.squares[row][column] == MINIMAX_X_SQUARE)
        ticTacToeDisplay_drawX(row, column, !DRAW_SHAPE);
      // if the square is O, call the drawO funtion
      else if (myBoard.squares[row][column] == MINIMAX_O_SQUARE)
        ticTacToeDisplay_drawO(row, column, !DRAW_SHAPE);
    }
  }
}

// States for the controller state machine.
enum tttControl_st_t {
  init_st, // Start here, transition out of this state on the first tick.
  display_instruction_st, // display the instructions
  boss_or_rookie_st,  // waiting for player to touch the screen at the start of
                      // the game
  adc_settle_st,      // wait for adc to settle
  boss_move_st,       // computer makes the move
  wait_for_rookie_st, // wait for the player to touch the screen for the next
                      // move
  rookie_move_st,     // rookie makes the move
  game_over_st,       // game is over, transition to wait_reset
  reset_draw_board_st // clear the board and draw the board
} currentState;

// Place this function before the tick() function in the file to keep the
// compiler happy. All printed messages for states are provided here.
#define INIT_ST_MSG "init state\n"
#define DISPLAY_INSTRUCTION_ST_MSG "display_instruction_st\n"
#define BOSS_OR_ROOKIE_ST_MSG "boss_or_rookie_st\n"
#define ADC_SETTLE_ST_MSG "adc_settle_st\n"
#define BOSS_MOVE_ST_MSG "boss_move_st\n"
#define WAIT_FOR_ROOKIE_ST_MSG "wait_for_rookie_st\n"
#define ROOKIE_MOVE_ST_MSG "rookie_move_st\n"
#define GAME_OVER_ST_MSG "game_over_st\n"
#define RESET_DRAW_BOARD_ST_MSG "reset_draw_board_st\n"
// This is a debug state print routine. It will print the names of the states
// each time tick() is called. It only prints states if they are different than
// the previous state.
void debugStatePrint() {
  static enum tttControl_st_t previousState;
  static bool firstPass = true;
  // Only print the message if:
  // 1. This the first pass and the value for previousState is unknown.
  // 2. previousState != currentState - this prevents reprinting the same state
  // name over and over.
  if (previousState != currentState || firstPass) {
    firstPass = false; // previousState will be defined, firstPass is false.
    previousState =
        currentState;       // keep track of the last state that you were in.
    switch (currentState) { // This prints messages based upon the state that
                            // you were in.
    case init_st:
      printf(INIT_ST_MSG);
      break;
    case display_instruction_st:
      printf(DISPLAY_INSTRUCTION_ST_MSG);
      break;
    case boss_or_rookie_st:
      printf(BOSS_OR_ROOKIE_ST_MSG);
      break;
    case adc_settle_st:
      printf(ADC_SETTLE_ST_MSG);
      break;
    case boss_move_st:
      printf(BOSS_MOVE_ST_MSG);
      break;
    case wait_for_rookie_st:
      printf(WAIT_FOR_ROOKIE_ST_MSG);
      break;
    case rookie_move_st:
      printf(ROOKIE_MOVE_ST_MSG);
      break;
    case game_over_st:
      printf(GAME_OVER_ST_MSG);
      break;
    case reset_draw_board_st:
      printf(RESET_DRAW_BOARD_ST_MSG);
      break;
    }
  }
}

// Initialize the tic-tac-toe conroller state machine before tick function
void ticTacToeControl_init() {
  currentState = init_st;
  display_init();
  display_fillScreen(DISPLAY_BLACK);
}

// Tick the tic-tac-toe conroller state machine
void ticTacToeControl_tick() {

  // print the current state on the terminal
  debugStatePrint();

  // Perform state update first.
  switch (currentState) {

  // initialization
  case init_st:
    printInstruction();
    currentState = display_instruction_st;
    break;

  // display instructions
  case display_instruction_st:
    // stay in this state until instruction is displayed for 2 seconds
    if (instructionCounter < INSTRUCTION_MAX_VALUE)
      currentState = display_instruction_st;
    // goes to reset_draw_board_st when instruction is displayed for 2 seconds
    else if (instructionCounter == INSTRUCTION_MAX_VALUE) {
      eraseInstruction();
      currentState = reset_draw_board_st;
    }
    break;

  // determine either the player or the computer goes first
  case boss_or_rookie_st:

    // if screen is touched, goes to adc_settle state
    if (display_isTouched()) {
      rookieIsX = true;
      currentState = adc_settle_st;
      adcCounter = RESET_TO_ZERO;
    }

    // if screen is not touched and the counter is less than 3 seconds
    // stay in this state
    else if (bossOrRookieCounter < BOSS_OR_ROOKIE_MAX_VALUE)
      currentState = boss_or_rookie_st;

    // if screen is not touched and the counter reached 3 seconds
    // goes to wait_for_rookie_st
    else if (bossOrRookieCounter == BOSS_OR_ROOKIE_MAX_VALUE) {
      rookieIsX = false;
      playerAssigned = PLAYER_ASSIGNED;
      myBoard.squares[row][column] = MINIMAX_X_SQUARE;
      ticTacToeDisplay_drawX(row, column, DRAW_SHAPE);
      currentState = wait_for_rookie_st;
    }
    break;

  // what for 50 ms to ensure a touch is valid
  case adc_settle_st:

    // if screen is touched and the counter reached 50 ms
    // goes to rookie_move_st
    if (display_isTouched() && adcCounter == ADC_COUNTER_MAX_VALUE) {
      playerAssigned = PLAYER_ASSIGNED;
      currentState = rookie_move_st;
    }

    // if screen is not touched, player is not assigned, and the counter reached
    // 50 ms goes back to boss_or_rookie_st
    else if (!display_isTouched() && adcCounter == ADC_COUNTER_MAX_VALUE &&
             playerAssigned == !PLAYER_ASSIGNED)
      currentState = boss_or_rookie_st;

    // if screen is not touched and the counter reached 50 ms
    // goes to wait_for_rookie_st
    else if (!display_isTouched() && adcCounter == ADC_COUNTER_MAX_VALUE)
      currentState = wait_for_rookie_st;

    // if the counter is less the 50 ms, stay in this state
    else if (adcCounter < ADC_COUNTER_MAX_VALUE)
      currentState = adc_settle_st;
    break;

  // wait for the player to touch the scree after the computer goes
  case wait_for_rookie_st:
    // if the screen is touched, goes to adc_settle_st
    if (display_isTouched()) {
      adcCounter = RESET_TO_ZERO;
      currentState = adc_settle_st;
    }
    // otherwise stay in this state
    else
      currentState = wait_for_rookie_st;
    break;

  // computer makes the move
  case boss_move_st:

    // if game is not over, goes to wait_for_rookie_st
    if (!minimax_isGameOver(minimax_computeBoardScore(&myBoard, !rookieIsX)))
      currentState = wait_for_rookie_st;
    // otherwise goes to game_over_st
    else
      currentState = game_over_st;
    break;

  // player makes the move
  case rookie_move_st:

    // if game is over, goes to game_over_st
    if (minimax_isGameOver(minimax_computeBoardScore(&myBoard, rookieIsX)))
      currentState = game_over_st;

    // if game is not over, check if the square chose is valid
    // if yes, goes to boss_move_st
    else if (validSquare)
      currentState = boss_move_st;

    // if game is not over and the square chose is invalid
    // goes back to wait_for_rookie_st
    else {
      currentState = wait_for_rookie_st;
      printf(SQUARE_USED);
    }
    break;

  // game is over when reached this state
  case game_over_st:
    // if BTN0 is pressed, goes to reset_draw_board_st
    if (buttons_read() == START_NEW_GAME)
      currentState = reset_draw_board_st;
    // otherwise stays in this state
    else
      currentState = game_over_st;
    break;

  // reset the board here and goes to boss_or_rookie_st next
  case reset_draw_board_st:
    currentState = boss_or_rookie_st;
    break;

  default:
    printf(ERR_MSG);
    break;
  }

  // Perform state action next.
  switch (currentState) {

  // reset instructionCounter
  case init_st:
    instructionCounter = RESET_TO_ZERO;
    break;

  // increment instructionCounter
  case display_instruction_st:
    instructionCounter++;
    break;

  // increment bossOrRookieCounter
  case boss_or_rookie_st:
    bossOrRookieCounter++;
    break;

  // increment adcCounter
  case adc_settle_st:
    adcCounter++;
    break;

  // does nothing here
  case wait_for_rookie_st:
    break;

  // compute the move and draw on the board
  case boss_move_st:
    minimax_computeNextMove(&myBoard, !rookieIsX, &row, &column);
    // draw X or O according to who plays what
    if (rookieIsX) {
      myBoard.squares[row][column] = MINIMAX_O_SQUARE;
      ticTacToeDisplay_drawO(row, column, DRAW_SHAPE);
    } else {
      myBoard.squares[row][column] = MINIMAX_X_SQUARE;
      ticTacToeDisplay_drawX(row, column, DRAW_SHAPE);
    }
    break;

  // player makes the move here
  case rookie_move_st:

    ticTacToeDisplay_touchScreenComputeBoardRowColumn(&row, &column);

    // check if the square chose is used
    if (isSquareUsed(row, column)) {
      validSquare = false;
      break;
    } else
      validSquare = true;

    // draw X or O according to who plays what
    if (rookieIsX) {
      myBoard.squares[row][column] = MINIMAX_X_SQUARE;
      ticTacToeDisplay_drawX(row, column, DRAW_SHAPE);
    } else {
      myBoard.squares[row][column] = MINIMAX_O_SQUARE;
      ticTacToeDisplay_drawO(row, column, DRAW_SHAPE);
    }
    break;

  // does nothing here
  case game_over_st:
    break;

  // reset the board and counters
  case reset_draw_board_st:
    bossOrRookieCounter = RESET_TO_ZERO;
    adcCounter = RESET_TO_ZERO;
    playerAssigned = !PLAYER_ASSIGNED;
    clearBoard();
    minimax_initBoard(&myBoard);
    ticTacToeDisplay_drawBoardLines();
    break;

  default:
    printf(ERR_MSG);
    break;
  }
}