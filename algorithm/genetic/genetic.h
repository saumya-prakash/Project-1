#include <bits/stdc++.h>

using namespace std;


class GeneticAlgorithm
{
private:
    int m, n;   // number of candidate sites, number of clients
    vector<int> construction;
    vector<vector<int>> weight;
    int total;  // to store the sum of values in value[]

    /*******
    Use 'test3' to show that initial poopulation size and number of iterations matter -> (10, 100) to
    (100, 100) to (1000, 10000)
    ********/
    
    const int INITIAL_POPULATION_SIZE = 10;
    const int NUMBER_OF_GENERATIONS = 10000;


public:
    GeneticAlgorithm(int _m, int _n, vector<int> &_construction, vector<vector<int>> &_weight):
        m(_m), n(_n), construction(_construction), weight(_weight), total(0)
    {}

    vector<vector<int>> population;
    vector<int> value;

    void solve();

    void print_chromosome(const vector<int> &chromosome) const;


private:

    vector<int> random_chromosome();

    pair<vector<int>, vector<int>> select();
    void permutate(int begin, int end, vector<int> &arr);

    pair<vector<int>, vector<int>> crossover(vector<int> &chr1, vector<int> &chr2);

    void validate(vector<int> &chromosome);

    int objective_function(vector<int> &chromosome) const;
    int locate(int key, const vector<int> &arr) const;
};