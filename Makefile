CC = gcc
CFLAGS = -Wall -W -pedantic `sdl-config --cflags` -march=i386 -Os
CLIBS = -L/usr/X11R6/lib -lGL `sdl-config --libs` -lm -lSDL_mixer

association: main.o model.o
	$(CC) $(CFLAGS) $(CLIBS) *.o -o association
	upx association
main.o: main.c
	$(CC) $(CFLAGS) main.c -c
model.o: model.c model.h
	$(CC) $(CFLAGS) model.c -c

clean:
	@echo Cleaning up...
	rm -f *.o *~ core*
	@echo Done.
