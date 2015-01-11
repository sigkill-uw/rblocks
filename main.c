/*
	main.c - entry point for rblocks.
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

#define _MAIN_C_

#include <stdio.h>
#include <SDL.h>

#include "game.h"
#include "video.h"
#include "common.h"
#include "nap.h"
#include "font.h"

const int window_width = 800;
const int window_height = 550;

const int frame_duration = 40;

int main(void)
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event ev;
	int timer;
	gamestate_t game;

	prtime(); puts("rblocks - an open source, cross-platform arcade game written in C");
	prtime(); puts("Written by sigkill for rcode. Built on " __DATE__ " at " __TIME__);

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		die("Couldn't initialize SDL");

	if(atexit(SDL_Quit))
		die("Couldn't queue cleanup mechanism");

	window = SDL_CreateWindow(
		"rblocks",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		window_width, window_height,
		SDL_WINDOW_OPENGL);
	
	if(!window)
		die("Couldn't create window");

	prtime(); puts("Spawned a window");

	renderer = SDL_CreateRenderer(window, -1, 0);
	if(!renderer)
		die("Couldn't create renderer");

	prtime(); puts("Created a renderer");

	font_init(renderer);
	atexit(font_quit);

	timer = (int)SDL_GetTicks() + frame_duration;
	for(;;)
	{
		while(SDL_PollEvent(&ev))
		{
			if(ev.type == SDL_QUIT)
			{
				prtime(); puts("Received quit signal");
				break;
			}
			else if(ev.type == SDL_KEYDOWN)
			{
				;
			}
		}

		if(ev.type == SDL_QUIT)
			break;

		gamestate_tick(&game);
		video_render(renderer, NULL);

		nap(timer - (int)SDL_GetTicks());
		while((int)SDL_GetTicks() < timer);
		timer += frame_duration;
	}

	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

	return 0;
}


