/*
	font.c - tiny bitmap font engine for rblocks.
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

#define _FONT_C_

#include <stdint.h>
#include <SDL.h>

#include "font.h"
#include "fontdef.h"
#include "common.h"

static SDL_Texture *font[128];

void font_init(SDL_Renderer *r)
{
	int i, j, k;
	uint16_t buffer[internal_size * internal_size];

	SDL_ClearError();

	for(i = 128; i --;)
	{
		font[i] = SDL_CreateTexture(r, SDL_PIXELFORMAT_ARGB4444, SDL_TEXTUREACCESS_STATIC, internal_size, internal_size);
		SDL_SetTextureBlendMode(font[i], SDL_BLENDMODE_BLEND);

		for(j = 0; j < internal_size; j ++)
			for(k = internal_size; k --;)
				buffer[j * internal_size + (internal_size - k - 1)] = (((fontdef[i][j] >> k) & 1) ? 0xffff : 0);

		SDL_UpdateTexture(font[i], NULL, (const void *)buffer, 2 * internal_size);
	}

	sdl_errdie("Couldn't initialize font");
}

void font_quit(void)
{
	int i;

	SDL_ClearError();

	for(i = 128; i --;)
		SDL_DestroyTexture(font[i]);

	sdl_errdie("Couldn't deallocate font");
}

void font_write(SDL_Renderer *r, const char *str, int x, int y, int size)
{
	SDL_Rect re;

	SDL_ClearError();

	re.x = x;
	re.y = y;
	re.w = size;
	re.h = size;

	for(; *str; str ++)
	{
		SDL_RenderCopy(r, font[(int)*str], NULL, &re);
		re.x += size;
	}

	sdl_errdie("Couldn't render text");
}
