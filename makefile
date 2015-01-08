CC = gcc
OUTPUT = rblocks

all: $(OUTPUT)

$(OUTPUT):
	$(CC) -o rblocks main.c nap.c `sdl2-config --cflags --libs`
