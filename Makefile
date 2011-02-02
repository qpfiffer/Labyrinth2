INCLUDE = `sdl-config --cflags` -I/usr/include/GL -I/usr/include -I/usr/include/SDL
LINKER = `sdl-config --libs` -lGL -lGLU -lSDL_image
NAME = btw
LIBDIR =
COMPILERFLAGS = -std=c++0x -Wall -g
OBJFILES = room.o shape.o config.o world.o
EVERYTHING = $(INCLUDE) $(LIBDIR) $(LINKER) $(COMPILERFLAGS)
all:    main.cpp main.h
	g++ $(EVERYTHING) -c room.cpp
	g++ $(EVERYTHING) -c config.cpp
	g++ $(EVERYTHING) -c shape.cpp
	g++ $(EVERYTHING) -c world.cpp
	g++ $(EVERYTHING) -o $(NAME) main.cpp $(OBJFILES)
clean:
	rm *.o
	rm $(NAME)
