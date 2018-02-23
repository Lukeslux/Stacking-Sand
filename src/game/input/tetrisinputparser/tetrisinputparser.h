#ifndef TETRIS_INPUT_PARSER_H
#define TETRIS_INPUT_PARSER_H

#include "tetrisinputparser.ih"

class TetrisInputParser : public InputParser
{
public:
  explicit TetrisInputParser(TetrisModel *tetrisModel);
  void parse(InputState inputState) override ;

private:
  /* Gameplay constants. */
  const float SPEEDUP_TIME = 0.5f;

  TetrisModel *d_tetrisModel;
};

#endif /* TETRIS_INPUT_PARSER_H */
