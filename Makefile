ifeq ($(shell uname -s), Darwin)
LDFLAGS=-L/usr/local/Cellar/glfw3/3.2.1/lib -framework OpenGL -lglfw3 -lm
else
LDFLAGS=-lX11 -lGL -lGLU -lglfw -lGLEW -lm
endif
CC = g++
CFLAGS=-g -Wall -std=c++11 -I/usr/local/Cellar/glfw3/3.2.1/include

TARGET = my_matrix_test
SRC = $(TARGET).cc
LIB = my_matrix.o
all: my_matrix_test

my_matrix_test: $(SRC) $(LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC) $(LIB)

#gl_replacement.o: gl_replacement.cc gl_replacement.h
#	$(CC) $(CFLAGS) -c gl_replacement.cc

my_matrix.o: my_matrix.cc my_matrix.h
	$(CC) $(CFLAGS) -c my_matrix.cc

clean:
	rm $(TARGET) $(LIB)
