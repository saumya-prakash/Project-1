#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, long double>>> get_graph(const unordered_map<int, int> &node_to_id);

unordered_set<int> normalize(vector<vector<pair<int, long double>>> &graph, const unordered_map<int, int> &id_to_node);

vector<long double> get_traffic(const unordered_map<int, int> &node_to_id);

vector<vector<long double>> calculate_distance_matrix(const vector<vector<pair<int, long double>>> &graph, const vector<int> &sites);