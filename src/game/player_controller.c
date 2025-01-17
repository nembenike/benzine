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

    // Apply gravity first
    handle_gravity(engine, player);

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

    // Handle jump
    if (input_is_key_pressed(&engine->input, SDLK_SPACE)) {
        jump(engine, player);
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
    
    handle_boundary_collision(engine, player);
}

void handle_boundary_collision(Engine* engine, Entity* player) {
    // Left boundary
    if (player->x < 0) {
        player->x = 0;
        player->velocity_x = 0;
    }
    // Right boundary
    if (player->x + player->width > engine->screen_width) {
        player->x = engine->screen_width - player->width;
        player->velocity_x = 0;
    }
    // Top boundary
    if (player->y < 0) {
        player->y = 0;
        player->velocity_y = 0;
    }
    // Bottom boundary
    if (player->y + player->height > engine->screen_height) {
        player->y = engine->screen_height - player->height;
        player->velocity_y = 0;
    }
}

void jump(Engine* engine, Entity* player) {
    if (player->is_grounded && input_is_key_just_pressed(&engine->input, SDLK_SPACE)) {
        player->velocity_y = -JUMP_STRENGTH;
        player->is_grounded = false;
    }
}

void handle_gravity(Engine* engine, Entity* player) {
    player->velocity_y += GRAVITY * engine->delta_time;
    
    // Check ground collision
    if (player->y + player->height >= engine->screen_height) {
        player->y = engine->screen_height - player->height;
        player->velocity_y = 0;
        player->is_grounded = true;
    } else {
        player->is_grounded = false;
    }
}