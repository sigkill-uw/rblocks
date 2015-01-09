#define _FONT_C_

#include <stdint.h>
#include <SDL.h>

#include "font.h"
#include "fontdef.h"
#include "common.h"

const int internal_width = 8;
const int internal_height = 8;

static SDL_Texture *font[128];

void font_init(SDL_Renderer *r)
{
	int i, j, k;
	uint16_t buffer[internal_width * internal_height];

	for(i = 128; i --;)
	{
		font[i] = SDL_CreateTexture(r, SDL_PIXELFORMAT_ARGB4444, SDL_TEXTUREACCESS_STATIC, internal_width, internal_height);
		SDL_SetTextureBlendMode(font[i], SDL_BLENDMODE_BLEND);

		for(j = 0; j < internal_height; j ++)
			for(k = internal_width; k --;)
				buffer[j * internal_width + (internal_width - k - 1)] = (((fontdef[i][j] >> k) & 1) ? 0xffff : 0);

		SDL_UpdateTexture(font[i], NULL, (const void *)buffer, 2 * internal_width);
	}
}

void font_quit(void)
{
	int i;

	for(i = 128; i --;)
		SDL_DestroyTexture(font[i]);
}

void font_write(SDL_Renderer *r, const char *str, int x, int y, int size)
{
	SDL_Rect re;

	re.x = x;
	re.y = y;
	re.w = size;
	re.h = size;

	for(; *str; str ++)
	{
		SDL_RenderCopy(r, font[(int)*str], NULL, &re);
		re.x += size;
	}
}
