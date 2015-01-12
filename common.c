#define _COMMON_C_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL.h>

#include "common.h"

void die(const char *msg)
{
	prftime(stderr);
	fputs("Fatal error: ", stderr);
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

void sdl_errdie(const char *msg)
{
	const char *foo;

	foo = SDL_GetError();
	if(foo && *foo)
		die(msg);
}

void prtime(void)
{
	prftime(stdout);
}

void prftime(FILE *f)
{
	time_t now;
	char buffer[10 + 1 + 1]; /* "[xx:xx:xx] " */

	now = time(NULL);

	strftime(buffer, 12, "[%T] ", localtime(&now));
	fputs(buffer, f);
}
