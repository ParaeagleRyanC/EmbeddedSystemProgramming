#ifndef CARDSMATCHGLOBALS_H_
#define CARDSMATCHGLOBALS_H_

#include <stdbool.h>
#include <stdint.h>

#define A1 0
#define A2 1
#define A3 2
#define A4 3
#define A5 4
#define A6 5
#define B1 6
#define B2 7
#define B3 8
#define B4 9
#define B5 10
#define B6 11
#define C1 12
#define C2 13
#define C3 14
#define C4 15
#define C5 16
#define C6 17
#define D1 18
#define D2 19
#define D3 20
#define D4 21
#define D5 22
#define D6 23

#define INDEX_ORIGIN 0
#define BOARD_SIZE 24

void globals_setBoardCards(const uint16_t cards[]);

uint16_t globals_getCardColor(uint8_t index);

#endif /* CARDSMATCHGLOBALS_H_ */