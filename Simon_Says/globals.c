
#include "globals.h"
#include <stdint.h>
#include <stdio.h>

#define INDEX_ORIGIN 0

static uint8_t sequenceArray[GLOBALS_MAX_FLASH_SEQUENCE];
static uint16_t sequenceValue;
static uint16_t iterationLength;
static uint16_t sequenceLength;

// This is the length of the complete sequence at maximum length.
// You must copy the contents of the sequence[] array into the global variable
// that you maintain. Do not just grab the pointer as this will fail.
void globals_setSequence(const uint8_t sequence[], uint16_t length) {
  for (uint16_t index = INDEX_ORIGIN; index < length; index++)
    sequenceArray[index] = sequence[index];
  sequenceLength = length;
}

// This returns the value of the sequence at the index.
uint8_t globals_getSequenceValue(uint16_t index) {
  return sequenceArray[index];
}

// Retrieve the sequence length.
uint16_t globals_getSequenceLength() { return sequenceLength; }

// This is the length of the sequence that you are currently working on.
void globals_setSequenceIterationLength(uint16_t length) {
  iterationLength = length;
}

// This is the length of the sequence that you are currently working on,
// not the maximum length but the interim length as
// the person playing the game works through the pattern one color at a time.
uint16_t globals_getSequenceIterationLength() { return iterationLength; }