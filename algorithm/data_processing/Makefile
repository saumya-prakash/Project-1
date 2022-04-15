
all: a.out

FLAGS=-g

a.out: main.cpp utils.o graph.o
		g++ main.cpp utils.o graph.o $(FLAGS) -o a.out


utils.o: utils.h utils.cpp
		g++ utils.cpp $(FLAGS) -c


graph.o: graph.h graph.cpp
		g++ graph.cpp $(FLAGS) -c


clean:
	rm -f *.out *.o