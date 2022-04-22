
all: a.out

FLAGS=
GENETIC_DIR=../genetic


a.out: main.cpp utils.o graph.o genetic.o
		g++ $(FLAGS) main.cpp utils.o graph.o genetic.o -o a.out


utils.o: utils.h utils.cpp
		g++ $(FLAGS) utils.cpp -c


graph.o: graph.h graph.cpp
		g++ $(FLAGS) graph.cpp -c


genetic.o: $(GENETIC_DIR)/genetic.h $(GENETIC_DIR)/genetic.cpp
		g++ $(FLAGS) $(GENETIC_DIR)/genetic.cpp -c


clean:
	rm -f *.out *.o