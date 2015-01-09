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


