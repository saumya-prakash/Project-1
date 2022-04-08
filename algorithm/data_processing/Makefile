
all: a.out


a.out: main.cpp utils.o graph.o
		g++ main.cpp utils.o graph.o -o a.out


utils.o: utils.h utils.cpp
		g++ utils.cpp -c


graph.o: graph.h graph.cpp
		g++ graph.cpp -c


clean:
	rm -f *.out *.o