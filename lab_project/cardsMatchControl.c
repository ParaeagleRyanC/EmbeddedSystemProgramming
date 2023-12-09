#include "cardsMatchControl.h"
#include "cardsMatchDisplay.h"
#include "cardsMatchGlobals.h"
#include "display.h"

// variables to store touch data
static int16_t x, y;
static uint8_t z;

uint8_t matchedSets;
uint8_t mistakesCounter;
uint8_t displayCardsCounter;
uint8_t timeOutCounter;
uint8_t displayMessageCounter;
uint16_t randomCounter;

static int8_t regionNumber;
static uint8_t tempRegion_1;
static uint8_t tempRegion_2;
static uint16_t tempCard_1;
static uint16_t tempCard_2;

// arrays to keep track picked and matched cards
uint8_t cardsPicked[TOTAL_CARDS];
uint8_t cardsMatched[TOTAL_CARDS];

uint16_t cards[BOARD_SIZE];

enum cardsMatchControl_st_t {
  init_st,
  intro_st,
  show_cards_st,
  pick_first_card_st,
  flip_card1_st,
  pick_second_card_st,
  flip_card2_st,
  verify_st,
  end_game_st,
  end_game_msg_st,
} currentState = init_st;

void cardGenerator() {

  uint8_t position;
  srand(randomCounter);

  for (uint8_t index = RESET; index < TOTAL_CARDS; index++)
    cards[index] = NO_ENTRY;

  for (uint16_t colorIndex = RESET; colorIndex < COMPLETE_SETS; colorIndex++) {
    for (uint8_t card = RESET; card < TWO_CARDS_PER_COLOR; card++) {
      position = rand() % TOTAL_CARDS;
      if (cards[position] == NO_ENTRY)
        cards[position] = colorIndex;
      else {
        for (uint8_t i = RESET; i < TOTAL_CARDS; i++) {
          if (cards[i] == NO_ENTRY) {
            cards[i] = colorIndex;
            break;
          }
        }
      }
    }
  }

  for (uint8_t index = RESET; index < TOTAL_CARDS; index++) {
    switch (cards[index]) {
    case 0:
      cards[index] = DISPLAY_BLUE;
      break;

    case 1:
      cards[index] = DISPLAY_GREEN;
      break;

    case 2:
      cards[index] = DISPLAY_MAGENTA;
      break;

    case 3:
      cards[index] = DISPLAY_DARK_BLUE;
      break;

    case 4:
      cards[index] = DISPLAY_DARK_GREEN;
      break;

    case 5:
      cards[index] = DISPLAY_DARK_MAGENTA;
      break;

    case 6:
      cards[index] = DISPLAY_RED;
      break;

    case 7:
      cards[index] = DISPLAY_CYAN;
      break;

    case 8:
      cards[index] = DISPLAY_YELLOW;
      break;

    case 9:
      cards[index] = DISPLAY_DARK_RED;
      break;

    case 10:
      cards[index] = DISPLAY_DARK_CYAN;
      break;

    case 11:
      cards[index] = DISPLAY_DARK_YELLOW;
      break;
    }
  }
}

// check if the card is already picked
bool cardPicked(uint8_t region) {
  if (cardsPicked[region] == true)
    return true;
  return false;
}

// check if the card was matched already
bool cardMatched(uint8_t region) {
  if (cardsPicked[region] == true)
    return true;
  return false;
}

// if the card is a match, set it to true
void cardMatch(uint8_t region) { cardsMatched[region] = true; }

// mark the card as picked or not
void cardPick(uint8_t region, bool picked) {
  if (picked)
    cardsPicked[region] = true;
  else
    cardsPicked[region] = false;
}

// function to display introduction
void cardsMatchControl_displayIntro() {
  display_fillScreen(DISPLAY_BLACK);
  display_setTextSize(3);
  display_setCursor(20, 20);
  display_println("Match the Cards!");
  display_setTextSize(1);
  display_setCursor(0, 80);
  display_println("* 24 cards will be displayed for 12 seconds");
  display_setCursor(0, 100);
  display_println("* Try to remember where the cards are and match them.");
  display_setCursor(0, 120);
  display_println("* 10 mistakes and the game is over.");
  display_setCursor(0, 140);
  display_println("* Don't think too long or the game will be over too.");
  display_setCursor(0, 160);
  display_println("* Cheat by taking a photo with your phone.");
  display_setCursor(0, 180);
  display_println("* Quit anytime by hitting Ctrl+C in the terminal.");
  display_setTextSize(2);
  display_setCursor(27, 210);
  display_println("*Touch screen to START*");
}

// function to display win message
void cardsMatchControl_displayWinMessage() {
  display_fillScreen(DISPLAY_BLACK);
  display_setTextSize(3);
  display_setCursor(50, 70);
  display_println("You did it!");
  display_setTextSize(2);
  display_setCursor(10, 120);
  display_println("Game will restart shortly");
}

// function to display time out message
void cardsMatchControl_displayTimeOutMessage() {
  display_fillScreen(DISPLAY_BLACK);
  display_setTextSize(3);
  display_setCursor(50, 70);
  display_println("Took too long");
  display_setTextSize(2);
  display_setCursor(10, 120);
  display_println("Game will restart shortly");
}

// function to display lose message
void cardsMatchControl_displayLoseMessage() {
  display_fillScreen(DISPLAY_BLACK);
  display_setTextSize(2);
  display_setCursor(20, 70);
  display_println("Made too many mistakes");
  display_setCursor(10, 120);
  display_println("Game will restart shortly");
}

