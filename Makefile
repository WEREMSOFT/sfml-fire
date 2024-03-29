SRC = $(shell find src -name *.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))
CC = g++
FLAGS = -g -O0
TARGET = bin/main.bin
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CC) -c $(FLAGS) $^ -o $@

clean:
	rm -rf $(TARGET) $(OBJ)

run_main: clean all
	$(TARGET)

