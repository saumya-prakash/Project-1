
all: exp.out exp2.out


BRUTE_DIR=../brute_force
GENETIC_DIR=../genetic
FLAGS=

exp.out: exp.cpp brute_force.o genetic.o
	g++ $(FLAGS) exp.cpp brute_force.o genetic.o -o exp.out


exp2.out: exp2.cpp brute_force.o genetic.o
	g++ $(FLAGS) exp2.cpp brute_force.o genetic.o -o exp2.out



brute_force.o: $(BRUTE_DIR)/brute_force.h $(BRUTE_DIR)/brute_force.cpp
	g++ $(FLAGS) $(BRUTE_DIR)/brute_force.cpp  -c


genetic.o: $(GENETIC_DIR)/genetic.h $(GENETIC_DIR)/genetic.cpp
	g++ $(FLAGS) $(GENETIC_DIR)/genetic.cpp -c


clean:
	rm -f *o .out
	