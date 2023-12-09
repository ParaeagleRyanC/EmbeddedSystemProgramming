#include "clockDisplay.h"
#include "display.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>

#define X_CENTER DISPLAY_WIDTH / 2
#define Y_CENTER DISPLAY_HEIGHT / 2
#define TEXT_START_X (X_CENTER - (CLOCKDISPLAY_TEXT_SIZE * 22.5))
#define TEXT_START_Y (Y_CENTER - (CLOCKDISPLAY_TEXT_SIZE * 3.5))

#define HR_UP_X0 (X_CENTER - (CLOCKDISPLAY_TEXT_SIZE * 17.5))
#define HR_UP_X1 (MIN_UP_X1 - (CLOCKDISPLAY_TEXT_SIZE * 17.5))
#define HR_UP_X2 (HR_UP_X1 + (CLOCKDISPLAY_TEXT_SIZE * 10))
#define HR_UP_Y0 (Y_CENTER - (CLOCKDISPLAY_TEXT_SIZE * 15))
#define HR_UP_Y1 (Y_CENTER - (CLOCKDISPLAY_TEXT_SIZE * 6.5))
#define HR_UP_Y2 (Y_CENTER - (CLOCKDISPLAY_TEXT_SIZE * 6.5))
#define HR_DN_X0 (X_CENTER - (CLOCKDISPLAY_TEXT_SIZE * 17.5))
#define HR_DN_X1 (MIN_UP_X1 - (CLOCKDISPLAY_TEXT_SIZE * 17.5))
#define HR_DN_X2 (HR_UP_X1 + (CLOCKDISPLAY_TEXT_SIZE * 10))
#define HR_DN_Y0 (Y_CENTER + (CLOCKDISPLAY_TEXT_SIZE * 15))
#define HR_DN_Y1 (Y_CENTER + (CLOCKDISPLAY_TEXT_SIZE * 6.5))
#define HR_DN_Y2 (Y_CENTER + (CLOCKDISPLAY_TEXT_SIZE * 6.5))

#define MIN_UP_X0 X_CENTER
#define MIN_UP_X1 (X_CENTER - (CLOCKDISPLAY_TEXT_SIZE * 5))
#define MIN_UP_X2 (X_CENTER + (CLOCKDISPLAY_TEXT_SIZE * 5))
#define MIN_UP_Y0 (Y_CENTER - (CLOCKDISPLAY_TEXT_SIZE * 15))
#define MIN_UP_Y1 (Y_CENTER - (CLOCKDISPLAY_TEXT_SIZE * 6.5))
#define MIN_UP_Y2 (Y_CENTER - (CLOCKDISPLAY_TEXT_SIZE * 6.5))
#define MIN_DN_X0 X_CENTER
#define MIN_DN_X1 (X_CENTER - (CLOCKDISPLAY_TEXT_SIZE * 5))
#define MIN_DN_X2 (X_CENTER + (CLOCKDISPLAY_TEXT_SIZE * 5))
#define MIN_DN_Y0 (Y_CENTER + (CLOCKDISPLAY_TEXT_SIZE * 15))
#define MIN_DN_Y1 (Y_CENTER + (CLOCKDISPLAY_TEXT_SIZE * 6.5))
#define MIN_DN_Y2 (Y_CENTER + (CLOCKDISPLAY_TEXT_SIZE * 6.5))

#define SEC_UP_X0 (X_CENTER + (CLOCKDISPLAY_TEXT_SIZE * 17.5))
#define SEC_UP_X1 (MIN_UP_X1 + (CLOCKDISPLAY_TEXT_SIZE * 17.5))
#define SEC_UP_X2 (SEC_UP_X1 + (CLOCKDISPLAY_TEXT_SIZE * 10))
#define SEC_UP_Y0 (Y_CENTER - (CLOCKDISPLAY_TEXT_SIZE * 15))
#define SEC_UP_Y1 (Y_CENTER - (CLOCKDISPLAY_TEXT_SIZE * 6.5))
#define SEC_UP_Y2 (Y_CENTER - (CLOCKDISPLAY_TEXT_SIZE * 6.5))
#define SEC_DN_X0 (X_CENTER + (CLOCKDISPLAY_TEXT_SIZE * 17.5))
#define SEC_DN_X1 (MIN_UP_X1 + (CLOCKDISPLAY_TEXT_SIZE * 17.5))
#define SEC_DN_X2 (SEC_UP_X1 + (CLOCKDISPLAY_TEXT_SIZE * 10))
#define SEC_DN_Y0 (Y_CENTER + (CLOCKDISPLAY_TEXT_SIZE * 15))
#define SEC_DN_Y1 (Y_CENTER + (CLOCKDISPLAY_TEXT_SIZE * 6.5))
#define SEC_DN_Y2 (Y_CENTER + (CLOCKDISPLAY_TEXT_SIZE * 6.5))

