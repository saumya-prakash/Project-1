#include "utils.h"
#include "graph.h"
// #include "../genetic/genetic.h"

void process(const string &line)
{
    unordered_map<int, int> node_to_id, id_to_node;

    istringstream iss(line);

    int cnt = 0;
    int a = 0;
    while(iss>>a)
    {
        node_to_id[a] = cnt;
        id_to_node[cnt] = a;
        ++cnt;
    }

    // Now create the graph corresponding to this component.

    vector<vector<pair<int, long double>>> graph = get_graph(node_to_id);


    // Get the candidte sites

    // Do BFS


    // Get the traffic levels


    // Call the genetic algorithm
}