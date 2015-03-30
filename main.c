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
#include "icon.h"

/* Rendering code is, in theory, agnostic to these */
#define WINDOW_WIDTH 460
#define WINDOW_HEIGHT 550

/* ms per tick */
#define FRAME_DURATION 25

int main(void)
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event ev;
	int timer;
	gamestate_t game;

	prtime(); puts("rblocks - an open source, cross-platform arcade game written in C");
	prtime(); puts("Written by sigkill for rcode. Built on " __DATE__ " at " __TIME__);

	/* Intialize SDL */
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		die("Couldn't initialize SDL");

	/* Queue up the SDL cleanup function. I feel like this is a little useless but whatever */
	if(atexit(SDL_Quit))
		die("Couldn't queue cleanup mechanism");

	/* Make a window */
	window = SDL_CreateWindow(
		"rblocks",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL);
	
	if(!window)
		die("Couldn't create window");

	/* Set the icon - errors handled within */
	set_icon(window);

	prtime(); puts("Spawned a window");

	/* Create the renderer */
	renderer = SDL_CreateRenderer(window, -1, 0);
	if(!renderer)
		die("Couldn't create renderer");

	prtime(); puts("Created a renderer");

	/* Initialize fonts and queue font cleanup */
	font_init(renderer);
	if(atexit(SDL_Quit))
		die("Couldn't queue cleanup mechanism");

	/* Initialize other video stuff - errors handled within */
	video_init(renderer);

	prtime(); puts("Initialized video assets");

	/* Initialize gamestate */
	gamestate_init(&game);

	/* Loop runs once every `FRAME_DURATION` millseconds;
	  	I'm told that it's good practice to run game logic and rendering independently,
		but for these purposes (small, discrete state changes) rendering is useless in the absence game logic. */
	timer = (int)SDL_GetTicks() + FRAME_DURATION;
	for(;;)
	{
		/* Event loop */
		while(SDL_PollEvent(&ev))
		{
			if(ev.type == SDL_QUIT) /* Quit message */
			{
				prtime(); puts("Received quit signal");
				break;
			}
			else if(ev.type == SDL_KEYDOWN) /* Keydown message */
			{
				;
			}
		}

		if(ev.type == SDL_QUIT)
			break;

		/* Advance the state by a single frame */
		gamestate_tick(&game);

		/* Render it */
		video_render(renderer, NULL);

		/* Stall and increment timer. Should be self-correcting. */
		nap(timer - (int)SDL_GetTicks());
		while((int)SDL_GetTicks() < timer);
		timer += FRAME_DURATION;
	}

	/* Destroy our local properties. Font cleanup and SDL cleanup should happen implicitly via atexit */
	video_quit();
	font_quit();
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

	return 0;
}


