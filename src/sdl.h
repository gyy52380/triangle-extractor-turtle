#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "typedef.h"


namespace sdl
{


bool init(SDL_Window* &the_window_handle, SDL_GLContext &the_gl_context, const u32 SCREEN_WIDTH, const u32 SCREEN_HEIGHT);
void cleanup(SDL_Window* &the_window_handle, SDL_GLContext &the_gl_context);

extern glm::vec2 mouse_pos;
extern bool mouse_pressed[3];
void update_events(bool &requested_exit);


}
