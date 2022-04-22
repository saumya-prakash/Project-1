
all: a.out

FLAGS=


a.out: main.cpp brute_force.o
	g++ $(FLAGS) main.cpp brute_force.o -o a.out


brute_force.o: brute_force.h brute_force.cpp
	g++ $(FLAGS) brute_force.cpp -c


clean:
	rm -f *.out *.o