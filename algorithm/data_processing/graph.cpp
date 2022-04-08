#include "graph.h"

vector<vector<pair<int, long double>>> get_graph(const unordered_map<int, int> &node_to_id)
{
    int n = node_to_id.size();  // total number of nodes

    vector<vector<pair<int, long double>>> graph(n);

    ifstream fi("./data/edges.csv", istream::in);

    string line;
    int cnt = 0;
    
    getline(fi, line);  // consume the header line

    while(getline(fi, line))
    {
        istringstream iss(line);

        int u = -1, v = -1;
        long double dist = 0.00;

        // It is an undirected graph.
        iss>>u>>v>>dist;

        if(node_to_id.find(u) == node_to_id.end())
            continue;
        
        if(node_to_id.find(v) == node_to_id.end())
            continue;
        
        int a = node_to_id.find(u)->second;
        int b = node_to_id.find(v)->second;

        graph[a].push_back({b, dist});
        graph[b].push_back({a, dist});
    }

    fi.close();
    return graph;
}