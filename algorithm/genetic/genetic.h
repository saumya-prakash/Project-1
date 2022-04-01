#include <bits/stdc++.h>

using namespace std;


class GeneticAlgorithm
{
private:
    int m, n;   // number of candidate sites, number of clients
    vector<int> construction;
    vector<vector<int>> weight;

    long double total;  // to store the sum of special weights assigned to the individuals
    long double mean;

    const int INITIAL_POPULATION_SIZE = 10;
    const int NUMBER_OF_GENERATIONS = 10000;


public:
    GeneticAlgorithm(int _m, int _n, vector<int> &_construction, vector<vector<int>> &_weight):
        m(_m), n(_n), construction(_construction), weight(_weight), total(0), mean(0.00)
    {}

    vector<vector<int>> population;
    vector<long double> value;

    void solve();

    vector<int> best_chromosome() const;
    int best_objective_value();
    void print_chromosome(const vector<int> &chromosome) const;

    int objective_function(const vector<int> &chromosome);

    void validate(vector<int> &chromosome);
    

private:

    vector<int> random_chromosome();

    pair<vector<int>, vector<int>> select();
    void permutate(int begin, int end, vector<int> &arr);

    pair<vector<int>, vector<int>> crossover(vector<int> &chr1, vector<int> &chr2);

    

    long double fitness(const vector<int> &chromosome);
    
    int locate(int key, const vector<int> &arr) const;
};





    /*******
    initial poopulation size and number of iterations matter -> (10, 100) to
    (100, 100) to (1000, 10000)
    ********/
    