#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "core.h"

typedef struct {
  // Background image object with fading decoration
  NODE;
  uint8_t current_alpha;
  float duration; // duration of animation in seconds
  bool activated;
  SDL_Texture* texture;
  SDL_FRect menu_area;
} BackGroundImage;

extern BackGroundImage* create_background_image(void* appstate, const char* img_path);

typedef struct {
  NODE;
} MainMenu;

extern MainMenu* create_main_menu(void* appstate);

typedef struct {
  NODE;
  SDL_FRect body;
  char* text;
  bool hovering;
  SDL_Texture* texture;
  SDL_FRect text_area;
  void (*callbackfun)();
} Button;

extern Button* create_main_menu_button(void* appstate, SDL_FRect area, char* text);
