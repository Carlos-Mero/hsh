#include "scene.h"

#include "objects.h"
#include "appstate.h"

// static void scene_process_0(void* this, double delta) {}

// static void scene_render_0(const void* this, SDL_Renderer* rr) {}

// static void scene_handle_event_0(void* this, SDL_Event* e) {}

static void scene_destruct_0(void* this) {}

Scene* init_scene_0(void* appstate) {
  AppState* as = (AppState*)appstate;
  Scene* scene = (Scene*)SDL_calloc(1, sizeof(Scene));

  scene->node_count = 1;
  scene->nodes = SDL_malloc(scene->node_count * sizeof(Node));
  scene->nodes[0] = (Node*)create_main_menu(appstate);

  scene->_process = NULL;
  scene->_render = NULL;
  scene->_handle_event = NULL;
  scene->_destruct = scene_destruct_0;
  return scene;
}
