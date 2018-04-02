#variables de compilation
SHELL := /bin/sh
CC := gcc
CFLAGS += -flto -Wall -W -pedantic $(shell pkgconf gl sdl SDL_mixer --cflags) -O3 -std=gnu90 -ffast-math
LDFLAGS += -L/usr/X11R6/lib $(shell pkgconf gl sdl SDL_mixer --libs) -lm

TARGET   := association-by-cyberneticgenetics
#variable de nettoyage
RM_F := rm -f

#compilation en paralelle si disponible
ifneq (,$(filter parallel=%,$(DEB_BUILD_OPTIONS)))
 NUMJOBS = $(patsubst parallel=%,%,$(filter parallel=%,$(DEB_BUILD_OPTIONS)))
 MAKEFLAGS += -j$(NUMJOBS)
endif

export

all: $(TARGET)

$(TARGET): main.o model.o
	$(CC) $(CFLAGS)  *.o -o $(TARGET) $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c -c

model.o: model.c model.h
	$(CC) $(CFLAGS) model.c -c

clean:
	-@$(RM_F) *.o *~ core* $(TARGET)
