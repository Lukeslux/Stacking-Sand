#include "tetrismodel.ih"

double TetrisModel::waitTime()
{
  double delay;
  if (d_score >= SCORE_LEVEL6)
    delay = DELAY_LEVEL6;
  else if (d_score >= SCORE_LEVEL5)
    delay = DELAY_LEVEL5;
  else if (d_score >= SCORE_LEVEL4)
    delay = DELAY_LEVEL4;
  else if (d_score >= SCORE_LEVEL3)
    delay = DELAY_LEVEL3;
  else if (d_score >= SCORE_LEVEL2)
    delay = DELAY_LEVEL2;
  else if (d_score >= SCORE_LEVEL1)
    delay = DELAY_LEVEL1;
  else
    delay = DELAY_LEVEL0;

  return delay;
}
