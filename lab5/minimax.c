
#include "minimax.h"
#include "stdio.h"

// board size which is 9
#define BOARDSIZE MINIMAX_BOARD_ROWS *MINIMAX_BOARD_COLUMNS
// this is the start of the board, 0 in terms of arrays
#define ROW_COLUMN_ORIGIN 0
// this is the origin of the index
#define INDEX_ORIGIN 0
// reach this number of streak to win
#define WIN_AT_THREE 3
// clear winStreak to 0
#define WINSTREAK_RESET 0
// compare scores for X and O
#define X_SCORE_COMPARE -11
#define O_SCORE_COMPARE 11

#define ALL_SQUARE_USED true
#define THERE_IS_A_WIN true
#define GAME_IS_OVER true
#define BOARD_IS_EMPTY true

// global variale that holds the move computed by minimax
static minimax_move_t choice;

// minimax recursive function
minimax_score_t minimax(minimax_board_t *board, bool current_player_is_X) {

  // array to store moves
  minimax_move_t movesArray[BOARDSIZE];
  // array to store scores
  minimax_score_t scoresArray[BOARDSIZE];
  // index for both arrays
  uint8_t arrayIndex = INDEX_ORIGIN;
  // get the score based on pervious player
  minimax_score_t currentScore =
      minimax_computeBoardScore(board, !current_player_is_X);

  // base case, game is over when there has been a win or a draw
  // return the score based on pervious player
  if (minimax_isGameOver(currentScore))
    return currentScore;

  // otherwise we need to recurse

  // this loop will generate all possible boards
  // all rows
  for (uint8_t row = ROW_COLUMN_ORIGIN; row < MINIMAX_BOARD_ROWS; row++) {
    // all columns
    for (uint8_t column = ROW_COLUMN_ORIGIN; column < MINIMAX_BOARD_COLUMNS;
         column++) {
      // check if the position is empty
      if (board->squares[row][column] == MINIMAX_EMPTY_SQUARE) {
        // if current player is X then place an X
        if (current_player_is_X)
          board->squares[row][column] = MINIMAX_X_SQUARE;
        // otherwise place an O here
        else
          board->squares[row][column] = MINIMAX_O_SQUARE;

        // call minimax on itself to go deep down into all possible boards
        currentScore = minimax(board, !current_player_is_X);
        // add score to scores array
        scoresArray[arrayIndex] = currentScore;
        // add move to moves array
        movesArray[arrayIndex].row = row;
        movesArray[arrayIndex].column = column;
        // undo the change to the board (return the square to empty) prior the
        // next iteration of the for-loops
        board->squares[row][column] = MINIMAX_EMPTY_SQUARE;

        // advance index before next iteration
        arrayIndex++;
      }
    }
  }

  // at this point all scores have been computed at this level
  // proceed to return the score depending on the player

  // if the current player is X, max score is wanted
  if (current_player_is_X) {
    currentScore = X_SCORE_COMPARE;
    // iterate through the scores in the scores array
    for (uint8_t index = INDEX_ORIGIN; index < arrayIndex; index++) {
      // if current score is higher than the tempScore, update the tempScore and
      // next move
      if (scoresArray[index] > currentScore) {
        currentScore = scoresArray[index];
        choice = movesArray[index];
      }
    }
  }
  // otherwise min score is wanted
  else {
    currentScore = O_SCORE_COMPARE;
    // iterate through the scores in the scores array
    for (uint8_t index = INDEX_ORIGIN; index < arrayIndex; index++) {
      // if current score is lower than the tempScore, update the tempScore and
      // next move
      if (scoresArray[index] < currentScore) {
        currentScore = scoresArray[index];
        choice = movesArray[index];
      }
    }
  }
  return currentScore;
}

// check for row-based win
bool rowBasedWin(minimax_board_t *board, uint8_t currentPlayer) {
  uint8_t winStreak = WINSTREAK_RESET;

  // iterate through each row
  for (uint8_t row = ROW_COLUMN_ORIGIN; row < MINIMAX_BOARD_ROWS; row++) {
    for (uint8_t column = ROW_COLUMN_ORIGIN; column < MINIMAX_BOARD_COLUMNS;
         column++) {
      // if the sqaure looked at doesn't match the current player then break
      if (board->squares[row][column] != currentPlayer)
        break;
      // if it matches then add to the winStreak count
      else if (board->squares[row][column] == currentPlayer)
        winStreak++;
    }
    // if the winStreak reaches 3, there is a win
    if (winStreak == WIN_AT_THREE)
      return THERE_IS_A_WIN;
    // clear winStreak before the next row
    winStreak = WINSTREAK_RESET;
  }
  // return false if winStreak not met
  return !THERE_IS_A_WIN;
}

// check for column-based win
bool columnBasedWin(minimax_board_t *board, uint8_t currentPlayer) {
  uint8_t winStreak = WINSTREAK_RESET;

  // iterate through each column
  for (uint8_t column = ROW_COLUMN_ORIGIN; column < MINIMAX_BOARD_COLUMNS;
       column++) {
    for (uint8_t row = ROW_COLUMN_ORIGIN; row < MINIMAX_BOARD_ROWS; row++) {
      // if the sqaure looked at doesn't match the current player then break
      if (board->squares[row][column] != currentPlayer)
        break;
      // if it matches then add to the winStreak count
      else if (board->squares[row][column] == currentPlayer)
        winStreak++;
    }
    // if the winStreak reaches 3, there is a win
    if (winStreak == WIN_AT_THREE)
      return THERE_IS_A_WIN;
    // clear winStreak before the next row
    winStreak = WINSTREAK_RESET;
  }
  // return false if winStreak not met
  return !THERE_IS_A_WIN;
}

