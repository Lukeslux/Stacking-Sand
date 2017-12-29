#include "controller.ih"

bool Controller::processEvents()
{
  SDL_Event e;
  while(SDL_PollEvent(&e) != 0)
  {
    // Process window events.
    switch (e.type) {
      case SDL_QUIT: // Exit button is pressed.
        return false;
    }

    // Process keys.
    TetrisBlock* tetrisBlock = this->d_tetris->tetrisBlock();
    switch (e.key.keysym.sym) {
      case SDLK_LEFT: // Left
        tetrisBlock->move(Point2D(-1, 0));
        break;
      case SDLK_RIGHT: // Right
        tetrisBlock->move(Point2D(1, 0));
        break;
      case SDLK_DOWN: // Down
        //tetrisBlock->move(Point2D(0, 1));
        break;
      case SDLK_SPACE: // Rotate
        break;
    }
  }
  return true;
}
