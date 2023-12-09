#include "cardsMatchGlobals.h"

static uint16_t boardCards[BOARD_SIZE];

void globals_setBoardCards(const uint16_t cards[]) {
  for (uint8_t index = INDEX_ORIGIN; index < BOARD_SIZE; index++)
    boardCards[index] = cards[index];
}

uint16_t globals_getCardColor(uint8_t index) { return boardCards[index]; }