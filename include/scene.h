#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "core.h"

typedef struct {
  NODE;
  uint32_t res_count;
  SDL_Texture** res;
} Scene;

extern Scene* init_scene_0(void* appstate);
