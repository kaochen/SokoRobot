#Makefile

CC=gcc
CFLAGS= -Wall -Wextra `sdl2-config --cflags --libs`  -lSDL2main -lSDL2_image -lSDL2 -lSDL2_ttf `xml2-config --cflags` `xml2-config --libs`
LDFLAGS=
OBJDIR=obj
EXEC=SokoRobot
DEPS= inc/const.h inc/game.h inc/level.h inc/menu.h inc/sprites.h inc/slc.h
OBJS= $(OBJDIR)/game.o $(OBJDIR)/level.o $(OBJDIR)/main.o $(OBJDIR)/menu.o $(OBJDIR)/sprites.o $(OBJDIR)/slc.o

#first create the obj folder to receive *.o files :
$(shell   mkdir -p $(OBJDIR))

all: $(EXEC)


$(EXEC): $(OBJS)
	$(CC)  -o SokoRobot $(OBJS) $(CFLAGS)

$(OBJDIR)/main.o: src/main.c $(DEPS)
	$(CC) -o $(OBJDIR)/main.o -c src/main.c -I inc $(CFLAGS)

$(OBJDIR)/game.o: src/game.c $(DEPS)
	$(CC) -o $(OBJDIR)/game.o -c src/game.c -I inc $(CFLAGS)

$(OBJDIR)/level.o: src/level.c $(DEPS)
	$(CC) -o $(OBJDIR)/level.o -c src/level.c -I inc $(CFLAGS)

$(OBJDIR)/menu.o: src/menu.c $(DEPS)
	$(CC) -o $(OBJDIR)/menu.o -c src/menu.c -I inc $(CFLAGS)

$(OBJDIR)/sprites.o: src/sprites.c $(DEPS)
	$(CC) -o $(OBJDIR)/sprites.o -c src/sprites.c -I inc $(CFLAGS)

$(OBJDIR)/slc.o: src/slc.c $(DEPS)
	 $(CC) -o $(OBJDIR)/slc.o -c src/slc.c -I inc $(CFLAGS)


clean:
	rm -rf $(OBJDIR)/*.o

mrproper:
	rm -rf $(EXEC)
