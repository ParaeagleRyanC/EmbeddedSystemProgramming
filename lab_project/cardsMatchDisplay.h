#ifndef CARDSMATCHDISPLAY_H_
#define CARDSMATCHDISPLAY_H_

#include <stdbool.h>
#include <stdint.h>

#define CARD_WIDTH 53.33
#define CARD_LEGNTH 60

#define BOARD_ORIGIN 0
#define ROW_1 DISPLAY_HEIGHT / 4
#define ROW_2 ROW_1 * 2
#define ROW_3 ROW_1 * 3
#define ROW_4 DISPLAY_HEIGHT
#define COLUMN_1 DISPLAY_WIDTH / 6
#define COLUMN_2 COLUMN_1 * 2
#define COLUMN_3 COLUMN_1 * 3
#define COLUMN_4 COLUMN_1 * 4
#define COLUMN_5 COLUMN_1 * 5
#define COLUMN_6 DISPLAY_WIDTH

#define X_1 DISPLAY_WIDTH / 12
#define X_2 X_1 + CARD_WIDTH
#define X_3 X_1 + CARD_WIDTH * 2
#define X_4 X_1 + CARD_WIDTH * 3
#define X_5 X_1 + CARD_WIDTH * 4
#define X_6 X_1 + CARD_WIDTH * 5
#define Y_1 DISPLAY_HEIGHT / 8
#define Y_2 Y_1 + CARD_LEGNTH
#define Y_3 Y_1 + CARD_LEGNTH * 2
#define Y_4 Y_1 + CARD_LEGNTH * 3
#define CIRCLE_RADIUS 15

#define INDEX_ORIGIN 0
#define BOARD_SIZE 24
#define OFFSET 1.5

uint8_t cardsMatchDisplay_computeRegionNumber(int16_t x, int16_t y);

void cardsMatchDisplay_showOrCoverCard(uint8_t region, bool cover,
                                       uint16_t color);

void cardsMatchDisplay_showAllCards();

void cardsMatchDisplay_coverAllCards();

void cardsMatchDisplay_removeCard(uint8_t region);

void cardsMatchDisplay_removeAllCards();

void cardsMatchDisplay_runTest();

#endif /* CARDSMATCHDISPLAY_H_ */