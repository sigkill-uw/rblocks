CC = gcc
SOURCE = main.c game.c video.c nap.c common.c font.c
OBJECTS = $(SOURCE:.c=.o)
OUTPUT = rblocks
CFLAGS = `sdl2-config --cflags --libs` -Wall -Wextra -Werror -O4 -std=c99 -pedantic

.PHONY: all
.PHONY: clean

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJECTS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

font.o: font.c fontdef.h
	$(CC) $(CFLAGS) -c font.c

fontdef.h: fontref.txt fontgen.py
	python2 fontgen.py < fontref.txt > fontdef.h

clean:
	-rm $(OUTPUT) $(OBJECTS) fontdef.h
