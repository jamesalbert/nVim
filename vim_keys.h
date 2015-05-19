#ifndef VIM_KEYS_H
#define VIM_KEYS_H

#include <nspireio2.h>
#include <SDL/SDL.h>
#include <stdbool.h>

#include "vim_panels.h"
#include "vim_lines.h"

bool vim_HandleKeys(SDL_keysym*, Panels*, Lines*);

#endif