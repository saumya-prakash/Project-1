#include <bits/stdc++.h>

using namespace std;

class BruteForce
{
private:
    int m, n;   // number of candidate sites, number of clients
    vector<int> construction;
    vector<vector<int>> cost;
    vector<long double> traffic;

    vector<int> allotment;

public:
    BruteForce(int _m, int _n, vector<int> &_construction, vector<vector<int>> &_cost, vector<long double> &_traffic):
        m(_m), n(_n), construction(_construction), cost(_cost), traffic(_traffic), allotment(vector<int>(n, -1))
    {}

    pair<int, int> solve();


private:
    void generate_check(int cur, int &best, int &worst);
};

