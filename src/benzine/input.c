#include "input.h"
#include "logging.h"
#include <string.h>

void input_init(InputManager *input) {
  memset(input->keys, 0, sizeof(input->keys));
  memset(input->keys_previous, 0, sizeof(input->keys_previous));
  input->mouse_x = 0;
  input->mouse_y = 0;
  memset(input->mouse_buttons, 0, sizeof(input->mouse_buttons));
}

void input_handle_event(InputManager *input, SDL_Event *event) {
  switch (event->type) {
  case SDL_KEYDOWN:
    if (!event->key.repeat) {
      log_keypress(event->key.keysym.sym, true);
    }
    break;
  case SDL_KEYUP:
    log_keypress(event->key.keysym.sym, false);
    break;
  }
}

void input_update(InputManager *input) {
  // Store previous keyboard state
  memcpy(input->keys_previous, input->keys, sizeof(input->keys));

  // Get current keyboard state
  const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);
  for (int i = 0; i < MAX_KEYS; i++) {
    input->keys[i] = keyboard_state[i];
  }

  // Get mouse state
  Uint32 mouse_state = SDL_GetMouseState(&input->mouse_x, &input->mouse_y);
  input->mouse_buttons[0] = (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
  input->mouse_buttons[1] = (mouse_state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0;
  input->mouse_buttons[2] = (mouse_state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;
}

bool input_is_key_pressed(InputManager *input, SDL_Keycode key) {
  SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
  return input->keys[scancode];
}

bool input_is_key_just_pressed(InputManager *input, SDL_Keycode key) {
  SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
  return input->keys[scancode] && !input->keys_previous[scancode];
}

bool input_is_mouse_button_pressed(InputManager *input, int button) {
  if (button >= 0 && button < 3) {
    return input->mouse_buttons[button];
  }
  return false;
}
