#include "engine.h"
#include <stdio.h>
#include <stdlib.h>

Engine *engine_init(const char *title, int width, int height) {
  Engine *engine = malloc(sizeof(Engine));
  if (!engine) {
    printf("Failed to allocate memory for engine\n");
    return NULL;
  }

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL initialization failed: %s\n", SDL_GetError());
    free(engine);
    return NULL;
  }

  engine->window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_SHOWN);
  if (!engine->window) {
    printf("Window creation failed: %s\n", SDL_GetError());
    SDL_Quit();
    free(engine);
    return NULL;
  }

  engine->renderer =
      SDL_CreateRenderer(engine->window, -1, SDL_RENDERER_ACCELERATED);
  if (!engine->renderer) {
    printf("Renderer creation failed: %s\n", SDL_GetError());
    SDL_DestroyWindow(engine->window);
    SDL_Quit();
    free(engine);
    return NULL;
  }

  engine->running = true;
  engine->screen_width = width;
  engine->screen_height = height;
  engine->last_frame = SDL_GetTicks();
  engine->delta_time = 0.0f;

  // Initialize subsystems
  input_init(&engine->input);
  renderer_init(&engine->renderer_system, engine->renderer);
  entity_manager_init(&engine->entity_manager);

  return engine;
}

void engine_update(Engine *engine) {
  // Calculate frame timing
  Uint32 current_time = SDL_GetTicks();
  Uint32 frame_time = current_time - engine->last_frame;
  
  // If we're running too fast, delay
  if (frame_time < FRAME_TIME) {
    SDL_Delay(FRAME_TIME - frame_time);
    current_time = SDL_GetTicks();
    frame_time = current_time - engine->last_frame;
  }
  
  engine->delta_time = frame_time / 1000.0f;
  engine->last_frame = current_time;

  // Handle input
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      engine->running = false;
    }
    // Handle input events
    input_handle_event(&engine->input, &event);
  }

  input_update(&engine->input);

  // Update all active entities
  for (int i = 0; i < MAX_ENTITIES; i++) {
    if (engine->entity_manager.entities[i].active) {
      entity_update(&engine->entity_manager, i, engine->delta_time);
    }
  }
}

void engine_render(Engine *engine) {
  renderer_clear(&engine->renderer_system);

  // Render all active entities
  for (int i = 0; i < MAX_ENTITIES; i++) {
    if (engine->entity_manager.entities[i].active) {
      renderer_draw_entity(&engine->renderer_system,
                           &engine->entity_manager.entities[i]);
    }
  }

  renderer_present(&engine->renderer_system);
}

void engine_cleanup(Engine *engine) {
  SDL_DestroyRenderer(engine->renderer);
  SDL_DestroyWindow(engine->window);
  SDL_Quit();
  free(engine);
}
