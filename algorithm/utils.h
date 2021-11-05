#include <bits/stdc++.h>

using namespace std;


vector<int> random_chromosome(int m, int n);

void permutate(int begin, int end, vector<int> &);

void print_chromosome(vector<int> &chromosome, int m, int n);


int objective_function(vector<int> &chromosome, int m, int n, vector<int> &construction, vector<vector<int>> &weight);

pair<vector<int>, vector<int>> crossover(vector<int> &chr1, vector<int> &chr2, int m, int n);

void validate(vector<int> &chromosome, int m, int n);