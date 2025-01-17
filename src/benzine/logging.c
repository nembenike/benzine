#include "logging.h"
#include <stdio.h>
#include <time.h>

void print_log(const char *message, log_level level) {
  time_t now;
  time(&now);
  char *time_str = ctime(&now);
  time_str[strlen(time_str) - 1] = '\0';

  switch (level) {
  case DEBUG:
    printf("[%s][DEBUG]: %s\n", time_str, message);
    break;
  case WARNING:
    printf("[%s][WARNING]: %s\n", time_str, message);
    break;
  case ERROR:
    printf("[%s][ERROR]: %s\n", time_str, message);
    break;
  case INPUT:
    printf("[%s][INPUT]: %s\n", time_str, message);
    break;
  }
}

void log_keypress(SDL_Keycode key, bool pressed) {
  char message[256];
  const char *key_name = SDL_GetKeyName(key);
  snprintf(message, sizeof(message), "Key '%s' was %s", key_name,
           pressed ? "pressed" : "released");
  print_log(message, INPUT);
}
