
all: a.out

FLAGS=


a.out: main.cpp genetic.o
	g++ $(FLAGS) main.cpp genetic.o -o a.out


genetic.o: genetic.h genetic.cpp
	g++ $(FLAGS) genetic.cpp -c



clean:
	rm -f *.out *.o