#include "entity.h"
#include <stdlib.h>

void entity_manager_init(EntityManager *manager) {
  manager->entity_count = 0;
  for (int i = 0; i < MAX_ENTITIES; i++) {
    manager->entities[i].active = false;
  }
}

int entity_create(EntityManager *manager) {
  if (manager->entity_count >= MAX_ENTITIES)
    return -1;

  int id = 0;
  while (id < MAX_ENTITIES && manager->entities[id].active) {
    id++;
  }

  if (id < MAX_ENTITIES) {
    Entity *entity = &manager->entities[id];
    entity->active = true;
    entity->x = 0;
    entity->y = 0;
    entity->width = 32;
    entity->height = 32;
    entity->velocity_x = 0;
    entity->velocity_y = 0;
    entity->color = (SDL_Color){255, 255, 255, 255};
    entity->has_collision = false;
    entity->has_sprite = false;
    entity->sprite_path = NULL;

    manager->entity_count++;
    return id;
  }

  return -1;
}

void entity_destroy(EntityManager *manager, int entity_id) {
  if (entity_id < 0 || entity_id >= MAX_ENTITIES)
    return;

  Entity *entity = &manager->entities[entity_id];
  if (entity->active) {
    entity->active = false;
    if (entity->sprite_path) {
      free(entity->sprite_path);
      entity->sprite_path = NULL;
    }
    manager->entity_count--;
  }
}

void entity_update(EntityManager *manager, int entity_id, float delta_time) {
  if (entity_id < 0 || entity_id >= MAX_ENTITIES)
    return;

  Entity *entity = &manager->entities[entity_id];
  if (!entity->active)
    return;

  entity->x += entity->velocity_x * delta_time;
  entity->y += entity->velocity_y * delta_time;
}
