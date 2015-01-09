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
