INCLUDE = -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -I/usr/include/GL -I/usr/include
LINKER = -L/usr/lib -lSDL -lpthread -lGL -lGLU -lglut
NAME = labyrinth2
LIBDIR =
COMPILERFLAGS = -Wall
OBJFILES = shape.o
EVERYTHING = $(INCLUDE) $(LIBDIR) $(LINKER) $(COMPILERFLAGS)
all:    main.cpp main.h
	g++ $(EVERYTHING) -c shape.cpp
	g++ $(EVERYTHING) -o $(NAME) main.cpp $(OBJFILES)
clean:
	rm *~
	rm labyrinth2
