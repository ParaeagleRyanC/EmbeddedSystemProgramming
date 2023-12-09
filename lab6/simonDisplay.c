
#include "simonDisplay.h"
#include "display.h"
#include "utils.h"
#include <stdbool.h>
#include <stdint.h>

#define DISPLAY_X_CENTER DISPLAY_WIDTH / 2
#define DISPLAY_Y_CENTER DISPLAY_HEIGHT / 2
#define RGN_0_2_BTN_X 50
#define RGN_1_3_BTN_X RGN_0_2_BTN_X + DISPLAY_X_CENTER
#define RGN_0_1_BTN_Y 30
#define RGN_2_3_BTN_Y RGN_0_1_BTN_Y + DISPLAY_Y_CENTER
#define RGN_0_2_SQR_X 20
#define RGN_1_3_SQR_X RGN_0_2_SQR_X + DISPLAY_X_CENTER
#define RGN_0_1_SQR_Y 0
#define RGN_2_3_SQR_Y DISPLAY_Y_CENTER
#define INDEX_ORIGIN 0
#define TEST_DELAY 60
#define TEXT_SIZE 2
#define TEST_START_TXT "Start the test by touching and releasing the buttons.\n"
#define TEST_DONE_TXT "Display Test terminated"

// this computes and return the region
int8_t simonDisplay_computeRegionNumber(int16_t x, int16_t y) {
  // top left
  if (x < DISPLAY_X_CENTER && y < DISPLAY_Y_CENTER)
    return SIMON_DISPLAY_REGION_0;
  // bottom left
  else if (x < DISPLAY_X_CENTER && y > DISPLAY_Y_CENTER)
    return SIMON_DISPLAY_REGION_2;
  // top right
  else if (x > DISPLAY_X_CENTER && y < DISPLAY_Y_CENTER)
    return SIMON_DISPLAY_REGION_1;
  // bottom right
  else
    return SIMON_DISPLAY_REGION_3;
}

// Draws a colored "button" that the user can touch.
// The colored button is centered in the region but does not fill the region.
// If erase argument is true, draws the button as black background to erase it.
void simonDisplay_drawButton(uint8_t regionNumber, bool erase) {
  // if erase is false, then draw!
  if (erase == SIMON_DISPLAY_DRAW) {
    // if regionNumber is 0, work on region 0
    if (regionNumber == SIMON_DISPLAY_REGION_0)
      display_fillRect(RGN_0_2_BTN_X, RGN_0_1_BTN_Y, SIMON_DISPLAY_BUTTON_WIDTH,
                       SIMON_DISPLAY_BUTTON_HEIGHT, DISPLAY_RED);
    // if regionNumber is 1, work on region 1
    if (regionNumber == SIMON_DISPLAY_REGION_1)
      display_fillRect(RGN_1_3_BTN_X, RGN_0_1_BTN_Y, SIMON_DISPLAY_BUTTON_WIDTH,
                       SIMON_DISPLAY_BUTTON_HEIGHT, DISPLAY_YELLOW);
    // if regionNumber is 2, work on region 2
    if (regionNumber == SIMON_DISPLAY_REGION_2)
      display_fillRect(RGN_0_2_BTN_X, RGN_2_3_BTN_Y, SIMON_DISPLAY_BUTTON_WIDTH,
                       SIMON_DISPLAY_BUTTON_HEIGHT, DISPLAY_BLUE);
    // if regionNumber is 3, work on region 3
    if (regionNumber == SIMON_DISPLAY_REGION_3)
      display_fillRect(RGN_1_3_BTN_X, RGN_2_3_BTN_Y, SIMON_DISPLAY_BUTTON_WIDTH,
                       SIMON_DISPLAY_BUTTON_HEIGHT, DISPLAY_GREEN);
  }
  // if erase is true, then erase!
  else {
    // if regionNumber is 0, work on region 0
    if (regionNumber == SIMON_DISPLAY_REGION_0)
      display_fillRect(RGN_0_2_BTN_X, RGN_0_1_BTN_Y, SIMON_DISPLAY_BUTTON_WIDTH,
                       SIMON_DISPLAY_BUTTON_HEIGHT, DISPLAY_BLACK);
    // if regionNumber is 1, work on region 1
    if (regionNumber == SIMON_DISPLAY_REGION_1)
      display_fillRect(RGN_1_3_BTN_X, RGN_0_1_BTN_Y, SIMON_DISPLAY_BUTTON_WIDTH,
                       SIMON_DISPLAY_BUTTON_HEIGHT, DISPLAY_BLACK);
    // if regionNumber is 2, work on region 2
    if (regionNumber == SIMON_DISPLAY_REGION_2)
      display_fillRect(RGN_0_2_BTN_X, RGN_2_3_BTN_Y, SIMON_DISPLAY_BUTTON_WIDTH,
                       SIMON_DISPLAY_BUTTON_HEIGHT, DISPLAY_BLACK);
    // if regionNumber is 3, work on region 3
    if (regionNumber == SIMON_DISPLAY_REGION_3)
      display_fillRect(RGN_1_3_BTN_X, RGN_2_3_BTN_Y, SIMON_DISPLAY_BUTTON_WIDTH,
                       SIMON_DISPLAY_BUTTON_HEIGHT, DISPLAY_BLACK);
  }
}

// Convenience function that draws all of the buttons.
void simonDisplay_drawAllButtons() {
  // iterate through each region and draw buttons
  for (uint8_t index = INDEX_ORIGIN; index < SIMON_DISPLAY_REGION_COUNT;
       index++)
    simonDisplay_drawButton(index, SIMON_DISPLAY_DRAW);
}

