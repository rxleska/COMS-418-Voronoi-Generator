
# builds the run target
all: run

GPPAF = g++ -Wall -Werror -ggdb 


run: main.o vertex.o Beach_Line_RBT.o
	$(GPPAF) -o run bin/main.o bin/Vertex.o bin/Beach_Line_RBT.o

main.o: main/main.cpp
	$(GPPAF) -c main/main.cpp -o bin/main.o

vertex.o: lib/Vertex.cpp
	$(GPPAF) -c lib/Vertex.cpp -o bin/Vertex.o

Beach_Line_RBT.o: lib/Beach_Line_RedBlackTree.cpp 
	$(GPPAF) -c lib/Beach_Line_RedBlackTree.cpp -o bin/Beach_Line_RBT.o

clean:
	rm -f bin/*.o run