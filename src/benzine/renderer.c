#include "renderer.h"

void renderer_init(RenderSystem *renderer, SDL_Renderer *sdl_renderer) {
  renderer->sdl_renderer = sdl_renderer;
}

void renderer_draw_entity(RenderSystem *renderer, Entity *entity) {
  if (!entity->active)
    return;

  SDL_SetRenderDrawColor(renderer->sdl_renderer, entity->color.r,
                         entity->color.g, entity->color.b, entity->color.a);

  SDL_Rect rect = {(int)entity->x, (int)entity->y, (int)entity->width,
                   (int)entity->height};

  SDL_RenderFillRect(renderer->sdl_renderer, &rect);
}

void renderer_clear(RenderSystem *renderer) {
  SDL_SetRenderDrawColor(renderer->sdl_renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer->sdl_renderer);
}

void renderer_present(RenderSystem *renderer) {
  SDL_RenderPresent(renderer->sdl_renderer);
}
