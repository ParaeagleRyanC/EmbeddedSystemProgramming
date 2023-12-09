#include "cardsMatchDisplay.h"
#include "cardsMatchGlobals.h"
#include "display.h"
#include "utils.h"

uint8_t cardsMatchDisplay_computeRegionNumber(int16_t x, int16_t y) {
  if (y < ROW_1) {
    if (x < COLUMN_1)
      return A1;
    else if (x < COLUMN_2)
      return A2;
    else if (x < COLUMN_3)
      return A3;
    else if (x < COLUMN_4)
      return A4;
    else if (x < COLUMN_5)
      return A5;
    else
      return A6;
  } else if (y < ROW_2) {
    if (x < COLUMN_1)
      return B1;
    else if (x < COLUMN_2)
      return B2;
    else if (x < COLUMN_3)
      return B3;
    else if (x < COLUMN_4)
      return B4;
    else if (x < COLUMN_5)
      return B5;
    else
      return B6;
  } else if (y < ROW_3) {
    if (x < COLUMN_1)
      return C1;
    else if (x < COLUMN_2)
      return C2;
    else if (x < COLUMN_3)
      return C3;
    else if (x < COLUMN_4)
      return C4;
    else if (x < COLUMN_5)
      return C5;
    else
      return C6;
  } else {
    if (x < COLUMN_1)
      return D1;
    else if (x < COLUMN_2)
      return D2;
    else if (x < COLUMN_3)
      return D3;
    else if (x < COLUMN_4)
      return D4;
    else if (x < COLUMN_5)
      return D5;
    else
      return D6;
  }
}