// Convenience function that erases all of the buttons.
void simonDisplay_eraseAllButtons() {
  // iterate through each region and erase buttons
  for (uint8_t index = INDEX_ORIGIN; index < SIMON_DISPLAY_REGION_COUNT;
       index++)
    simonDisplay_drawButton(index, SIMON_DISPLAY_ERASE);
}

// Draws a bigger square that completely fills the region.
// If the erase argument is true, it draws the square as black background to
// "erase" it.
void simonDisplay_drawSquare(uint8_t regionNo, bool erase) {
  // if erase is false, then draw!
  if (erase == SIMON_DISPLAY_DRAW) {
    // if regionNumber is 0, work on region 0
    if (regionNo == SIMON_DISPLAY_REGION_0)
      display_fillRect(RGN_0_2_SQR_X, RGN_0_1_SQR_Y, SIMON_DISPLAY_SQUARE_WIDTH,
                       SIMON_DISPLAY_SQUARE_HEIGHT, DISPLAY_RED);
    // if regionNumber is 1, work on region 1
    if (regionNo == SIMON_DISPLAY_REGION_1)
      display_fillRect(RGN_1_3_SQR_X, RGN_0_1_SQR_Y, SIMON_DISPLAY_SQUARE_WIDTH,
                       SIMON_DISPLAY_SQUARE_HEIGHT, DISPLAY_YELLOW);
    // if regionNumber is 2, work on region 2
    if (regionNo == SIMON_DISPLAY_REGION_2)
      display_fillRect(RGN_0_2_SQR_X, RGN_2_3_SQR_Y, SIMON_DISPLAY_SQUARE_WIDTH,
                       SIMON_DISPLAY_SQUARE_HEIGHT, DISPLAY_BLUE);
    // if regionNumber is 3, work on region 3
    if (regionNo == SIMON_DISPLAY_REGION_3)
      display_fillRect(RGN_1_3_SQR_X, RGN_2_3_SQR_Y, SIMON_DISPLAY_SQUARE_WIDTH,
                       SIMON_DISPLAY_SQUARE_HEIGHT, DISPLAY_GREEN);
  }
  // if erase is true, then erase!
  else {
    // if regionNumber is 0, work on region 0
    if (regionNo == SIMON_DISPLAY_REGION_0)
      display_fillRect(RGN_0_2_SQR_X, RGN_0_1_SQR_Y, SIMON_DISPLAY_SQUARE_WIDTH,
                       SIMON_DISPLAY_SQUARE_HEIGHT, DISPLAY_BLACK);
    // if regionNumber is 1, work on region 1
    if (regionNo == SIMON_DISPLAY_REGION_1)
      display_fillRect(RGN_1_3_SQR_X, RGN_0_1_SQR_Y, SIMON_DISPLAY_SQUARE_WIDTH,
                       SIMON_DISPLAY_SQUARE_HEIGHT, DISPLAY_BLACK);
    // if regionNumber is 2, work on region 2
    if (regionNo == SIMON_DISPLAY_REGION_2)
      display_fillRect(RGN_0_2_SQR_X, RGN_2_3_SQR_Y, SIMON_DISPLAY_SQUARE_WIDTH,
                       SIMON_DISPLAY_SQUARE_HEIGHT, DISPLAY_BLACK);
    // if regionNumber is 3, work on region 3
    if (regionNo == SIMON_DISPLAY_REGION_3)
      display_fillRect(RGN_1_3_SQR_X, RGN_2_3_SQR_Y, SIMON_DISPLAY_SQUARE_WIDTH,
                       SIMON_DISPLAY_SQUARE_HEIGHT, DISPLAY_BLACK);
  }
}

// Runs a brief demonstration of how buttons can be pressed and squares lit up
// to implement the user interface of the Simon game. The routine will continue
// to run until the touchCount has been reached, e.g., the user has touched the
// pad touchCount times.

// I used a busy-wait delay (utils_msDelay) that uses a for-loop and just blocks
// until the time has passed. When you implement the game, you CANNOT use this
// function as we discussed in class. Implement the delay using the non-blocking
// state-machine approach discussed in class.
void simonDisplay_runTest(uint16_t touchCount) {

  // display_init();

  // uint8_t regionNumber;

  // display_fillScreen(DISPLAY_BLACK);
  // display_setCursor(0, 0);
  // display_setTextSize(TEXT_SIZE);
  // display_setTextColor(DISPLAY_RED);
  // display_println(TEST_START_TXT);
  // utils_msDelay(TEST_DELAY);

  // display_fillScreen(DISPLAY_BLACK);
  // simonDisplay_drawAllButtons();

  // int16_t x, y;
  // uint8_t z;

  // for (uint8_t touches = INDEX_ORIGIN; touches < touchCount; touches++) {
  //   if (display_isTouched()) {
  //     display_clearOldTouchData();
  //     utils_msDelay(TEST_DELAY);
  //     display_getTouchedPoint(&x, &y, &z);
  //     regionNumber = simonDisplay_computeRegionNumber(x, y);
  //     simonDisplay_drawSquare(regionNumber, SIMON_DISPLAY_DRAW);
  //   } else {
  //     simonDisplay_drawSquare(regionNumber, SIMON_DISPLAY_ERASE);
  //     simonDisplay_drawButton(regionNumber, SIMON_DISPLAY_DRAW);
  //   }
  // }

  // display_fillScreen(DISPLAY_BLACK);
  // display_println(TEST_DONE_TXT);
}