// function to reset all variables and counters
void cardsMatchControl_resetAll() {
  matchedSets = RESET;
  mistakesCounter = RESET;
  displayCardsCounter = RESET;
  timeOutCounter = RESET;
  displayMessageCounter = RESET;
  tempRegion_1 = RESET;
  tempRegion_2 = RESET;
  tempCard_1 = RESET;
  tempCard_2 = RESET;
  for (uint8_t index = RESET; index < TOTAL_CARDS; index++) {
    cardsPicked[index] = false;
    cardsMatched[index] = false;
  }
}

void cardsMatchControl_init() {
  randomCounter = RESET;
  currentState = init_st;
}

void cardsMatchControl_tick() {

  randomCounter++;

  // transition first
  switch (currentState) {
  case init_st:
    cardsMatchControl_displayIntro();
    cardGenerator();
    globals_setBoardCards(cards);
    currentState = intro_st;
    break;

  case intro_st:
    if (display_isTouched()) {
      display_fillScreen(DISPLAY_BLACK);
      cardsMatchDisplay_showAllCards();
      displayCardsCounter = RESET;
      currentState = show_cards_st;
    }
    break;

  case show_cards_st:
    if (displayCardsCounter < CARDS_DISPLAY_TIME)
      currentState = show_cards_st;
    else if (displayCardsCounter == CARDS_DISPLAY_TIME) {
      cardsMatchDisplay_coverAllCards();
      currentState = pick_first_card_st;
    }
    break;

  case pick_first_card_st:
    if (mistakesCounter == MISTAKES_MAX || timeOutCounter == TIME_OUT ||
        matchedSets == COMPLETE_SETS)
      currentState = end_game_st;
    else if (display_isTouched()) {
      display_clearOldTouchData();
      timeOutCounter = RESET;
      currentState = flip_card1_st;
    } else if (timeOutCounter < TIME_OUT)
      currentState = pick_first_card_st;
    break;

  case flip_card1_st:
    if (!display_isTouched()) {
      display_getTouchedPoint(&x, &y, &z);
      tempRegion_1 = cardsMatchDisplay_computeRegionNumber(x, y);
      if (cardMatched(tempRegion_1)) {
        timeOutCounter = RESET;
        currentState = pick_first_card_st;
      } else {
        cardPick(tempRegion_1, true);
        tempCard_1 = globals_getCardColor(tempRegion_1);
        cardsMatchDisplay_showOrCoverCard(tempRegion_1, SHOW_CARD, tempCard_1);
        currentState = pick_second_card_st;
      }
    }
    break;

  case pick_second_card_st:
    if (timeOutCounter == TIME_OUT)
      currentState = end_game_st;
    else if (display_isTouched()) {
      display_clearOldTouchData();
      timeOutCounter = RESET;
      currentState = flip_card2_st;
    } else if (timeOutCounter < TIME_OUT)
      currentState = pick_second_card_st;
    break;

  case flip_card2_st:
    if (!display_isTouched()) {
      display_getTouchedPoint(&x, &y, &z);
      tempRegion_2 = cardsMatchDisplay_computeRegionNumber(x, y);
      if (cardMatched(tempRegion_2)) {
        timeOutCounter = RESET;
        currentState = pick_second_card_st;
      } else if (cardPicked(tempRegion_2)) {
        timeOutCounter = RESET;
        currentState = pick_second_card_st;
      } else {
        cardPick(tempRegion_2, true);
        tempCard_2 = globals_getCardColor(tempRegion_2);
        cardsMatchDisplay_showOrCoverCard(tempRegion_2, SHOW_CARD, tempCard_2);
        currentState = verify_st;
      }
    }
    break;

  case verify_st:
    if (tempCard_1 == tempCard_2) {
      cardsMatchDisplay_removeCard(tempRegion_1);
      cardsMatchDisplay_removeCard(tempRegion_2);
      cardMatch(tempRegion_1);
      cardMatch(tempRegion_2);
      matchedSets++;
    } else {
      cardPick(tempRegion_1, false);
      cardPick(tempRegion_2, false);
      cardsMatchDisplay_showOrCoverCard(tempRegion_1, COVER_CARD, tempCard_2);
      cardsMatchDisplay_showOrCoverCard(tempRegion_2, COVER_CARD, tempCard_2);
      mistakesCounter++;
    }
    currentState = pick_first_card_st;
    break;

  case end_game_st:
    if (timeOutCounter == TIME_OUT) {
      cardsMatchControl_displayTimeOutMessage();
      currentState = end_game_msg_st;
    } else if (mistakesCounter == MISTAKES_MAX) {
      cardsMatchControl_displayLoseMessage();
      currentState = end_game_msg_st;
    } else {
      cardsMatchControl_displayWinMessage();
      currentState = end_game_msg_st;
    }
    break;

  case end_game_msg_st:
    if (displayMessageCounter < MESSAGE_DISPLAY_TIME)
      currentState = end_game_msg_st;
    else if (displayMessageCounter == MESSAGE_DISPLAY_TIME)
      currentState = init_st;
    break;

  default:
    break;
  }

  // then actions
  switch (currentState) {
  case init_st:
    cardsMatchControl_resetAll();
    break;

  case intro_st:
    break;

  case show_cards_st:
    displayCardsCounter++;
    break;

  case pick_first_card_st:
    timeOutCounter++;
    break;

  case flip_card1_st:
    break;

  case pick_second_card_st:
    timeOutCounter++;
    break;

  case flip_card2_st:
    break;

  case verify_st:
    break;

  case end_game_st:
    cardsMatchDisplay_removeAllCards();
    break;

  case end_game_msg_st:
    displayMessageCounter++;
    break;

  default:
    break;
  }
}