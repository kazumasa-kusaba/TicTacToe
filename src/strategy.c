#include "strategy.h"

#include <stdio.h>
#include <stdlib.h>

#include "board.h"

static const int SCORE_VALUE_WIN  = 1;
static const int SCORE_VALUE_LOSE = -1;
static const int SCORE_VALUE_DRAW = 0;
static const int SCORE_VALUE_MAX  = 9999;

static StrategyError StrategyMinMax(const BoardInfo *bi, BoardMark mark, BoardPoint *point);
static int MinMax(BoardInfo bi, BoardMark computer_mark, BoardMark mark, BoardPoint *point);
static int CalculateScore(const BoardInfo *bi, BoardMark computer_mark);
static void UpdateResult(BoardMark computer_mark, BoardMark mark,
    int score, const BoardPoint *point, int *return_score, BoardPoint *return_point);

StrategyError StrategyPlaceMark(const BoardInfo *bi, BoardMark mark, BoardPoint *point)
{
  return StrategyMinMax(bi, mark, point);
}

static StrategyError StrategyMinMax(const BoardInfo *bi, BoardMark computer_mark, BoardPoint *next_point)
{
  MinMax(*bi, computer_mark, computer_mark, next_point);
  return STRATEGY_ERROR_OK;
}

static int MinMax(BoardInfo bi, BoardMark computer_mark, BoardMark mark, BoardPoint *point)
{
  if (bi.result != BOARD_RESULT_NOT_DECIDED) {
    return CalculateScore(&bi, computer_mark);
  }

  int ret = computer_mark == mark ? -SCORE_VALUE_MAX : SCORE_VALUE_MAX;

  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int col = 0; col < BOARD_SIZE; col++) {
      BoardPoint next_point = {row, col};
      BoardInfo next_board = bi;
      if (BoardPlaceMark(&next_board, &next_point, mark) != BOARD_ERROR_OK) {
        continue;
      }
      BoardMark next_mark = mark == BOARD_MARK_O ? BOARD_MARK_X : BOARD_MARK_O;
      int score = MinMax(next_board, computer_mark, next_mark, &next_point);
      UpdateResult(computer_mark, mark, score, &next_point, &ret, point);
    }
  }

  return ret;
}

static int CalculateScore(const BoardInfo *bi, BoardMark computer_mark)
{
  int ret = SCORE_VALUE_MAX;

  switch (bi->result) {
    case BOARD_RESULT_MARK_O_WON: {
      if (computer_mark == BOARD_MARK_O) {
        ret = SCORE_VALUE_WIN;
      } else {
        ret = SCORE_VALUE_LOSE;
      }
      break;
    }
    case BOARD_RESULT_MARK_X_WON: {
      if (computer_mark == BOARD_MARK_X) {
        ret = SCORE_VALUE_WIN;
      } else {
        ret = SCORE_VALUE_LOSE;
      }
      break;
    }
    case BOARD_RESULT_DRAW:
      ret = SCORE_VALUE_DRAW;
      break;
    default: 
      // Never comes
      printf("Error");
      exit(1);
  }

  return ret;
}

static void UpdateResult(BoardMark computer_mark, BoardMark mark,
    int score, const BoardPoint *point, int *return_score, BoardPoint *return_point)
{
  if (computer_mark == mark) {
    if (*return_score < score) {
      *return_score = score;
      return_point->row = point->row;
      return_point->col = point->col;
    }
  } else {
    if (*return_score > score) {
      *return_score = score;
    }
  }
}