#define HR_MAX 12
#define HR_MIN 1
#define HR_OVER 13
#define HR_MIN_SEC_ZERO 0
#define MIN_SEC_OVER 60
#define MIN_SEC_MAX 59
#define ARRAY_SIZE 9
#define CHAR_WIDTH 6
#define HR_PUSH 106
#define MIN_PUSH 213
#define ONE_TWENTIETH_SEC_DELAY 50

uint8_t hour;
uint8_t minute;
uint8_t second;
char currTime[ARRAY_SIZE];
char oldTime[ARRAY_SIZE];

void incrementHours() {
  hour++;
  // if the hour reaches 13 then rollover to 1
  if (hour == HR_OVER)
    hour = HR_MIN;
}

void decrementHours() {
  hour--;
  // if the hour reaches 0 then rollover to 12
  if (hour == HR_MIN_SEC_ZERO)
    hour = HR_MAX;
}

void incrementMinutes() {
  minute++;
  // if the minute reaches 60 then rollover to 00
  if (minute == MIN_SEC_OVER) {
    minute = HR_MIN_SEC_ZERO;
    incrementHours();
  }
}

void decrementMinutes() {
  minute--;
  // if the minute reaches 00 then rollover to 59
  if (minute == HR_MIN_SEC_ZERO)
    minute = MIN_SEC_MAX;
}

void incrementSeconds() {
  second++;
  // if the second reaches 60 then rollover to 00
  if (second == MIN_SEC_OVER) {
    second = HR_MIN_SEC_ZERO;
    incrementMinutes();
  }
}

void decrementSeconds() {
  second--;
  // if the second reaches 00 then rollover to 59
  if (second == HR_MIN_SEC_ZERO)
    second = MIN_SEC_MAX;
}

// Called only once - performs any necessary inits.
// This is a good place to draw the triangles and any other
// parts of the clock display that will never change.
void clockDisplay_init() {

  hour = HR_MAX;
  minute = MIN_SEC_MAX;
  second = MIN_SEC_MAX;

  display_init();
  display_fillScreen(DISPLAY_BLACK);
  display_setTextSize(CLOCKDISPLAY_TEXT_SIZE);
  display_setTextColorBg(DISPLAY_GREEN, DISPLAY_BLACK);

  // draw 6 triangles for inc and dec above and below hr, min, and sec
  display_fillTriangle(HR_UP_X0, HR_UP_Y0, HR_UP_X1, HR_UP_Y1, HR_UP_X2,
                       HR_UP_Y2, DISPLAY_GREEN);
  display_fillTriangle(HR_DN_X0, HR_DN_Y0, HR_DN_X1, HR_DN_Y1, HR_DN_X2,
                       HR_DN_Y2, DISPLAY_GREEN);
  display_fillTriangle(MIN_UP_X0, MIN_UP_Y0, MIN_UP_X1, MIN_UP_Y1, MIN_UP_X2,
                       MIN_UP_Y2, DISPLAY_GREEN);
  display_fillTriangle(MIN_DN_X0, MIN_DN_Y0, MIN_DN_X1, MIN_DN_Y1, MIN_DN_X2,
                       MIN_DN_Y2, DISPLAY_GREEN);
  display_fillTriangle(SEC_UP_X0, SEC_UP_Y0, SEC_UP_X1, SEC_UP_Y1, SEC_UP_X2,
                       SEC_UP_Y2, DISPLAY_GREEN);
  display_fillTriangle(SEC_DN_X0, SEC_DN_Y0, SEC_DN_X1, SEC_DN_Y1, SEC_DN_X2,
                       SEC_DN_Y2, DISPLAY_GREEN);

  // display the colons
  display_setCursor(TEXT_START_X, TEXT_START_Y);
  sprintf(oldTime, "%2hd:%02hd:%02hd", hour, minute, second);
  display_print(oldTime);
}

