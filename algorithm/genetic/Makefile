
all: a.out


a.out: main.cpp genetic.o
	g++ main.cpp genetic.o -o a.out


genetic.o: genetic.h genetic.cpp
	g++ genetic.cpp -c



clean:
	rm -f *.out *.o