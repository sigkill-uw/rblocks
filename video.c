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

const color_t c_backdrop =	{0xff, 0x07, 0x1B, 0x30};
const color_t c_grid =		{0xff, 0x10, 0x20, 0x50};
const color_t c_mbox =		{0x99, 0x00, 0x00, 0x00};

inline void set_renderer_color(SDL_Renderer *r, const color_t * const c);

SDL_Texture *next_text;
SDL_Texture *hold_text;
SDL_Texture *score_text;

void video_init(SDL_Renderer *r)
{
	SDL_ClearError();

	next_text = font_render(r, "NEXT", 16);
	hold_text = font_render(r, "HOLD", 16);
	score_text = font_render(r, "SCORE", 16);

	sdl_errdie("Couldn't initalize video stuff");
}

void video_render(SDL_Renderer *r, gamestate_t *g)
{
	int i, j;
	SDL_Rect re;

	g = g;

	SDL_ClearError();

	set_renderer_color(r, &c_backdrop);
	SDL_RenderClear(r);

	font_blit(r, next_text, 2 * margin + block_size * BUCKET_WIDTH, margin + 5);
	font_blit(r, hold_text, 2 * margin + block_size * BUCKET_WIDTH, 3 * margin + 4 * block_size + 5);
	font_blit(r, score_text, 2 * margin + block_size * BUCKET_WIDTH, 5 * margin + 8 * block_size + 16 + 10);

	set_renderer_color(r, &c_grid);

	re.x = margin;
	re.y = margin;
	re.w = block_size * BUCKET_WIDTH + 2;
	re.h = block_size * BUCKET_HEIGHT + 2;
	SDL_RenderDrawRect(r, &re);

	re.y = margin + 1;
	re.w = block_size;
	re.h = block_size;

	for(i = 0; i < BUCKET_HEIGHT; i ++)
	{
		re.x = margin + 1;

		for(j = 0; j < BUCKET_WIDTH; j ++)
		{
			SDL_RenderDrawRect(r, &re);

			re.x += block_size;
		}

		re.y += block_size;
	}

	SDL_RenderPresent(r);

	sdl_errdie("Failed to render");
}

void video_quit(void)
{
	/*
		This is a stub just like its font counterpart, because nuking the renderer in main
		seems to be the only deallocation necessary
	*/
}

inline void set_renderer_color(SDL_Renderer *r, const color_t * const c)
{
	if(SDL_SetRenderDrawColor(r, c->r, c->g, c->b, c->a) < 0)
		die("Failed to render");
}
