#include <bits/stdc++.h>

using namespace std;

class BruteForce
{
private:
    int m, n;   // number of candidate sites, number of clients
    vector<long double> construction;
    vector<vector<long double>> cost;
    vector<long double> traffic;

    vector<int> allotment;

public:
    BruteForce(int _m, int _n, vector<long double> &_construction, vector<vector<long double>> &_cost, vector<long double> &_traffic):
        m(_m), n(_n), construction(_construction), cost(_cost), traffic(_traffic), allotment(vector<int>(n, -1))
    {}

    pair<long double, long double> solve();
    void save_space();


private:
    vector<long double> values;
    void generate_check(int cur, long double &best, long double &worst);
};

