#ifndef _GAME_H_
#define _GAME_H_

extern const int bucket_width;
extern const int bucket_height;

typedef struct
{
	int no;
} gamestate_t;

void gamestate_tick(gamestate_t *g);

#endif
