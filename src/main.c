#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

#include "core.h"
#include "scene.h"
#include "appstate.h"

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  SDL_SetAppMetadata("HaiShangHua", "0.0.1", "com.mel_carlos.hsh");

  if (!SDL_Init(SDL_INIT_VIDEO) || !TTF_Init()) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  AppState* as = (AppState*)SDL_calloc(1, sizeof(AppState));

  *appstate = as;

  if (!SDL_CreateWindowAndRenderer("HaiShangHua", 960, 640, 0, &as->window, &as->renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  SDL_SetRenderDrawBlendMode(as->renderer, SDL_BLENDMODE_BLEND);

  as->font_large = TTF_OpenFont("./res/LXGWWenKaiLite-Regular.ttf", 42);
  if (!as->font_large) {
    SDL_Log("Error when loading font LXGWWenKaiLite-Regular.ttf: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  as->scene = init_scene_0(as);

  as->tick = SDL_GetTicksNS();

  return SDL_APP_CONTINUE;  /* carry on with the program! */
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  AppState* as = (AppState*)appstate;
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  handle_event((Node*)as->scene, event);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState* as = (AppState*)appstate;
  uint64_t ntick = SDL_GetTicksNS();
  double delta = (ntick - as->tick) / 1e9;
  as->tick = ntick;
  SDL_SetRenderDrawColor(as->renderer, 0xbd, 0xd0, 0xf1, SDL_ALPHA_OPAQUE_FLOAT);

  SDL_RenderClear(as->renderer);

  process((Node*)as->scene, delta);
  render((Node*)as->scene, as->renderer);

  SDL_RenderPresent(as->renderer);

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  AppState* as = (AppState*)appstate;
  TTF_CloseFont(as->font_large);
  destruct((Node*)as->scene);
}
