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
        stub.cpp \
        $(NULL)

targets default: $(TARGETS)

$(PROGFILES:.cpp=): main.o stub.o
	$(CC) -o cg02 main.o stub.o ${LFLAGS}

depend :
	makedepend ${PROGFILES}
clean :
	rm cg02 main.o stub.o
# DO NOT DELETE
