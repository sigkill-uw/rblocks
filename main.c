#include <stdio.h>
#include <time.h>

#include <SDL.h>

#include "nap.h"

inline void prtime(void);

int main(void)
{
	return 0;
}

inline void prtime(void)
{
	time_t now;
	char buffer[10 + 1 + 1]; /* "[xx:xx:xx] " */

	now = time(NULL);

	strftime(buffer, 12, "[%T] ", localtime(&now));
	fputs(buffer, stdout);
}