void cardsMatchDisplay_showOrCoverCard(uint8_t region, bool cover,
                                       uint16_t color) {
  if (cover == false) {
    switch (region) {
    case A1:
      display_fillRect(BOARD_ORIGIN, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_1, Y_1, CIRCLE_RADIUS, color);
      break;

    case A2:
      display_fillRect(COLUMN_1, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_2, Y_1, CIRCLE_RADIUS, color);
      break;

    case A3:
      display_fillRect(COLUMN_2, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_3, Y_1, CIRCLE_RADIUS, color);
      break;

    case A4:
      display_fillRect(COLUMN_3, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_4, Y_1, CIRCLE_RADIUS, color);
      break;

    case A5:
      display_fillRect(COLUMN_4, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_5, Y_1, CIRCLE_RADIUS, color);
      break;

    case A6:
      display_fillRect(COLUMN_5, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_6, Y_1, CIRCLE_RADIUS, color);
      break;

    case B1:
      display_fillRect(BOARD_ORIGIN, ROW_1, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_1, Y_2, CIRCLE_RADIUS, color);
      break;

    case B2:
      display_fillRect(COLUMN_1, ROW_1, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_2, Y_2, CIRCLE_RADIUS, color);
      break;

    case B3:
      display_fillRect(COLUMN_2, ROW_1, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_3, Y_2, CIRCLE_RADIUS, color);
      break;

    case B4:
      display_fillRect(COLUMN_3, ROW_1, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_4, Y_2, CIRCLE_RADIUS, color);
      break;

    case B5:
      display_fillRect(COLUMN_4, ROW_1, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_5, Y_2, CIRCLE_RADIUS, color);
      break;

    case B6:
      display_fillRect(COLUMN_5, ROW_1, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_6, Y_2, CIRCLE_RADIUS, color);
      break;

    case C1:
      display_fillRect(BOARD_ORIGIN, ROW_2, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_1, Y_3, CIRCLE_RADIUS, color);
      break;

    case C2:
      display_fillRect(COLUMN_1, ROW_2, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_2, Y_3, CIRCLE_RADIUS, color);
      break;

    case C3:
      display_fillRect(COLUMN_2, ROW_2, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_3, Y_3, CIRCLE_RADIUS, color);
      break;

    case C4:
      display_fillRect(COLUMN_3, ROW_2, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_4, Y_3, CIRCLE_RADIUS, color);
      break;

    case C5:
      display_fillRect(COLUMN_4, ROW_2, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_5, Y_3, CIRCLE_RADIUS, color);
      break;

    case C6:
      display_fillRect(COLUMN_5, ROW_2, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_6, Y_3, CIRCLE_RADIUS, color);
      break;

    case D1:
      display_fillRect(BOARD_ORIGIN, ROW_3, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_1, Y_4, CIRCLE_RADIUS, color);
      break;

    case D2:
      display_fillRect(COLUMN_1, ROW_3, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_2, Y_4, CIRCLE_RADIUS, color);
      break;

    case D3:
      display_fillRect(COLUMN_2, ROW_3, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_3, Y_4, CIRCLE_RADIUS, color);
      break;

    case D4:
      display_fillRect(COLUMN_3, ROW_3, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_4, Y_4, CIRCLE_RADIUS, color);
      break;

    case D5:
      display_fillRect(COLUMN_4, ROW_3, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_5, Y_4, CIRCLE_RADIUS, color);
      break;

    case D6:
      display_fillRect(COLUMN_5, ROW_3, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      display_fillCircle(X_6, Y_4, CIRCLE_RADIUS, color);
      break;
    }
  }

  else {
    switch (region) {
    case A1:
      display_fillRect(BOARD_ORIGIN, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case A2:
      display_fillRect(COLUMN_1, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case A3:
      display_fillRect(COLUMN_2, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case A4:
      display_fillRect(COLUMN_3, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case A5:
      display_fillRect(COLUMN_4, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case A6:
      display_fillRect(COLUMN_5, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case B1:
      display_fillRect(BOARD_ORIGIN, ROW_1, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case B2:
      display_fillRect(COLUMN_1, ROW_1, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case B3:
      display_fillRect(COLUMN_2, ROW_1, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case B4:
      display_fillRect(COLUMN_3, ROW_1, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case B5:
      display_fillRect(COLUMN_4, ROW_1, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case B6:
      display_fillRect(COLUMN_5, ROW_1, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case C1:
      display_fillRect(BOARD_ORIGIN, ROW_2, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case C2:
      display_fillRect(COLUMN_1, ROW_2, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case C3:
      display_fillRect(COLUMN_2, ROW_2, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case C4:
      display_fillRect(COLUMN_3, ROW_2, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case C5:
      display_fillRect(COLUMN_4, ROW_2, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case C6:
      display_fillRect(COLUMN_5, ROW_2, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case D1:
      display_fillRect(BOARD_ORIGIN, ROW_3, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case D2:
      display_fillRect(COLUMN_1, ROW_3, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case D3:
      display_fillRect(COLUMN_2, ROW_3, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case D4:
      display_fillRect(COLUMN_3, ROW_3, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case D5:
      display_fillRect(COLUMN_4, ROW_3, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;

    case D6:
      display_fillRect(COLUMN_5, ROW_3, CARD_WIDTH - OFFSET,
                       CARD_LEGNTH - OFFSET, DISPLAY_LIGHT_GRAY);
      break;
    }
  }
}

void cardsMatchDisplay_showAllCards() {
  for (uint8_t index = INDEX_ORIGIN; index < BOARD_SIZE; index++) {
    cardsMatchDisplay_showOrCoverCard(index, false,
                                      globals_getCardColor(index));
  }
}

void cardsMatchDisplay_coverAllCards() {
  for (uint8_t index = INDEX_ORIGIN; index < BOARD_SIZE; index++) {
    cardsMatchDisplay_showOrCoverCard(index, false, DISPLAY_LIGHT_GRAY);
  }
}

void cardsMatchDisplay_removeCard(uint8_t region) {
  switch (region) {
  case A1:
    display_fillRect(BOARD_ORIGIN, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                     CARD_LEGNTH - OFFSET, DISPLAY_BLACK);
    break;

  case A2:
    display_fillRect(COLUMN_1, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                     CARD_LEGNTH - OFFSET, DISPLAY_BLACK);
    break;

  case A3:
    display_fillRect(COLUMN_2, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                     CARD_LEGNTH - OFFSET, DISPLAY_BLACK);
    break;

  case A4:
    display_fillRect(COLUMN_3, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                     CARD_LEGNTH - OFFSET, DISPLAY_BLACK);
    break;

  case A5:
    display_fillRect(COLUMN_4, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                     CARD_LEGNTH - OFFSET, DISPLAY_BLACK);
    break;

  case A6:
    display_fillRect(COLUMN_5, BOARD_ORIGIN, CARD_WIDTH - OFFSET,
                     CARD_LEGNTH - OFFSET, DISPLAY_BLACK);
    break;

  case B1:
    display_fillRect(BOARD_ORIGIN, ROW_1, CARD_WIDTH - OFFSET,
                     CARD_LEGNTH - OFFSET, DISPLAY_BLACK);
    break;

  case B2:
    display_fillRect(COLUMN_1, ROW_1, CARD_WIDTH - OFFSET, CARD_LEGNTH - OFFSET,
                     DISPLAY_BLACK);
    break;

  case B3:
    display_fillRect(COLUMN_2, ROW_1, CARD_WIDTH - OFFSET, CARD_LEGNTH - OFFSET,
                     DISPLAY_BLACK);
    break;

  case B4:
    display_fillRect(COLUMN_3, ROW_1, CARD_WIDTH - OFFSET, CARD_LEGNTH - OFFSET,
                     DISPLAY_BLACK);
    break;

  case B5:
    display_fillRect(COLUMN_4, ROW_1, CARD_WIDTH - OFFSET, CARD_LEGNTH - OFFSET,
                     DISPLAY_BLACK);
    break;

  case B6:
    display_fillRect(COLUMN_5, ROW_1, CARD_WIDTH - OFFSET, CARD_LEGNTH - OFFSET,
                     DISPLAY_BLACK);
    break;

  case C1:
    display_fillRect(BOARD_ORIGIN, ROW_2, CARD_WIDTH - OFFSET,
                     CARD_LEGNTH - OFFSET, DISPLAY_BLACK);
    break;

  case C2:
    display_fillRect(COLUMN_1, ROW_2, CARD_WIDTH - OFFSET, CARD_LEGNTH - OFFSET,
                     DISPLAY_BLACK);
    break;

  case C3:
    display_fillRect(COLUMN_2, ROW_2, CARD_WIDTH - OFFSET, CARD_LEGNTH - OFFSET,
                     DISPLAY_BLACK);
    break;

  case C4:
    display_fillRect(COLUMN_3, ROW_2, CARD_WIDTH - OFFSET, CARD_LEGNTH - OFFSET,
                     DISPLAY_BLACK);
    break;

  case C5:
    display_fillRect(COLUMN_4, ROW_2, CARD_WIDTH - OFFSET, CARD_LEGNTH - OFFSET,
                     DISPLAY_BLACK);
    break;

  case C6:
    display_fillRect(COLUMN_5, ROW_2, CARD_WIDTH - OFFSET, CARD_LEGNTH - OFFSET,
                     DISPLAY_BLACK);
    break;

  case D1:
    display_fillRect(BOARD_ORIGIN, ROW_3, CARD_WIDTH - OFFSET,
                     CARD_LEGNTH - OFFSET, DISPLAY_BLACK);
    break;

  case D2:
    display_fillRect(COLUMN_1, ROW_3, CARD_WIDTH - OFFSET, CARD_LEGNTH - OFFSET,
                     DISPLAY_BLACK);
    break;

  case D3:
    display_fillRect(COLUMN_2, ROW_3, CARD_WIDTH - OFFSET, CARD_LEGNTH - OFFSET,
                     DISPLAY_BLACK);
    break;

  case D4:
    display_fillRect(COLUMN_3, ROW_3, CARD_WIDTH - OFFSET, CARD_LEGNTH - OFFSET,
                     DISPLAY_BLACK);
    break;

  case D5:
    display_fillRect(COLUMN_4, ROW_3, CARD_WIDTH - OFFSET, CARD_LEGNTH - OFFSET,
                     DISPLAY_BLACK);
    break;

  case D6:
    display_fillRect(COLUMN_5, ROW_3, CARD_WIDTH - OFFSET, CARD_LEGNTH - OFFSET,
                     DISPLAY_BLACK);
    break;
  }
}

void cardsMatchDisplay_removeAllCards() { display_fillScreen(DISPLAY_BLACK); }

void cardsMatchDisplay_runTest() {
  cardsMatchDisplay_showAllCards();
  utils_msDelay(300);
  cardsMatchDisplay_coverAllCards();
  utils_msDelay(300);
  cardsMatchDisplay_showOrCoverCard(0, false, globals_getCardColor(0));
  utils_msDelay(300);
  cardsMatchDisplay_showOrCoverCard(0, true, globals_getCardColor(0));
  utils_msDelay(300);
  cardsMatchDisplay_removeCard(0);
  utils_msDelay(300);
  cardsMatchDisplay_removeAllCards();
  utils_msDelay(300);
}