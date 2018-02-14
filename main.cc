#include "main.ih"

const float MAX_DELTA_TIME = 0.17;

int main(int argc, char **argv)
{
  try
  {
    // Initialize our window.
    Window &window = Window::getWindow();
    SDL_Renderer *sdlRenderer = window.getSDLRenderer();

    // Initialise our games.
    TetrisModel* tetrisModel = new TetrisModel();
    TetrisRenderer* tetrisRenderer = new TetrisRenderer(sdlRenderer, tetrisModel);
    TetrisInputParser* tetrisInputParser = new TetrisInputParser(tetrisModel);
    Game *tetrisGame = new Game(tetrisRenderer, tetrisInputParser, tetrisModel);

    BlockModel* blockModel = new BlockModel(tetrisModel);
    BlockRenderer* blockRenderer = new BlockRenderer(sdlRenderer, blockModel);
    BlockInputParser* blockInputParser = new BlockInputParser(blockModel);
    Game *blockGame = new Game(blockRenderer, blockInputParser, blockModel);

    // Push the games on the game stack, following their drawing order.
    vector<Game> games;
    games.reserve(2);
    games.push_back(*blockGame);
    games.push_back(*tetrisGame);

    // Main game loop
    auto startTime = chrono::high_resolution_clock::now();
    auto endTime = startTime;
    while(games.size())
    {
      // Calulate elapsed time.
      startTime = endTime;
      endTime = chrono::high_resolution_clock::now();
      chrono::duration<float> elapsedSeconds = endTime - startTime;
      float deltaTime = elapsedSeconds.count();

      // Destroy all dead games.
      games.erase(remove_if(games.begin(), games.end(),
                  [](Game game){return !(game.alive());}),
                  games.end());

      // Update all living games.
      SDL_RenderClear(sdlRenderer);
      ButtonState buttonState = Input::getState();
      for (Game &game : games)
      {
        game.update(*sdlRenderer, buttonState, deltaTime);
      }
      SDL_RenderPresent(sdlRenderer);

      // Lock the game at MAX_DELTA_TIME to save power.
      float leftTime = MAX_DELTA_TIME - deltaTime;
      if (leftTime > 0)
        SDL_Delay((unsigned int)(1000 * leftTime));
    }
  }
  catch(runtime_error runerr)
  {
    cout << "ERROR - Could not initialize an SDL window: " << runerr.what() << endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
