#ifndef CARDSMATCHCONTROL_H_
#define CARDSMATCHCONTROL_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TOTAL_CARDS 24
#define COMPLETE_SETS 12
#define MISTAKES_MAX 10
#define CARDS_DISPLAY_TIME 50
#define TIME_OUT 40
#define MESSAGE_DISPLAY_TIME 20
#define RESET 0
#define TWO_CARDS_PER_COLOR 2
#define NO_ENTRY 25
#define SHOW_CARD false
#define COVER_CARD true

// generate random cards
void cardGenerator();

// check if the card is already picked
bool cardPicked(uint8_t region);

// check if the card was matched already
bool cardMatched(uint8_t region);

// if the card is a match, set it to true
void cardMatch(uint8_t region);

// mark the card as picked or not
void cardPick(uint8_t region, bool picked);

// function to display introduction
void cardsMatchControl_displayIntro();

// function to display win message
void cardsMatchControl_displayWinMessage();

// function to display time out message
void cardsMatchControl_displayTimeOutMessage();

// function to display lose message
void cardsMatchControl_displayLoseMessage();

// function to reset all variables and counters
void cardsMatchControl_resetAll();

void cardsMatchControl_init();

void cardsMatchControl_tick();

#endif /* CARDSMATCHCONTROL_H_ */