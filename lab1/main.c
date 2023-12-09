/*
This software is provided for student assignment use in the Department of
Electrical and Computer Engineering, Brigham Young University, Utah, USA.

Users agree to not re-host, or redistribute the software, in source or binary
form, to other persons or other institutions. Users may modify and use the
source code for personal or educational use.

For questions, contact Brad Hutchings or Jeff Goeders, https://ece.byu.edu/
*/

// Print out "hello world" on both the console and the LCD screen.

#include "display.h"

#define TEXT_SIZE 2
#define CURSOR_X 0
#define CURSOR_Y 0

#define TRI_X1 135
#define TRI_X2 185
#define TRI_X3 160
#define U_TRI_Y1 40
#define U_TRI_Y2 40
#define U_TRI_Y3 90
#define L_TRI_Y1 200
#define L_TRI_Y2 200
#define L_TRI_Y3 150
#define CIRCLE_RADIUS 30
#define L_CIR_X 80
#define R_CIR_X 240
#define CIR_Y 120

#include <stdio.h>
int main() {
  display_init(); // Must init all of the software and underlying hardware for
                  // LCD.
  display_fillScreen(DISPLAY_BLACK);     // Blank the screen.
  display_setCursor(CURSOR_X, CURSOR_Y); // The upper left of the LCD screen.
  display_setTextColor(DISPLAY_RED);     // Make the text red.
  display_setTextSize(TEXT_SIZE);        // Make the text a little larger.
  // display_println("hello world (on the LCD)!"); // This actually prints the
  // string to the LCD.
  // printf("hello world!\n");                     // This prints on the
  // console.

  // below is the graph
  // this draws two lines that form an X
  display_drawLine(CURSOR_X, CURSOR_Y, DISPLAY_WIDTH, DISPLAY_HEIGHT,
                   DISPLAY_GREEN);
  display_drawLine(CURSOR_X, DISPLAY_HEIGHT, DISPLAY_WIDTH, CURSOR_Y,
                   DISPLAY_GREEN);

  // this draws upper triangle
  display_drawTriangle(TRI_X1, U_TRI_Y1, TRI_X2, U_TRI_Y2, TRI_X3, U_TRI_Y3,
                       DISPLAY_YELLOW);
  display_fillTriangle(TRI_X1, U_TRI_Y1, TRI_X2, U_TRI_Y2, TRI_X3, U_TRI_Y3,
                       DISPLAY_YELLOW);

  // this draws lower triangle
  display_drawTriangle(TRI_X1, L_TRI_Y1, TRI_X2, L_TRI_Y2, TRI_X3, L_TRI_Y3,
                       DISPLAY_YELLOW);

  // this draws left circle
  display_drawCircle(L_CIR_X, CIR_Y, CIRCLE_RADIUS, DISPLAY_RED);

  // this draws right circle
  display_drawCircle(R_CIR_X, CIR_Y, CIRCLE_RADIUS, DISPLAY_RED);
  display_fillCircle(R_CIR_X, CIR_Y, CIRCLE_RADIUS, DISPLAY_RED);

  return 0;
}

// This function must be defined but can be left empty for now.
// You will use this function in a later lab.
// It is called in the timer interrupt service routine (see interrupts.c in
// supportFiles).
void isr_function() {
  // Empty for now.
}