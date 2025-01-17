#include "game.h"

int main(int argc, char* argv[]) {
    Game* game = game_init();
    if (!game) return 1;

    while (game->engine->running) {
        engine_update(game->engine);
        game_update(game);
        engine_render(game->engine);
    }

    game_cleanup(game);
    return 0;
}