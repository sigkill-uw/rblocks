/*
	game.h - header file for rblocks game engine.
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

#ifndef _GAME_H_
#define _GAME_H_

#define BUCKET_WIDTH	10
#define BUCKET_HEIGHT	20

typedef struct
{
	uint8_t grid[BUCKET_WIDTH][BUCKET_HEIGHT];
} gamestate_t;

void gamestate_init(gamestate_t *g);
void gamestate_tick(gamestate_t *g);

#endif
