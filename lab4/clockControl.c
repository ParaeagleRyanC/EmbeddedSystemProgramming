#include "clockControl.h"
#include "clockDisplay.h"
#include "display.h"
#include <stdio.h>

// States for the controller state machine.
enum clockControl_st_t {
  init_st, // Start here, transition out of this state on the first tick.
  never_touched_st, // Wait here until the first touch - clock is disabled until
                    // set.
  waiting_for_touch_st,    // waiting for touch, clock is enabled and running.
  adc_counter_running_st,  // waiting for the touch-controller ADC to settle.
  auto_counter_running_st, // waiting for the auto-update delay to expire
                           // (user is holding down button for auto-inc/dec)
  rate_counter_running_st, // waiting for the rate-timer to expire to know when
                           // to perform the auto inc/dec.
  rate_counter_expired_st, // when the rate-timer expires, perform the inc/dec
                           // function.
  add_second_to_clock_st   // add a second to the clock time and reset the ms
                           // counter.
} currentState;

static uint8_t adcCounter;
static uint8_t autoCounter;
static uint8_t rateCounter;
static uint8_t secondCounter;

#define ADC_COUNTER_MAX_VALUE 1
#define AUTO_COUNTER_MAX_VALUE 10
#define RATE_COUNTER_MAX_VALUE 1
#define RESET_TO_ZERO 0
#define ONE_SEC_IN_TICKS 20
#define ERR_MSG "FAILED!"

// Place this function before the tick() function in the file to keep the
// compiler happy. All printed messages for states are provided here.
#define INIT_ST_MSG "init state\n"
#define NEVER_TOUCHED_ST_MSG "never_touched_st\n"
#define WAITING_FOR_TOUCH_ST_MSG "waiting for touch_st\n"
#define AD_TIMER_RUNNING_ST_MSG "adc_timer_running_st\n"
#define AUTO_TIMER_RUNNING_ST_MSG "auto_timer_running_st\n"
#define RATE_TIMER_RUNNING_ST_MSG "rate_timer_running_st\n"
#define RATE_TIMER_EXPIRED_ST_MSG "rate_timer_expired_st\n"
// This is a debug state print routine. It will print the names of the states
// each time tick() is called. It only prints states if they are different than
// the previous state.
void debugStatePrint() {
  static enum clockControl_st_t previousState;
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
    case never_touched_st:
      printf(NEVER_TOUCHED_ST_MSG);
      break;
    case waiting_for_touch_st:
      printf(WAITING_FOR_TOUCH_ST_MSG);
      break;
    case adc_counter_running_st:
      printf(AD_TIMER_RUNNING_ST_MSG);
      break;
    case auto_counter_running_st:
      printf(AUTO_TIMER_RUNNING_ST_MSG);
      break;
    case rate_counter_running_st:
      printf(RATE_TIMER_RUNNING_ST_MSG);
      break;
    case rate_counter_expired_st:
      printf(RATE_TIMER_EXPIRED_ST_MSG);
      break;
    }
  }
}

// Call this before you call clockControl_tick().
void clockControl_init() { currentState = init_st; }

// Standard tick function.
void clockControl_tick() {

  // print the current state on the terminal
  debugStatePrint();

  // Perform state update first.
  switch (currentState) {

  case init_st:
    currentState = never_touched_st;
    break;

  case never_touched_st:
    // check if the screen is touched
    // goes to adc_counter_running_st if true
    if (display_isTouched()) {
      display_clearOldTouchData();
      currentState = adc_counter_running_st;
    }
    break;

  case waiting_for_touch_st:
    // check if the screen is touched
    // goes to adc_counter_running_st if true
    if (display_isTouched()) {
      display_clearOldTouchData();
      currentState = adc_counter_running_st;
    }
    // check if the screen is touched and held for over 1 second
    // if yes, goes to add_second_to_clock_st
    if (secondCounter >= ONE_SEC_IN_TICKS)
      currentState = add_second_to_clock_st;
    break;

  case adc_counter_running_st:
    // if the screen is not touched and adcCounter is 1
    // perform increment or decrement
    // then goes to waiting_for_touch_st
    if (!display_isTouched() && (adcCounter == ADC_COUNTER_MAX_VALUE)) {
      clockDisplay_performIncDec();
      currentState = waiting_for_touch_st;
    }
    // if the screen is touched and adcCounter is 1
    // goes to auto_counter_running_st
    else if (display_isTouched() && (adcCounter == ADC_COUNTER_MAX_VALUE))
      currentState = auto_counter_running_st;
    // otherwise goes to adc_counter_running_st
    else
      currentState = adc_counter_running_st;
    break;

  case auto_counter_running_st:
    // if the screen is not touched then perform increment or decrement
    // goes to waiting_for_touch_st afterwards
    if (!display_isTouched()) {
      clockDisplay_performIncDec();
      currentState = waiting_for_touch_st;
    }
    // if the screen is touched and autoCounter is 10
    // perform increment or decrement
    // then goes to rate_counter_running_st
    else if (display_isTouched() && (autoCounter == AUTO_COUNTER_MAX_VALUE)) {
      clockDisplay_performIncDec();
      currentState = rate_counter_running_st;
    }
    // otherwise goes to auto_counter_running_st
    else
      currentState = auto_counter_running_st;
    break;

  case rate_counter_running_st:
    // if the screen is not touched
    // goes to waiting_for_touch_st
    if (!display_isTouched())
      currentState = waiting_for_touch_st;
    // if the screen is touched and rateCounter is 1
    // then goes to rate_counter_expired_st
    else if (display_isTouched() && (rateCounter == RATE_COUNTER_MAX_VALUE))
      currentState = rate_counter_expired_st;
    // otherwise goes to rate_counter_running_st
    else
      currentState = rate_counter_running_st;
    break;

  case rate_counter_expired_st:
    // if the screen is not touched
    // goes to waiting_for_touch_st
    if (!display_isTouched())
      currentState = waiting_for_touch_st;
    // if the screen is touched
    // perform increment or decrement
    // then goes to rate_counter_running_st
    else if (display_isTouched()) {
      clockDisplay_performIncDec();
      currentState = rate_counter_running_st;
    }
    break;

  // simply advance a second
  // then goes back to waiting_for_touch_st
  case add_second_to_clock_st:
    clockDisplay_advanceTimeOneSecond();
    secondCounter = RESET_TO_ZERO;
    currentState = waiting_for_touch_st;
    break;

  default:
    // print an error message here.
    printf(ERR_MSG);
    break;
  }

  // Perform state action next.
  switch (currentState) {

  case init_st:
    break;

  case never_touched_st:
    adcCounter = 0;
    autoCounter = 0;
    rateCounter = 0;
    break;

  case waiting_for_touch_st:
    adcCounter = 0;
    autoCounter = 0;
    rateCounter = 0;
    secondCounter++;
    break;

  case adc_counter_running_st:
    adcCounter++;
    break;

  case auto_counter_running_st:
    autoCounter++;
    break;

  case rate_counter_running_st:
    rateCounter++;
    break;

  case rate_counter_expired_st:
    rateCounter = 0;
    break;

  case add_second_to_clock_st:
    break;

  default:
    // print an error message here.
    printf(ERR_MSG);
    break;
  }
}