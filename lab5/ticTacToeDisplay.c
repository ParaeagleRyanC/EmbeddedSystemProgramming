#include "ticTacToeDisplay.h"
#include "buttons.h"
#include "display.h"
#include "stdio.h"
#include "switches.h"
#include "utils.h"

#define X_ORIGIN 0
#define Y_ORIGIN 0
#define X_L_LINE DISPLAY_WIDTH / 3
#define X_R_LINE 2 * (DISPLAY_WIDTH / 3)
#define Y_UP_LINE (DISPLAY_HEIGHT / 3)
#define Y_DW_LINE 2 * (DISPLAY_HEIGHT / 3)
#define X_X_BASE DISPLAY_WIDTH / 12
#define X_Y_BASE DISPLAY_HEIGHT / 12
#define O_X_BASE DISPLAY_WIDTH / 6
#define O_Y_BASE DISPLAY_HEIGHT / 6
#define CIRCLE_RADIUS 30
#define COLUMN_0 0
#define COLUMN_1 1
#define COLUMN_2 2
#define ROW_0 0
#define ROW_1 1
#define ROW_2 2
#define TEXT_SIZE 2
#define O_PLAYS 0x1
#define X_PLAYS 0x0
#define SCREEN_CLEAR 0x1
#define GAME_TERMINATES 0x2
#define DELAY_TO_SETTLE 50

// Inits the tic-tac-toe display, draws the lines that form the board.
void ticTacToeDisplay_init() {
  display_init();
  display_fillScreen(DISPLAY_BLACK);
  display_setTextSize(TEXT_SIZE);
  display_setTextColor(DISPLAY_GREEN);
  ticTacToeDisplay_drawBoardLines();
}

// Draws an X at the specified row and column.
// erase == true means to erase the X by redrawing it as background. erase ==
// false, draw the X as foreground.
void ticTacToeDisplay_drawX(uint8_t row, uint8_t column, bool erase) {

  // assign coordinates values
  uint16_t x_start = X_X_BASE + X_L_LINE * column;
  uint16_t x_end = (X_L_LINE * (column + COLUMN_1)) - X_X_BASE;
  uint16_t y_1_start = X_Y_BASE + Y_UP_LINE * row;
  uint16_t y_1_end = (Y_UP_LINE * (row + ROW_1)) - X_Y_BASE;
  uint16_t y_2_start = (Y_UP_LINE * (row + ROW_1)) - X_Y_BASE;
  uint16_t y_2_end = X_Y_BASE + Y_UP_LINE * row;

  // if erase is false then draw X
  if (erase == false) {
    display_drawLine(x_start, y_1_start, x_end, y_1_end, DISPLAY_GREEN);
    display_drawLine(x_start, y_2_start, x_end, y_2_end, DISPLAY_GREEN);
  }
  // otherwise draw black
  else {
    display_drawLine(x_start, y_1_start, x_end, y_1_end, DISPLAY_BLACK);
    display_drawLine(x_start, y_2_start, x_end, y_2_end, DISPLAY_BLACK);
  }
}

// Draws an O at the specified row and column.
// erase == true means to erase the O by redrawing it as background. erase ==
// false, draw the O as foreground.
void ticTacToeDisplay_drawO(uint8_t row, uint8_t column, bool erase) {

  // assign coordinates values
  uint16_t x = O_X_BASE + X_L_LINE * column;
  uint16_t y = O_Y_BASE + Y_UP_LINE * row;

  // if erase is false then draw O
  if (erase == false)
    display_drawCircle(x, y, CIRCLE_RADIUS, DISPLAY_GREEN);
  // otherwise draw black
  else
    display_drawCircle(x, y, CIRCLE_RADIUS, DISPLAY_BLACK);
}

// After a touch has been detected and after the proper delay, this sets the row
// and column arguments according to where the user touched the board.
void ticTacToeDisplay_touchScreenComputeBoardRowColumn(uint8_t *row,
                                                       uint8_t *column) {

  // get the touch point data
  int16_t x, y;
  uint8_t z;
  display_getTouchedPoint(&x, &y, &z);

  // check for where y is and assign row to respective value
  if (y < Y_UP_LINE)
    *row = ROW_0;
  else if (y < Y_DW_LINE)
    *row = ROW_1;
  else
    *row = ROW_2;

  // check for where x is and assign column to respective value
  if (x < X_L_LINE)
    *column = COLUMN_0;
  else if (x < X_R_LINE)
    *column = COLUMN_1;
  else
    *column = COLUMN_2;
}

// Runs a test of the display. Does the following.
// Draws the board. Each time you touch one of the screen areas, the screen will
// paint an X or an O, depending on whether switch 0 (SW0) is slid up (O) or
// down (X). When BTN0 is pushed, the screen is cleared. The test terminates
// when BTN1 is pushed.
void ticTacToeDisplay_runTest() {

  uint8_t row;
  uint8_t column;

  // initialize ticTacToeDisplay, buttons, and switches
  ticTacToeDisplay_init();
  buttons_init();
  switches_init();

  // keep running until test terminates
  while (buttons_read() != GAME_TERMINATES) {

    // check if display is touched, proceed if true
    if (display_isTouched()) {
      display_clearOldTouchData();
      utils_msDelay(DELAY_TO_SETTLE);
      ticTacToeDisplay_touchScreenComputeBoardRowColumn(&row, &column);
      // if the switch is up then draw O, otherwise draw X
      if (switches_read() == O_PLAYS)
        ticTacToeDisplay_drawO(row, column, false);
      else if (switches_read() == X_PLAYS)
        ticTacToeDisplay_drawX(row, column, false);
    }

    // if BTN0 is pushed, clear screen
    if (buttons_read() == SCREEN_CLEAR)
      ticTacToeDisplay_init();

    // if BTN1 is pushed, terminate the test
    if (buttons_read() == GAME_TERMINATES) {
      display_fillScreen(DISPLAY_BLACK);
      display_println("Test terminated.");
    }
  }
}

// This will draw the four board lines.
void ticTacToeDisplay_drawBoardLines() {
  display_drawFastVLine(X_L_LINE, Y_ORIGIN, DISPLAY_HEIGHT, DISPLAY_GREEN);
  display_drawFastVLine(X_R_LINE, Y_ORIGIN, DISPLAY_HEIGHT, DISPLAY_GREEN);
  display_drawFastHLine(X_ORIGIN, Y_UP_LINE, DISPLAY_WIDTH, DISPLAY_GREEN);
  display_drawFastHLine(X_ORIGIN, Y_DW_LINE, DISPLAY_WIDTH, DISPLAY_GREEN);
}
