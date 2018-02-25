#include "tetrisrenderer.ih"

void TetrisRenderer::renderLegend(SDL_Renderer &sdlRenderer, int cellSize)
{
  ScreenNormalizer normalizer(sdlRenderer);

  // Draw the shadow box.
  float legendX = 0.02;
  float legendY = 0.245;
  float legendW = 0.32;
  float legendH = 0.74;
  SDL_Rect rectangle = normalizer.deNormalize(legendX, legendY, legendW, legendH);
  this->d_shadowBrush.drawRectangle(sdlRenderer, rectangle);

  // Try to load font.
  TTF_Font* font = nullptr;
  font = TTF_OpenFont("data/gameFont.ttf", 80);
  if (font == nullptr)
  {
    cout << "Failed to load gameFont!" << '\n';
    return;
  }

  // Prepare text.
  SDL_Color fontColor = {255, 255, 255, 255};
  TextureFactory textureFactory(&sdlRenderer);
  Texture *title = textureFactory.fontTexture("Worth", *font, fontColor);

  // Draw Title
  float titleWidth  = legendW * 0.5f;
  float titleHeight = titleWidth / normalizer.normalizeWidth(title->width())
                      * normalizer.normalizeHeight(title->height());
  float titleX      = legendX + legendW / 2 - titleWidth / 2;
  float titleY      = legendY + 0.01f;

  SDL_Rect titleRectangle = normalizer.deNormalize(titleX, titleY, titleWidth, titleHeight);
  title->render(sdlRenderer, titleRectangle);
  delete title;

  // Determine cell value positions.
  float paddingHeight = 0.06f;
  float paddingWidth = 0.01f;
  unsigned long numCells = d_cellTextures.size();
  float cellHeight = (legendH - titleHeight) / numCells - (numCells/2+0.5f) * paddingHeight;
  float cellWidth  = cellHeight * normalizer.ratio();
  float valueWidth = legendW - cellWidth - paddingWidth * 4;

  fontColor = {100, 200, 100, 255};
  for (int i=0; i < numCells; i++)
  {
    // Draw the cell.
    float cellX = legendX + legendW / 2 - (cellWidth + valueWidth) / 2;
    float cellY = paddingHeight + legendY + titleHeight + i * (cellHeight + paddingHeight);
    SDL_Rect cellRectangle = normalizer.deNormalize(cellX, cellY, cellWidth, cellHeight);
    this->d_cellTextures[i].render(sdlRenderer, cellRectangle);

    // Draw the value.
    string value = "------ $ " + to_string(i+1);
    Texture *valueText = textureFactory.fontTexture(value, *font, fontColor);
    float valueHeight = valueWidth / normalizer.normalizeWidth(valueText->width())
                                  * normalizer.normalizeHeight(valueText->height());
    float valueY = cellY + cellHeight / 2 - valueHeight / 2;
    float valueX = paddingWidth + cellX + cellWidth;
    SDL_Rect valueRectangle = normalizer.deNormalize(valueX, valueY, valueWidth, valueHeight);
    valueText->render(sdlRenderer, valueRectangle);
    delete valueText;
  }
}
