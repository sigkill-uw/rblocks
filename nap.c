#define _NAP_C_

#if defined(_WIN32)
	#include <windows.h>
#elif defined(__unix__) || defined(__linux__) || defined(__APPLE)
	#include <time.h>
#else
	#include <SDL.h>
#endif

#include <time.h>

void nap(int millisecs)
{
	#if defined(_WIN32)
		Sleep(millisecs);
	#elif defined(__unix__) || defined(__linux__) || defined(__APPLE)
		struct timespec ts = {millisecs / 1000, (millisecs % 1000) * 1000 * 1000};
		nanosleep(&ts, NULL);
	#else
		SDL_Delay(millisecs);
	#endif
}
