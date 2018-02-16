#ifndef TEXTURE_H
#define TEXTURE_H

#include "texture.ih"

class Texture
{
public:
  Texture(SDL_Texture *texture, int width, int height);
  ~Texture();

  // Render to a surface.
  void render(SDL_Renderer &renderer, SDL_Rect destRect);
  void render(SDL_Renderer &renderer, int x, int y);

  // Set as render target.
  void asRenderTarget(SDL_Renderer &renderer);

  // Return texture size.
  int width();
  int height();

private:
  // The hardware texture.
  SDL_Texture *d_texture;

  // Texture size.
  int d_width;
  int d_height;
};

#endif /* TEXTURE_H */
