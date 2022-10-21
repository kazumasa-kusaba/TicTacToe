#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "strategy.h"

typedef enum {
  PLAYER_TURN_FIRST = 0,
  PLAYER_TURN_SECOND,
} PlayerTurn;

static void PrintSoftwareInfo(void);
static void InputTurn(PlayerTurn *human_turn, PlayerTurn *computer_turn);
static void ConductGame(BoardInfo *bi, PlayerTurn human_turn,
    BoardMark human_mark, PlayerTurn computer_turn, BoardMark computer_mark);
static void UserPlaceMark(BoardInfo *bi, BoardMark mark);
static void ComputerPlaceMark(BoardInfo *bi, BoardMark mark);
static void PrintResult(const BoardInfo *bi, PlayerTurn human_turn);

int main(void)
{
  PrintSoftwareInfo();

  BoardInfo bi;
  BoardInitialize(&bi);

  PlayerTurn human_turn = PLAYER_TURN_FIRST;
  PlayerTurn computer_turn = PLAYER_TURN_SECOND;
  InputTurn(&human_turn, &computer_turn);
  
  BoardMark human_mark = human_turn == PLAYER_TURN_FIRST ? BOARD_MARK_O : BOARD_MARK_X;
  BoardMark computer_mark = human_mark == BOARD_MARK_O ? BOARD_MARK_X : BOARD_MARK_O;
  BoardPrint(&bi);

  ConductGame(&bi, human_turn, human_mark, computer_turn, computer_mark);

  PrintResult(&bi, human_turn);

  return 0;
}

static void PrintSoftwareInfo(void)
{
  const char *version = "1.00";
  const char *github_url = "https://github.com/kazumasa-kusaba/TicTacToe";

  printf("TicTacToe version %s\n", version);
  printf("%s\n\n", github_url);
}

static void InputTurn(PlayerTurn *human_turn, PlayerTurn *computer_turn)
{
  int input = 0;

  while (1) {
    printf("Which do you play? (%d: first, %d: second)\n", PLAYER_TURN_FIRST, PLAYER_TURN_SECOND);
    printf("Input: "); scanf("%d", &input);

    if (input == PLAYER_TURN_FIRST || input == PLAYER_TURN_SECOND) {
      break;
    } else {
      printf("Error!! \"%d\" is invalid value!!\n", input);
    }
  }

  if (input == PLAYER_TURN_FIRST) {
    *human_turn = PLAYER_TURN_FIRST;
    *computer_turn = PLAYER_TURN_SECOND;
    printf("You are first, computer is second.\n");
  } else {
    *human_turn = PLAYER_TURN_SECOND;
    *computer_turn = PLAYER_TURN_FIRST;
    printf("You are second, computer is first.\n");
  }
}

static void ConductGame(BoardInfo *bi, PlayerTurn human_turn,
    BoardMark human_mark, PlayerTurn computer_turn, BoardMark computer_mark)
{
  PlayerTurn turn = 0;
  while (bi->result == BOARD_RESULT_NOT_DECIDED) {
    if (turn == human_turn) {
      UserPlaceMark(bi, human_mark);
    } else {
      ComputerPlaceMark(bi, computer_mark);
    }

    BoardPrint(bi);

    turn = turn == PLAYER_TURN_FIRST ? PLAYER_TURN_SECOND : PLAYER_TURN_FIRST;
  }
}

static void UserPlaceMark(BoardInfo *bi, BoardMark mark)
{
  BoardError err = BOARD_ERROR_OK;

  do {
    int row = 0;
    int col = 0;

    printf("Where do you place?\n");
    printf("Input Row: ");    scanf("%d", &row);
    printf("Input Column: "); scanf("%d", &col);

    BoardPoint point = {row, col};
    err = BoardPlaceMark(bi, &point, mark);
    if (err != BOARD_ERROR_OK) {
      printf("Invalid potision!! Try again...\n");
    }
  } while (err != BOARD_ERROR_OK);
}

static void ComputerPlaceMark(BoardInfo *bi, BoardMark mark)
{
  StrategyError strategy_error = STRATEGY_ERROR_OK;
  BoardError board_error = BOARD_ERROR_OK;
  BoardPoint point = {0, 0};

  strategy_error = StrategyPlaceMark(bi, mark, &point);
  if (strategy_error != STRATEGY_ERROR_OK) {
    printf("Error");
    exit(1);
  }

  board_error = BoardPlaceMark(bi, &point, mark);
  if (board_error != BOARD_ERROR_OK) {
    printf("Error");
    exit(1);
  }

  printf("Computer ROW: %d, COLUMN: %d.\n", point.row, point.col);
}

static void PrintResult(const BoardInfo *bi, PlayerTurn human_turn)
{
  if (bi->result == BOARD_RESULT_MARK_O_WON) {
    if (human_turn == PLAYER_TURN_FIRST) {
      printf("You Win!!\n");
    } else if (human_turn == PLAYER_TURN_SECOND) {
      printf("You Lose...\n");
    } else {
      // Never comes
      exit(1);
    }
  } else if (bi->result == BOARD_RESULT_MARK_X_WON) {
    if (human_turn == PLAYER_TURN_FIRST) {
      printf("You Lose...\n");
    } else if (human_turn == PLAYER_TURN_SECOND) {
      printf("You Win!!\n");
    } else {
      // Never comes
      exit(1);
    }
  } else if (bi->result == BOARD_RESULT_DRAW) {
    printf("Draw\n");
  } else {
    // Never comes
    exit(1);
  }
}