// check for diagonal-based win
bool diagonalBasedWin(minimax_board_t *board) {
  // check from top left
  if (board->squares[0][0] == board->squares[1][1] &&
      board->squares[0][0] == board->squares[2][2] &&
      board->squares[0][0] != MINIMAX_EMPTY_SQUARE)
    return THERE_IS_A_WIN;
  // check from bottom left
  if (board->squares[2][0] == board->squares[1][1] &&
      board->squares[2][0] == board->squares[0][2] &&
      board->squares[2][0] != MINIMAX_EMPTY_SQUARE)
    return THERE_IS_A_WIN;
  // return false if no match
  return !THERE_IS_A_WIN;
}

// return true if all squares are occupied
bool allSqauresOccupied(minimax_board_t *board) {
  // iterate through all squares and return false if there is an empty square
  for (uint8_t row = ROW_COLUMN_ORIGIN; row < MINIMAX_BOARD_ROWS; row++) {
    for (uint8_t column = ROW_COLUMN_ORIGIN; column < MINIMAX_BOARD_COLUMNS;
         column++)
      if (board->squares[row][column] == MINIMAX_EMPTY_SQUARE)
        return !ALL_SQUARE_USED;
  }
  // otherwise return true
  return ALL_SQUARE_USED;
}

// This routine is not recursive but will invoke the recursive minimax function.
// You will call this function from the controlling state machine that you will
// implement in a later milestone. It computes the row and column of the next
// move based upon: the current board, the player. true means the computer is X.
// false means the computer is O. When called from the controlling state
// machine, you will call this function as follows:
// 1. If the computer is playing as X, you will call this function with
// current_player_is_x = true.
// 2. If the computer is playing as O, you will call this function with
// current_player_is_x = false. minimax_computeNextMove directly passes the
// current_player_is_x argument into the minimax() (helper) function. To assign
// values to the row and column arguments, you must use the following syntax in
// the body of the function: *row = move_row; *column = move_column; (for
// example).
void minimax_computeNextMove(minimax_board_t *board, bool current_player_is_x,
                             uint8_t *row, uint8_t *column) {
  // invoke the recursive minimax function
  minimax(board, current_player_is_x);
  // assign values to the row and column
  *row = choice.row;
  *column = choice.column;
}

// Determine that the game is over by looking at the score.
bool minimax_isGameOver(minimax_score_t score) {
  // if the score is a X_WIN, a O_WIN, or a DRAW score, game is then over
  if (score == MINIMAX_X_WINNING_SCORE || score == MINIMAX_O_WINNING_SCORE ||
      score == MINIMAX_DRAW_SCORE)
    return GAME_IS_OVER;
  // otherwise game is not over
  return !GAME_IS_OVER;
}

// Returns the score of the board, based upon the player and the board.
// This returns one of 4 values: MINIMAX_X_WINNING_SCORE,
// MINIMAX_O_WINNING_SCORE, MINIMAX_DRAW_SCORE, MINIMAX_NOT_ENDGAME
// Note: the player argument makes it possible to speed up this function.
// Assumptions:
// (1) if current_player_is_x == true, the last thing played was an 'X'.
// (2) if current_player_is_x == false, the last thing played was an 'O'.
// Hint: If you know the game was not over when an 'X' was played,
// you don't need to look for 'O's, and vice-versa.
minimax_score_t minimax_computeBoardScore(minimax_board_t *board,
                                          bool player_is_x) {

  // if player is X, check if O wins
  if (player_is_x) {
    if (rowBasedWin(board, MINIMAX_X_SQUARE) ||
        columnBasedWin(board, MINIMAX_X_SQUARE) || diagonalBasedWin(board))
      return MINIMAX_X_WINNING_SCORE;
  }

  // if player is X, check if O wins
  else {
    if (rowBasedWin(board, MINIMAX_O_SQUARE) ||
        columnBasedWin(board, MINIMAX_O_SQUARE) || diagonalBasedWin(board))
      return MINIMAX_O_WINNING_SCORE;
  }

  // all squares are occupied but no winner then it is a draw
  if (allSqauresOccupied(board))
    return MINIMAX_DRAW_SCORE;

  // no one wins and there's still empty square then the game is not over yet
  return MINIMAX_NOT_ENDGAME;
}

// Init the board to all empty squares.
void minimax_initBoard(minimax_board_t *board) {
  // iterate through all rows and columns and set the square to empty
  for (uint8_t row = ROW_COLUMN_ORIGIN; row < MINIMAX_BOARD_ROWS; row++) {
    for (uint8_t column = ROW_COLUMN_ORIGIN; column < MINIMAX_BOARD_COLUMNS;
         column++)
      board->squares[row][column] = MINIMAX_EMPTY_SQUARE;
  }
}