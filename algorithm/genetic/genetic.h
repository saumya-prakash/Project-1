#include <bits/stdc++.h>

using namespace std;


class GeneticAlgorithm
{
private:
    int m, n;   // number of candidate sites, number of clients
    vector<int> construction;
    vector<vector<int>> weight;
    vector<long double> traffic;

    long double total;  // to store the sum of special weights assigned to the individuals
    long double mean;

    const int INITIAL_POPULATION_SIZE = 100;
    const int NUMBER_OF_GENERATIONS = 10000;
    const double CULL_PERCENT = 0.25;


public:
    GeneticAlgorithm(int _m, int _n, vector<int> &_construction, vector<vector<int>> &_weight, vector<long double> &_traffic):
        m(_m), n(_n), construction(_construction), weight(_weight), traffic(_traffic), total(0.00), mean(0.00)
    {}

    vector<vector<int>> population;
    vector<long double> value;

    void solve();

    vector<int> best_chromosome() const;
    long double best_objective_value();
    void print_chromosome(const vector<int> &chromosome) const;


private:

    long double objective_function(const vector<int> &chromosome);

    void validate(vector<int> &chromosome);
    
    vector<int> random_chromosome();

    void cull();

    pair<vector<int>, vector<int>> select();
    void permutate(int begin, int end, vector<int> &arr);

    pair<vector<int>, vector<int>> crossover(vector<int> &chr1, vector<int> &chr2);

    

    long double fitness(const vector<int> &chromosome);
    
    int locate(int key, const vector<int> &arr) const;
    
    void search(int i, int j, int target);
    int partition(int i, int j);
};





    /*******
    initial poopulation size and number of iterations matter -> (10, 100) to
    (100, 100) to (1000, 10000)
    ********/
    