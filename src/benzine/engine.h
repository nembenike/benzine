#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "entity.h"
#include "input.h"
#include "renderer.h"

#define TARGET_FPS 50
#define FRAME_TIME (1000.0f / TARGET_FPS )

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool running;
  int screen_width;
  int screen_height;
  float delta_time;
  Uint32 last_frame;
  InputManager input;
  RenderSystem renderer_system;
  EntityManager entity_manager;
} Engine;

Engine *engine_init(const char *title, int width, int height);
void engine_update(Engine *engine);
void engine_render(Engine *engine);
void engine_cleanup(Engine *engine);

#endif
