
# builds the run target
all: run

GPPAF = g++ -Wall -Werror -ggdb 

run: main.o EdgeNode.o Arc.o BeachLine.o ParabolaMath.o Vertex.o
	$(GPPAF) bin/main.o bin/EdgeNode.o bin/Arc.o bin/BeachLine.o bin/ParabolaMath.o bin/Vertex.o -o run


main.o: main.cpp
	$(GPPAF) -c main.cpp -o bin/main.o

EdgeNode.o: lib/BeachLine/EdgeNode.cpp lib/BeachLine/headers/EdgeNode.hpp
	$(GPPAF) -c lib/BeachLine/EdgeNode.cpp -o bin/EdgeNode.o

Arc.o: lib/BeachLine/Arc.cpp lib/BeachLine/headers/Arc.hpp
	$(GPPAF) -c lib/BeachLine/Arc.cpp -o bin/Arc.o

BeachLine.o: lib/BeachLine/BeachLine.cpp lib/BeachLine/headers/BeachLine.hpp
	$(GPPAF) -c lib/BeachLine/BeachLine.cpp -o bin/BeachLine.o

ParabolaMath.o: lib/BeachLine/ParabolaMath.cpp lib/BeachLine/headers/ParabolaMath.hpp
	$(GPPAF) -c lib/BeachLine/ParabolaMath.cpp -o bin/ParabolaMath.o

Vertex.o: lib/DCEL/Vertex.cpp lib/DCEL/headers/Vertex.hpp
	$(GPPAF) -c lib/DCEL/Vertex.cpp -o bin/Vertex.o


clean:
	rm -f bin/*.o run


valgrind: run #write valgrind output to file
	valgrind --leak-check=full --log-file="valgrind_output.log" ./run 