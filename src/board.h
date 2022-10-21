#ifndef TICTACTOE_BOARD_H_
#define TICTACTOE_BOARD_H_

#define BOARD_SIZE   3

typedef enum {
  BOARD_ERROR_OK = 0,
  BOARD_ERROR_FATAL,
} BoardError;

typedef enum {
  BOARD_MARK_NONE = 0,
  BOARD_MARK_O,
  BOARD_MARK_X,
} BoardMark;

typedef enum {
  BOARD_RESULT_MARK_O_WON = 0,
  BOARD_RESULT_MARK_X_WON,
  BOARD_RESULT_DRAW,
  BOARD_RESULT_NOT_DECIDED,
} BoardResult;

typedef struct {
  unsigned int row;
  unsigned int col;
} BoardPoint;

typedef struct {
  int rows[BOARD_SIZE];
  int cols[BOARD_SIZE];
  int diagonal;
  int anti_diagonal;
} BoardLines;

typedef struct {
  BoardMark board[BOARD_SIZE][BOARD_SIZE];
  BoardLines lines;
  unsigned int left_spaces;
  BoardResult result;
} BoardInfo;

extern void BoardInitialize(BoardInfo *bi);
extern void BoardPrint(const BoardInfo *bi);
extern BoardError BoardPlaceMark(BoardInfo *bi, const BoardPoint *point, BoardMark mark);

#endif  // TICTACTOE_BOARD_H_

