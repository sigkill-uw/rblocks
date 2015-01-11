/*
	nap.c - cross-platform sleep function.
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

#define _NAP_C_

#if defined(_WIN32)
	#include <windows.h>
#elif defined(__unix__) || defined(__linux__) || defined(__APPLE)
	#if __STDC_VERSION__ >= 199901L
		#define _XOPEN_SOURCE 600
	#else
		#define _XOPEN_SOURCE 500
	#endif
	#include <time.h>
#else
	#include <SDL.h>
#endif

void nap(int millisecs)
{
	if(millisecs <= 0)
		return;

	#if defined(_WIN32)
		Sleep(millisecs);
	#elif defined(__unix__) || defined(__linux__) || defined(__APPLE)
		struct timespec tz;

		tz.tv_sec = millisecs / 1000;
		tz.tv_nsec = (millisecs % 1000) * 1000 * 1000;

		nanosleep(&tz, NULL);
	#else
		SDL_Delay(millisecs);
	#endif
}
