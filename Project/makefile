
# builds the run target
all: run

GPPAF = g++ -Wall -Werror -ggdb 


run: main.o vertex.o
	$(GPPAF) -o run bin/main.o bin/Vertex.o

main.o: main/main.cpp
	$(GPPAF) -c main/main.cpp -o bin/main.o

vertex.o: lib/Vertex.cpp
	$(GPPAF) -c lib/Vertex.cpp -o bin/Vertex.o


clean:
	rm -f bin/*.o run