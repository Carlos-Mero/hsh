#pragma once

#include <SDL3_ttf/SDL_ttf.h>

#include "core.h"
#include "scene.h"

typedef struct {
  SDL_Window* window;
  SDL_Renderer* renderer;
  uint64_t tick;
  Scene* scene;
  TTF_Font* font_large;
  TTF_Font* font_medium;
} AppState;
