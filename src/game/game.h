#ifndef GAME_H
#define GAME_H

#include "../benzine/engine.h"

typedef struct {
    Engine* engine;
    int player_id;
    // other game-specific state here
} Game;

Game* game_init();
void game_update(Game* game);
void game_render(Game* game);
void game_cleanup(Game* game);

#endif