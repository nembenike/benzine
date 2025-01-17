#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAX_KEYS 322

typedef struct {
  bool keys[MAX_KEYS];
  bool keys_previous[MAX_KEYS];
  int mouse_x;
  int mouse_y;
  bool mouse_buttons[3];
} InputManager;

void input_init(InputManager *input);
void input_update(InputManager *input);
bool input_is_key_pressed(InputManager *input, SDL_Keycode key);
bool input_is_key_just_pressed(InputManager *input, SDL_Keycode key);
bool input_is_mouse_button_pressed(InputManager *input, int button);
void input_handle_event(InputManager *input, SDL_Event *event);

#endif
