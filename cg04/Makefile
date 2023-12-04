## Compiler
CC=g++
## Linker
LD=$(CC)
## Flags
CPPFLAGS = -Wall -g -DLINUX
LFLAGS = -lglut -L/usr/lib -L/usr/X11R6/lib -lXi -lXmu -lGL -lGLU -lm

TARGETS = $(PROGFILES:.cpp=)

PROGFILES = \
        main.cpp \
		objects.cpp \
        $(NULL)

targets default: $(TARGETS)

$(PROGFILES:.cpp=): main.o objects.o
	$(CC) -o cg04 main.o  objects.o ${LFLAGS}

depend :
	makedepend ${PROGFILES}
clean :
	rm -rf cg04 main.o objects.o
# DO NOT DELETE
