
all: exp.out exp2.out


brute_dir=../brute_force
genetic_dir=../genetic


exp.out: exp.cpp brute_force.o genetic.o
	g++ exp.cpp brute_force.o genetic.o -o exp.out


exp2.out: exp2.cpp brute_force.o genetic.o
	g++ exp2.cpp brute_force.o genetic.o -o exp2.out



brute_force.o: $(brute_dir)/brute_force.h $(brute_dir)/brute_force.cpp
	g++ $(brute_dir)/brute_force.cpp -c

genetic.o: $(genetic_dir)/genetic.h $(genetic_dir)/genetic.cpp
	g++ $(genetic_dir)/genetic.cpp -c


clean:
	rm -f *o .out