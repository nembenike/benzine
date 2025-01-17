#include "player_controller.h"
#include <math.h>

float move_toward(float current, float target, float max_delta) {
    if (fabs(target - current) <= max_delta) {
        return target;
    }
    return current + (target > current ? max_delta : -max_delta);
}

void update_player_movement(Engine *engine, int player_id) {
    Entity *player = &engine->entity_manager.entities[player_id];
    if (!player->active) return;

    float target_vel_x = 0;
    float target_vel_y = 0;

    // Get input
    if (input_is_key_pressed(&engine->input, SDLK_a) || 
        input_is_key_pressed(&engine->input, SDLK_LEFT)) {
        target_vel_x = -1;
    }
    if (input_is_key_pressed(&engine->input, SDLK_d) || 
        input_is_key_pressed(&engine->input, SDLK_RIGHT)) {
        target_vel_x = 1;
    }
    if (input_is_key_pressed(&engine->input, SDLK_w) || 
        input_is_key_pressed(&engine->input, SDLK_UP)) {
        target_vel_y = -1;
    }
    if (input_is_key_pressed(&engine->input, SDLK_s) || 
        input_is_key_pressed(&engine->input, SDLK_DOWN)) {
        target_vel_y = 1;
    }

    // Normalize diagonal movement
    if (target_vel_x != 0 && target_vel_y != 0) {
        float length = sqrt(target_vel_x * target_vel_x + target_vel_y * target_vel_y);
        target_vel_x /= length;
        target_vel_y /= length;
    }

    // Apply speed
    target_vel_x *= MAX_SPEED;
    target_vel_y *= MAX_SPEED;

    float accel = (target_vel_x != 0 || target_vel_y != 0) ? ACCELERATION : DECELERATION;
    
    player->velocity_x = move_toward(player->velocity_x, target_vel_x, 
                                   accel * engine->delta_time);
    player->velocity_y = move_toward(player->velocity_y, target_vel_y, 
                                   accel * engine->delta_time);
}