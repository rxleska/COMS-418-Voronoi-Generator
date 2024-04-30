
# builds the run target
all: run

GPPAF = g++ -Wall -Werror -ggdb 

LINKERFLAGS =  -lGL -lGLU -lglut 

run: bin/main.o bin/EdgeNode.o bin/Arc.o bin/BeachLine.o bin/ParabolaMath.o bin/Vertex.o bin/Callback.o bin/DrawObjects.o bin/EQueue.o bin/Event.o bin/Edge.o lib/CONST.hpp bin/Face.o bin/DCEL.o bin/PseudoEdge.o
	$(GPPAF) bin/main.o bin/EdgeNode.o bin/Arc.o bin/BeachLine.o bin/ParabolaMath.o bin/Vertex.o bin/Callback.o bin/DrawObjects.o bin/EQueue.o bin/Event.o bin/Edge.o bin/Face.o bin/DCEL.o bin/PseudoEdge.o -o run $(LINKERFLAGS)


bin/main.o: main.cpp lib/CONST.hpp
	$(GPPAF) -c main.cpp -o bin/main.o $(LINKERFLAGS) 


# BeachLine files

bin/EdgeNode.o: lib/BeachLine/EdgeNode.cpp lib/BeachLine/headers/EdgeNode.hpp lib/CONST.hpp
	$(GPPAF) -c lib/BeachLine/EdgeNode.cpp -o bin/EdgeNode.o $(LINKERFLAGS)

bin/Arc.o: lib/BeachLine/Arc.cpp lib/BeachLine/headers/Arc.hpp lib/CONST.hpp
	$(GPPAF) -c lib/BeachLine/Arc.cpp -o bin/Arc.o $(LINKERFLAGS)

bin/BeachLine.o: lib/BeachLine/BeachLine.cpp lib/BeachLine/headers/BeachLine.hpp lib/CONST.hpp
	$(GPPAF) -c lib/BeachLine/BeachLine.cpp -o bin/BeachLine.o $(LINKERFLAGS)

bin/ParabolaMath.o: lib/BeachLine/ParabolaMath.cpp lib/BeachLine/headers/ParabolaMath.hpp lib/CONST.hpp
	$(GPPAF) -c lib/BeachLine/ParabolaMath.cpp -o bin/ParabolaMath.o $(LINKERFLAGS)


# DCEL files

bin/Vertex.o: lib/DCEL/Vertex.cpp lib/DCEL/headers/Vertex.hpp lib/CONST.hpp
	$(GPPAF) -c lib/DCEL/Vertex.cpp -o bin/Vertex.o $(LINKERFLAGS)

bin/Edge.o: lib/DCEL/Edge.cpp lib/DCEL/headers/Edge.hpp lib/CONST.hpp
	$(GPPAF) -c lib/DCEL/Edge.cpp -o bin/Edge.o $(LINKERFLAGS)

bin/Face.o: lib/DCEL/Face.cpp lib/DCEL/headers/Face.hpp lib/CONST.hpp
	$(GPPAF) -c lib/DCEL/Face.cpp -o bin/Face.o $(LINKERFLAGS)

bin/DCEL.o: lib/DCEL/DCEL.cpp lib/DCEL/headers/DCEL.hpp lib/CONST.hpp
	$(GPPAF) -c lib/DCEL/DCEL.cpp -o bin/DCEL.o $(LINKERFLAGS)

bin/PseudoEdge.o: lib/DCEL/PseudoEdge.cpp lib/DCEL/headers/PseudoEdge.hpp lib/CONST.hpp
	$(GPPAF) -c lib/DCEL/PseudoEdge.cpp -o bin/PseudoEdge.o $(LINKERFLAGS)

#OGL files

bin/Callback.o: lib/OGL/Callback.cpp lib/OGL/headers/Callback.hpp lib/CONST.hpp
	$(GPPAF) -c lib/OGL/Callback.cpp -o bin/Callback.o $(LINKERFLAGS)


bin/DrawObjects.o: lib/OGL/DrawObjects.cpp lib/OGL/headers/DrawObjects.hpp lib/CONST.hpp
	$(GPPAF) -c lib/OGL/DrawObjects.cpp -o bin/DrawObjects.o $(LINKERFLAGS)


#Event Queue files

bin/EQueue.o: lib/EventQueue/EQueue.cpp lib/EventQueue/headers/EQueue.hpp lib/CONST.hpp
	$(GPPAF) -c lib/EventQueue/EQueue.cpp -o bin/EQueue.o $(LINKERFLAGS)

bin/Event.o: lib/EventQueue/Event.cpp lib/EventQueue/headers/Event.hpp lib/BeachLine/headers/ParabolaMath.hpp lib/CONST.hpp
	$(GPPAF) -c lib/EventQueue/Event.cpp -o bin/Event.o $(LINKERFLAGS)


clean:
	rm -f bin/*.o run valgrind_output.log

rebuild: clean all

progress:
	find . -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "Makefile" \) -exec wc -l {} + | awk '{total += $1} END {print total}'


valgrind: run #write valgrind output to file
	valgrind --leak-check=full --log-file="valgrind_output.log" ./run 