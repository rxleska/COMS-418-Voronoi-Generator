
# builds the run target
all: run

GPPAF = g++ -Wall -Werror -ggdb 


run: main.o vertex.o Beach_Line_RBT.o Event.o ProjectCalculations.o DCEL.o DCELEdge.o DCELFace.o
	$(GPPAF) -o run bin/main.o bin/Vertex.o bin/Beach_Line_RBT.o bin/Event.o bin/ProjectCalculations.o bin/DCEL.o bin/DCELEdge.o bin/DCELFace.o

main.o: main/main.cpp
	$(GPPAF) -c main/main.cpp -o bin/main.o

vertex.o: lib/Vertex.cpp
	$(GPPAF) -c lib/Vertex.cpp -o bin/Vertex.o

Beach_Line_RBT.o: lib/Beach_Line_RedBlackTree.cpp 
	$(GPPAF) -c lib/Beach_Line_RedBlackTree.cpp -o bin/Beach_Line_RBT.o

Event.o: lib/Event.cpp
	$(GPPAF) -c lib/Event.cpp -o bin/Event.o

ProjectCalculations.o: lib/ProjectCalculations.cpp
	$(GPPAF) -c lib/ProjectCalculations.cpp -o bin/ProjectCalculations.o

DCEL.o: lib/DCEL.cpp
	$(GPPAF) -c lib/DCEL.cpp -o bin/DCEL.o

DCELEdge.o: lib/DCELEdge.cpp
	$(GPPAF) -c lib/DCELEdge.cpp -o bin/DCELEdge.o

DCELFace.o: lib/DCELFace.cpp
	$(GPPAF) -c lib/DCELFace.cpp -o bin/DCELFace.o

clean:
	rm -f bin/*.o run