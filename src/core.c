#include "core.h"

void process(Node* node, double delta) {
  // for process iteration, subnodes goes first and parent later
  if (node->nodes) {
    for (int i = 0; i < node->node_count; i++) {
      process(node->nodes[i], delta);
    }
  }
  if (node->_process) {
    node->_process(node, delta);
  }
}

void handle_event(Node* node, SDL_Event* e) {
  // for process iteration, subnodes goes first and parent later
  if (node->nodes) {
    for (int i = 0; i < node->node_count; i++) {
      handle_event(node->nodes[i], e);
    }
  }
  if (node->_handle_event) {
    node->_handle_event(node, e);
  }
}

void render(const Node* node, SDL_Renderer* rr) {
  // for render process, the parent should go first
  if (node->_render) {
    node->_render(node, rr);
  }
  if (node->nodes) {
    for (int i = 0; i < node->node_count; i++) {
      render(node->nodes[i], rr);
    }
  }
}

void destruct(Node* node) {
  // subnodes should be destructed first
  if (node->nodes) {
    for (int i = 0; i < node->node_count; i++) {
      destruct(node->nodes[i]);
    }
  }
  SDL_free(node->nodes);
  if (node->_destruct) {
    node->_destruct(node);
  }
  SDL_free(node);
}
