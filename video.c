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

	font_write(r, "PYROTECHNICK", 0, 0, 10);
	font_write(r, "SDL 2", 0, 50, 10);

	SDL_RenderPresent(r);
}

inline void set_renderer_color(SDL_Renderer *r, const color_t * const c)
{
	if(SDL_SetRenderDrawColor(r, c->r, c->g, c->b, c->a) < 0)
		die("Failed to render");
}
