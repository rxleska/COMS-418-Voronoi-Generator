
all: build

flags = -Wall -Werror

build: run

run: main.o

main.o: main.cpp
	g++ $(flags) -o main.o main.cpp -lGL -lGLU -lglut