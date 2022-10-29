#ifndef TICTACTOE_STRATEGY_H_
#define TICTACTOE_STRATEGY_H_

#include "board.h"

typedef enum {
  STRATEGY_ERROR_OK = 0,
  STRATEGY_ERROR_FATAL,
} StrategyError;

StrategyError StrategyPlaceMark(const BoardInfo *bi, BoardMark computer_mark, BoardPoint *next_point);

#endif  // TICTACTOE_STRATEGY_H_

