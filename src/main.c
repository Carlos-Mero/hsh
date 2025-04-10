#define SDL_MAIN_USE_CALLBACKS 1  // use the callbacks instead of main()
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

typedef struct {
  SDL_Window* window;
  SDL_Renderer* renderer;
} AppState;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  SDL_SetAppMetadata("HaiShangHua", "0.0.1", "com.mel_carlos.hsh");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  AppState* as = (AppState*)SDL_calloc(1, sizeof(AppState));

  *appstate = as;

  if (!SDL_CreateWindowAndRenderer("HaiShangHua", 640, 480, 0, &as->window, &as->renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;  /* carry on with the program! */
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState* as = (AppState*)appstate;
  SDL_SetRenderDrawColor(as->renderer, 0xbd, 0xd0, 0xf1, SDL_ALPHA_OPAQUE_FLOAT);

  SDL_RenderClear(as->renderer);
  SDL_RenderPresent(as->renderer);

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {}
