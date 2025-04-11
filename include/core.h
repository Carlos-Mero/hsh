#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define NODE struct {\
  void (*_process)(void* this, double delta);\
  void (*_handle_event)(void* this, SDL_Event* e);\
  void (*_render)(const void* this, SDL_Renderer* rr);\
  void (*_destruct)(void* this);\
  void** nodes;\
  uint32_t node_count;\
}

typedef NODE Node;

extern void process(Node* node, double delta);
extern void handle_event(Node* node, SDL_Event* e);
extern void render(const Node* node, SDL_Renderer* rr);
extern void destruct(Node* node);