// Updates the time display with latest time, making sure to update only those
// digits that have changed since the last update. if forceUpdateAll is true,
// update all digits.
void clockDisplay_updateTimeDisplay(bool forceUpdateAll) {

  // if forceUpdateAll is true, update the entire time array
  if (forceUpdateAll) {
    for (uint8_t i = 0; i < ARRAY_SIZE; i++)
      oldTime[i] = currTime[i];
  }

  // otherwise update the differences between the old and current arrays
  else {
    sprintf(currTime, "%2hd:%02hd:%02hd", hour, minute, second);
    for (uint8_t i = 0; i < ARRAY_SIZE; i++) {
      if (currTime[i] != oldTime[i])
        oldTime[i] = currTime[i];
      display_drawChar(TEXT_START_X + (i * CHAR_WIDTH * CLOCKDISPLAY_TEXT_SIZE),
                       TEXT_START_Y, currTime[i], DISPLAY_GREEN, DISPLAY_BLACK,
                       CLOCKDISPLAY_TEXT_SIZE);
    }
  }
}

// Reads the touched coordinates and performs the increment or decrement,
// depending upon the touched region.
void clockDisplay_performIncDec() {

  int16_t x, y;
  uint8_t z;
  display_getTouchedPoint(&x, &y, &z);

  // if the touch is above the center of y axis,
  // perform increment on HR, MIN, or SEC
  // depending on where the screen is touched
  if (y < (Y_CENTER)) {
    if (x < HR_PUSH)
      incrementHours();
    else if (x < MIN_PUSH)
      incrementMinutes();
    else
      incrementSeconds();
  }

  // if the touch is below the center of y axis,
  // perform decrement on HR, MIN, or SEC
  // depending on where the screen is touched
  else if (y > (Y_CENTER)) {
    if (x < HR_PUSH)
      decrementHours();
    else if (x < MIN_PUSH)
      decrementMinutes();
    else
      decrementSeconds();
  }

  clockDisplay_updateTimeDisplay(false);
}

// Advances the time forward by 1 second and update the display.
void clockDisplay_advanceTimeOneSecond() {
  incrementSeconds();
  sprintf(currTime, "%2hd:%02hd:%02hd", hour, minute, second);
  clockDisplay_updateTimeDisplay(false);
}

// Run a test of clock-display functions.
void clockDisplay_runTest() {

  clockDisplay_init();

  // increment hours from 1 to 12 for 3 times
  for (uint8_t i = 0; i < 3; i++) {
    for (uint8_t i = 0; i < HR_MAX; i++) {
      incrementHours();
      clockDisplay_updateTimeDisplay(false);
      utils_msDelay(ONE_TWENTIETH_SEC_DELAY);
    }
  }

  // decrement hours from 12 to 1 for 2 times
  for (uint8_t i = 0; i < 2; i++) {
    for (uint8_t i = 0; i < HR_MAX; i++) {
      decrementHours();
      clockDisplay_updateTimeDisplay(false);
      utils_msDelay(ONE_TWENTIETH_SEC_DELAY);
    }
  }

  // increment minutes from 00 to 59 once
  for (uint8_t i = 0; i < MIN_SEC_MAX; i++) {
    incrementMinutes();
    clockDisplay_updateTimeDisplay(false);
    utils_msDelay(ONE_TWENTIETH_SEC_DELAY);
  }

  // decrement minutes from 59 to 00 once
  for (uint8_t i = 0; i < MIN_SEC_MAX; i++) {
    decrementMinutes();
    clockDisplay_updateTimeDisplay(false);
    utils_msDelay(ONE_TWENTIETH_SEC_DELAY);
  }

  // increment seconds from 00 to 59 once
  for (uint8_t i = 0; i < MIN_SEC_MAX; i++) {
    incrementSeconds();
    clockDisplay_updateTimeDisplay(false);
    utils_msDelay(ONE_TWENTIETH_SEC_DELAY);
  }

  // decrement seconds from 59 to 00 once
  for (uint8_t i = 0; i < MIN_SEC_MAX; i++) {
    decrementSeconds();
    clockDisplay_updateTimeDisplay(false);
    utils_msDelay(ONE_TWENTIETH_SEC_DELAY);
  }

  clockDisplay_init();

  // increment the clock 100 times by second
  for (uint8_t i = 0; i < 100; i++) {
    clockDisplay_advanceTimeOneSecond();
    clockDisplay_updateTimeDisplay(false);
    utils_msDelay(ONE_TWENTIETH_SEC_DELAY);
  }
}