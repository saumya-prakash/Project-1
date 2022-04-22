
all: a.out

FLAGS=
GENETIC_DIR=../genetic

a.out: main.cpp utils.o graph.o genetic.o
		g++ main.cpp utils.o graph.o genetic.o $(FLAGS) -o a.out


utils.o: utils.h utils.cpp
		g++ utils.cpp $(FLAGS) -c


graph.o: graph.h graph.cpp
		g++ graph.cpp $(FLAGS) -c


genetic.o: $(GENETIC_DIR)/genetic.h $(GENETIC_DIR)/genetic.cpp
		g++ $(GENETIC_DIR)/genetic.cpp $(FLAGS) -c


clean:
	rm -f *.out *.o