#include "game.h"
#include "player_controller.h"

Game* game_init() {
    Game* game = malloc(sizeof(Game));
    if (!game) return NULL;

    // Initialize engine
    game->engine = engine_init("Your Game Title", 800, 600);
    if (!game->engine) {
        free(game);
        return NULL;
    }

    // Create player
    game->player_id = entity_create(&game->engine->entity_manager);
    if (game->player_id >= 0) {
        Entity* player = &game->engine->entity_manager.entities[game->player_id];
        player->x = 400;
        player->y = 300;
        player->width = 50;
        player->height = 50;
        player->color = (SDL_Color){255, 0, 0, 255};
        player->has_collision = true;
    }

    return game;
}

void game_update(Game* game) {
    update_player_movement(game->engine, game->player_id);
    // other game-specific update logic
}

void game_render(Game* game) {
    //  game-specific rendering
}

void game_cleanup(Game* game) {
    engine_cleanup(game->engine);
    free(game);
}