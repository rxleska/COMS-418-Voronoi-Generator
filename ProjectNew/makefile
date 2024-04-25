
# builds the run target
all: run

GPPAF = g++ -Wall -Werror -ggdb 

LINKERFLAGS =  -lGL -lGLU -lglut 

run: main.o EdgeNode.o Arc.o BeachLine.o ParabolaMath.o Vertex.o Callback.o DrawObjects.o EQueue.o Event.o
	$(GPPAF) bin/main.o bin/EdgeNode.o bin/Arc.o bin/BeachLine.o bin/ParabolaMath.o bin/Vertex.o bin/Callback.o bin/DrawObjects.o bin/EQueue.o bin/Event.o -o run $(LINKERFLAGS)


main.o: main.cpp
	$(GPPAF) -c main.cpp -o bin/main.o $(LINKERFLAGS) 


# BeachLine files

EdgeNode.o: lib/BeachLine/EdgeNode.cpp lib/BeachLine/headers/EdgeNode.hpp
	$(GPPAF) -c lib/BeachLine/EdgeNode.cpp -o bin/EdgeNode.o $(LINKERFLAGS)

Arc.o: lib/BeachLine/Arc.cpp lib/BeachLine/headers/Arc.hpp
	$(GPPAF) -c lib/BeachLine/Arc.cpp -o bin/Arc.o $(LINKERFLAGS)

BeachLine.o: lib/BeachLine/BeachLine.cpp lib/BeachLine/headers/BeachLine.hpp
	$(GPPAF) -c lib/BeachLine/BeachLine.cpp -o bin/BeachLine.o $(LINKERFLAGS)

ParabolaMath.o: lib/BeachLine/ParabolaMath.cpp lib/BeachLine/headers/ParabolaMath.hpp
	$(GPPAF) -c lib/BeachLine/ParabolaMath.cpp -o bin/ParabolaMath.o $(LINKERFLAGS)


# DCEL files

Vertex.o: lib/DCEL/Vertex.cpp lib/DCEL/headers/Vertex.hpp
	$(GPPAF) -c lib/DCEL/Vertex.cpp -o bin/Vertex.o $(LINKERFLAGS)


#OGL files

Callback.o: lib/OGL/Callback.cpp lib/OGL/headers/Callback.hpp
	$(GPPAF) -c lib/OGL/Callback.cpp -o bin/Callback.o $(LINKERFLAGS)


DrawObjects.o: lib/OGL/DrawObjects.cpp lib/OGL/headers/DrawObjects.hpp
	$(GPPAF) -c lib/OGL/DrawObjects.cpp -o bin/DrawObjects.o $(LINKERFLAGS)


#Event Queue files

EQueue.o: lib/EventQueue/EQueue.cpp lib/EventQueue/headers/EQueue.hpp
	$(GPPAF) -c lib/EventQueue/EQueue.cpp -o bin/EQueue.o $(LINKERFLAGS)

Event.o: lib/EventQueue/Event.cpp lib/EventQueue/headers/Event.hpp lib/BeachLine/headers/ParabolaMath.hpp
	$(GPPAF) -c lib/EventQueue/Event.cpp -o bin/Event.o $(LINKERFLAGS)


clean:
	rm -f bin/*.o run


valgrind: run #write valgrind output to file
	valgrind --leak-check=full --log-file="valgrind_output.log" ./run 