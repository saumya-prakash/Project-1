
all: exp.out exp2.out

brute_dir=../brute_force
genetic_dir=../genetic

brute=$(brute_dir)/brute_force.h $(brute_dir)/brute_force.cpp
genetic=$(genetic_dir)/genetic.h $(genetic_dir)/genetic.cpp


exp.out: exp.cpp $(brute) $(genetic)
	g++ exp.cpp $(brute_dir)/brute_force.cpp $(genetic_dir)/genetic.cpp -o exp.out


exp2.out: exp2.cpp $(brute) $(genetic)
	g++ exp2.cpp $(brute_dir)/brute_force.cpp $(genetic_dir)/genetic.cpp -o exp2.out


clean:
	rm -f *.out