CC=gcc
CFLAGS=-g
LIBS=-lglut -lGLU -lGL -lpng

%:
	$(CC) $@.c -g -o $@ $(LIBS)

%-test:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$$(echo $@ | sed 's/-.*//')
