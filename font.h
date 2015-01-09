#ifndef _FONT_H_
#define _FONT_H_

#include <SDL.h>

void font_init(SDL_Renderer *r);
void font_quit(void);
void font_write(SDL_Renderer *r, const char *str, int x, int y, int scale);

#endif
