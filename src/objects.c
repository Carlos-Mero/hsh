#include "objects.h"

#include "appstate.h"

#include <SDL3_image/SDL_image.h>

void bkg_img_process(void* this, double delta) {
  BackGroundImage* bg = (BackGroundImage*)this;
  if (bg->activated) {
    bg->current_alpha = (uint8_t)((bg->current_alpha * (bg->duration - delta)) / bg->duration);
  } else {
    bg->current_alpha = 0xff - (uint8_t)(((0xff - bg->current_alpha) * (bg->duration - delta)) / bg->duration);
  }
}

void bkg_img_render(const void* this, SDL_Renderer* rr) {
  SDL_SetRenderTarget(rr, NULL);
  const BackGroundImage* bg = (BackGroundImage*)this;
  SDL_RenderTexture(rr, bg->texture, NULL, NULL);
  SDL_SetRenderDrawColor(rr, 0x42, 0x42, 0x42, 0x81);
  SDL_RenderFillRect(rr, &bg->menu_area);
  SDL_SetRenderDrawColor(rr, 0x00, 0x00, 0x00, 0x81);
  SDL_RenderRect(rr, &bg->menu_area);

  // black cover of this background
  SDL_SetRenderDrawColor(rr, 0x00, 0x00, 0x00, bg->current_alpha);
  SDL_RenderFillRect(rr, NULL);
  SDL_SetRenderDrawColor(rr, 0xff, 0xff, 0xff, 0xff);
}

void bkg_img_destruct(void* this) {
  BackGroundImage* bg = (BackGroundImage*)this;
  SDL_DestroyTexture(bg->texture);
}

BackGroundImage* create_background_image(void* appstate, const char* img_path) {
  AppState* as = (AppState*)appstate;
  BackGroundImage* bg = (BackGroundImage*)SDL_calloc(1, sizeof(BackGroundImage));
  bg->texture = IMG_LoadTexture(as->renderer, img_path);

  int w; int h;
  SDL_GetWindowSize(as->window, &w, &h);
  bg->menu_area = (SDL_FRect){0.0, 0.0, (float)w / 4.0f, (float)h};

  bg->activated = true;
  bg->current_alpha = 0xff;
  bg->duration = 1.4f;

  bg->_process = bkg_img_process;
  bg->_render = bkg_img_render;
  bg->_destruct = bkg_img_destruct;
  return bg;
}

static void main_menu_render(const void* this, SDL_Renderer* rr) {}

static void main_menu_destruct(void* this) {}

static void main_menu_handle_event(void* this, SDL_Event* e) {}

MainMenu* create_main_menu(void* appstate) {
  AppState* as = (AppState*)appstate;
  MainMenu* menu = (MainMenu*)SDL_calloc(1, sizeof(MainMenu));
  int w; int h;
  SDL_GetWindowSize(as->window, &w, &h);

  menu->node_count = 6;
  menu->nodes = SDL_malloc(menu->node_count * sizeof(Node));
  menu->nodes[0] = (Node*)create_background_image(as, "res/menu.jpeg");
  float init_h = ((float)h - ((float)h - 300.0f))/2;
  menu->nodes[1] = (Node*)create_main_menu_button(as, (SDL_FRect){0.0f, init_h, (float)w / 4.0f, 60.0f}, "从头开始");
  menu->nodes[2] = (Node*)create_main_menu_button(as, (SDL_FRect){0.0f, init_h + 60.0f, (float)w / 4.0f, 60.0f}, "书接上回");
  menu->nodes[3] = (Node*)create_main_menu_button(as, (SDL_FRect){0.0f, init_h + 120.0f, (float)w / 4.0f, 60.0f}, "画廊");
  menu->nodes[4] = (Node*)create_main_menu_button(as, (SDL_FRect){0.0f, init_h + 180.0f, (float)w / 4.0f, 60.0f}, "章节选择");
  menu->nodes[5] = (Node*)create_main_menu_button(as, (SDL_FRect){0.0f, init_h + 240.0f, (float)w / 4.0f, 60.0f}, "退出游戏");

  menu->_handle_event = main_menu_handle_event;
  menu->_render = main_menu_render;
  menu->_destruct = main_menu_destruct;
  return menu;
}

static void main_menu_button_render(const void* this, SDL_Renderer* rr) {
  Button* button = (Button*)this;
  SDL_SetRenderTarget(rr, NULL);
  if (button->hovering) {
    SDL_SetRenderDrawColor(rr, 0xbd, 0xd0, 0xf1, 0x81);
  } else {
    SDL_SetRenderDrawColor(rr, 0xbd, 0xd0, 0xf1, 0x00);
  }
  SDL_RenderFillRect(rr, &button->body);
  SDL_RenderTexture(rr, button->texture, NULL, &button->text_area);
}

static void main_menu_button_handle_event(void* this, SDL_Event* e) {}

static void main_menu_button_destruct(void* this) {
  Button* button = (Button*)this;
  SDL_DestroyTexture(button->texture);
}

Button* create_main_menu_button(void* appstate, SDL_FRect area, char* text) {
  AppState* as = (AppState*)appstate;
  Button* button = (Button*)SDL_calloc(1, sizeof(Button));

  const float padding_x = 20.0f;
  button->body = area;
  button->text = text;
  button->hovering = false;

  SDL_Color text_color = {0xee, 0xee, 0xee, 0xfc};
  SDL_Surface* text_surface = TTF_RenderText_Blended(as->font_large, text, 0, text_color);
  button->texture = SDL_CreateTextureFromSurface(as->renderer, text_surface);
  int textW = text_surface->w;
  int textH = text_surface->h;
  SDL_DestroySurface(text_surface);

  button->text_area = (SDL_FRect){
    area.x + padding_x, area.y + (area.h - textH) / 2, textW, textH
  };

  button->_render = main_menu_button_render;
  button->_handle_event = main_menu_button_handle_event;
  return button;
}
