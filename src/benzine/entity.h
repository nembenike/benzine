#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAX_ENTITIES 1000

typedef struct {
  float x, y;
  float width, height;
  float velocity_x, velocity_y;
  SDL_Color color;
  bool active;
  bool has_collision;
  bool has_sprite;
  char *sprite_path;
  bool is_grounded;
} Entity;

typedef struct {
  Entity entities[MAX_ENTITIES];
  int entity_count;
} EntityManager;

void entity_manager_init(EntityManager *manager);
int entity_create(EntityManager *manager);
void entity_destroy(EntityManager *manager, int entity_id);
void entity_update(EntityManager *manager, int entity_id, float delta_time);

#endif
