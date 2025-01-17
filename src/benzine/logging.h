#ifndef LOGGING_H
#define LOGGING_H
#include <stdbool.h>

#include <SDL2/SDL.h>

typedef enum log_level {
  DEBUG,
  WARNING,
  ERROR,
  INPUT
} log_level;

void print_log(const char *message, log_level level);
void log_keypress(SDL_Keycode key,
                  bool pressed);

#endif
