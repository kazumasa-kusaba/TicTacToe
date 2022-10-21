#include "board.h"

#include <stdio.h>
#include <stdlib.h>

#define MARK_O_VALUE   1
#define MARK_X_VALUE  -1

static void InitializeBoard(BoardInfo *bi);
static void InitializeLines(BoardInfo *bi);
static void InitializeLeftSpaces(BoardInfo *bi);
static void InitializeResult(BoardInfo *bi);
static void PrintMark(BoardMark mark);
static BoardError CheckIfMarkIsValid(const BoardMark board[BOARD_SIZE][BOARD_SIZE],
    const BoardPoint *point, BoardMark mark);
static void UpdateBoardLines(BoardInfo *bi, const BoardPoint *point, BoardMark mark);
inline static int GetMarkValue(BoardMark mark);
static void UpdateBoardResult(BoardInfo *bi, const BoardPoint *point, BoardMark mark);
static BoardResult GetBoardResult(BoardMark mark);

void BoardInitialize(BoardInfo *bi)
{
  InitializeBoard(bi);
  InitializeLines(bi);
  InitializeLeftSpaces(bi);
  InitializeResult(bi);
}

void BoardPrint(const BoardInfo *bi)
{
  printf("  ");
  for (int col = 0; col < BOARD_SIZE; col++) {
    printf("%01d", col);
  }
  printf("\n");

  printf(" |");
  for (int i = 0; i < BOARD_SIZE; i++) {
    printf("-");
  }
  printf("|\n");

  for (int row = 0; row < BOARD_SIZE; row++) {
    printf("%01d", row);
    printf("|");
    for (int col = 0; col < BOARD_SIZE; col++) {
      PrintMark(bi->board[row][col]);
    }
    printf("|\n");
  }

  printf(" |");
  for (int i = 0; i < BOARD_SIZE; i++) {
    printf("-");
  }
  printf("|\n");
}

BoardError BoardPlaceMark(BoardInfo *bi, const BoardPoint *point, BoardMark mark)
{
  BoardError ret = BOARD_ERROR_OK;

  ret = CheckIfMarkIsValid(bi->board, point, mark);
  if (ret != BOARD_ERROR_OK) {
    return ret;
  }

  bi->board[point->row][point->col] = mark;

  bi->left_spaces -= 1;
  UpdateBoardLines(bi, point, mark);
  UpdateBoardResult(bi, point, mark);

  return ret;
}

static void InitializeBoard(BoardInfo *bi)
{
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int col = 0; col < BOARD_SIZE; col++) {
      bi->board[row][col] = BOARD_MARK_NONE;
    }
  }
}

static void InitializeLines(BoardInfo *bi)
{
  for (int row = 0; row < BOARD_SIZE; row++) {
    bi->lines.rows[row] = 0;
  }
  for (int col = 0; col < BOARD_SIZE; col++) {
    bi->lines.cols[col] = 0;
  }
  bi->lines.diagonal = 0;
  bi->lines.anti_diagonal = 0;
}

static void InitializeLeftSpaces(BoardInfo *bi)
{
  bi->left_spaces = BOARD_SIZE * BOARD_SIZE;
}

static void InitializeResult(BoardInfo *bi)
{
  bi->result = BOARD_RESULT_NOT_DECIDED;
}

static void PrintMark(BoardMark mark)
{
  switch (mark) {
    case BOARD_MARK_NONE:
      printf(".");
      break;
    case BOARD_MARK_O:
      printf("O");
      break;
    case BOARD_MARK_X:
      printf("X");
      break;
    default:
      printf("Error!!");
      exit(1);
  }
}

static BoardError CheckIfMarkIsValid(const BoardMark board[BOARD_SIZE][BOARD_SIZE],
    const BoardPoint *point, BoardMark mark)
{
  if (point->row < 0 || BOARD_SIZE <= point->row ||
      point->col < 0 || BOARD_SIZE <= point->col) {
    return BOARD_ERROR_FATAL;
  }

  if (board[point->row][point->col] != BOARD_MARK_NONE) {
    return BOARD_ERROR_FATAL;
  }

  return BOARD_ERROR_OK;
}

static void UpdateBoardLines(BoardInfo *bi, const BoardPoint *point, BoardMark mark)
{
  bi->lines.rows[point->row] += GetMarkValue(mark);
  bi->lines.cols[point->col] += GetMarkValue(mark);
  if (point->row == point->col) {
    bi->lines.diagonal += GetMarkValue(mark);
  }
  if (point->row == (BOARD_SIZE - point->col - 1)) {
    bi->lines.anti_diagonal += GetMarkValue(mark);
  }
}

inline static int GetMarkValue(BoardMark mark)
{
  return mark == BOARD_MARK_O ? MARK_O_VALUE : MARK_X_VALUE;
}

static void UpdateBoardResult(BoardInfo *bi, const BoardPoint *point, BoardMark mark)
{
  if (abs(bi->lines.rows[point->row]) == BOARD_SIZE ||
      abs(bi->lines.cols[point->col]) == BOARD_SIZE ||
      abs(bi->lines.diagonal)         == BOARD_SIZE ||
      abs(bi->lines.anti_diagonal)    == BOARD_SIZE) {
    bi->result = GetBoardResult(mark);
  } else if (bi->left_spaces == 0) {
    bi->result = BOARD_RESULT_DRAW;
  }
}

static BoardResult GetBoardResult(BoardMark mark)
{
  BoardResult ret = BOARD_RESULT_NOT_DECIDED;

  switch (mark) {
    case BOARD_MARK_O:
      ret = BOARD_RESULT_MARK_O_WON;
      break;
    case BOARD_MARK_X:
      ret = BOARD_RESULT_MARK_X_WON;
      break;
    default:
      // Error
      printf("Error!!");
      exit(1);
  }

  return ret;
}

