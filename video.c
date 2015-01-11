/*
	video.c - internal rendering for rblocks.
	Copyright (C) 2015 Adam Richardson

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define _VIDEO_C_

#include <stdint.h>
#include <SDL.h>

#include "video.h"

#include "game.h"
#include "common.h"
#include "font.h"

typedef struct
{
	uint_fast8_t a, r, g, b;
} color_t;

const int margin = 25;

const int block_size = 25;

const color_t c_backdrop = {0xff, 0x07, 0x1B, 0x30};
const color_t c_grid = {0xff, 0x10, 0x20, 0x50};

inline void set_renderer_color(SDL_Renderer *r, const color_t * const c);

void video_render(SDL_Renderer *r, gamestate_t *g)
{
	int i, j;
	SDL_Rect re;

	g = NULL;
	if(g){}

	set_renderer_color(r, &c_backdrop);
	SDL_RenderClear(r);

	set_renderer_color(r, &c_grid);

	re.x = margin;
	re.y = margin;
	re.w = block_size * bucket_width + 2;
	re.h = block_size * bucket_height + 2;
	SDL_RenderDrawRect(r, &re);

	re.y = margin + 1;
	re.w = block_size;
	re.h = block_size;

	for(i = 0; i < bucket_height; i ++)
	{
		re.x = margin + 1;

		for(j = 0; j < bucket_width; j ++)
		{
			SDL_RenderDrawRect(r, &re);

			re.x += block_size;
		}

		re.y += block_size;
	}

	re.x = re.y = 0;
	re.w = re.h = 50;

	font_write(r, "ABCDEFGHIJKLM", 0, 0, 32);
	font_write(r, "NOPQRSTUVWXYZ", 0, 50, 32);
	font_write(r, "0123456789", 0, 100, 32);
	font_write(r, "ABCDEFGHIJKLM", 0, 150, 16);
	font_write(r, "NOPQRSTUVWXYZ", 0, 200, 16);
	font_write(r, "0123456789", 0, 250, 16);
	font_write(r, "ABCDEFGHIJKLM", 0, 300, 8);
	font_write(r, "NOPQRSTUVWXYZ", 0, 350, 8);
	font_write(r, "0123456789", 0, 400, 8);

	SDL_RenderPresent(r);
}

inline void set_renderer_color(SDL_Renderer *r, const color_t * const c)
{
	if(SDL_SetRenderDrawColor(r, c->r, c->g, c->b, c->a) < 0)
		die("Failed to render");
}
