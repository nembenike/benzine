#ifndef RENDERER_H
#define RENDERER_H

#include "entity.h"
#include <SDL2/SDL.h>

typedef struct {
  SDL_Renderer *sdl_renderer;
  // Add texture management
} RenderSystem;

void renderer_init(RenderSystem *renderer, SDL_Renderer *sdl_renderer);
void renderer_draw_entity(RenderSystem *renderer, Entity *entity);
void renderer_clear(RenderSystem *renderer);
void renderer_present(RenderSystem *renderer);

#endif
