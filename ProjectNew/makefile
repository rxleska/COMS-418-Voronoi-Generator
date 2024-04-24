
# builds the run target
all: run

GPPAF = g++ -Wall -Werror -ggdb 

run: 
	$(GPPAF)

clean:
	rm -f bin/*.o run


valgrind: run #write valgrind output to file
	valgrind --leak-check=full --log-file="valgrind_output.log" ./run 