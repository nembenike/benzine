#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "../benzine/engine.h"

#define PLAYER_SPEED 200.0f
#define ACCELERATION 800.0f
#define DECELERATION 400.0f
#define MAX_SPEED 200.0f
#define GRAVITY 1000.0f
#define JUMP_STRENGTH 500.0f

void update_player_movement(Engine *engine, int player_id);
float move_toward(float current, float target, float max_delta);
void handle_gravity(Engine* engine, Entity* player);
void jump(Engine* engine, Entity* player);
void handle_boundary_collision(Engine* engine, Entity* player);

#endif