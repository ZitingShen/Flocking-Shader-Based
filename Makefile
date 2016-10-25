ifeq ($(shell uname -s), Darwin)
LDFLAGS=-L/opt/ports/lib -framework OpenGL -lglfw -lGLEW -lm
else
LDFLAGS=-lX11 -lGL -lGLU —lglut -lglfw -lGLEW -lm
endif
CC = g++
CFLAGS=-g -Wall -std=c++11 -I/opt/ports/include

TARGET = flocking
SRC = $(TARGET).cc

LIB = gl_replacement.o my_matrix.o list.o boid.o view.o goal.o initshader.o
all: flocking

flocking: $(SRC) $(LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC) $(LIB)

#my_matrix_test: $(SRC) $(LIB)
#	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC) $(LIB)

gl_replacement.o: gl_replacement.cc gl_replacement.h
	$(CC) $(CFLAGS) -c gl_replacement.cc

my_matrix.o: my_matrix.cc my_matrix.h
	$(CC) $(CFLAGS) -c my_matrix.cc

list.o: list.cc list.h
	$(CC) $(CFLAGS) -c list.cc

boid.o: boid.cc boid.h
	$(CC) $(CFLAGS) -c boid.cc

view.o: view.cc view.h
	$(CC) $(CFLAGS) -c view.cc

goal.o: goal.cc goal.h
	$(CC) $(CFLAGS) -c goal.cc

initshader.o: initshader.c
	$(CC) $(CFLAGS) -c initshader.c

clean:
	rm $(TARGET) $(LIB)
