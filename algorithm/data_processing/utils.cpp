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


    int n = node_to_id.size();  // total number of nodes

    // Now create the graph corresponding to this component.

    vector<vector<pair<int, long double>>> graph = get_graph(node_to_id);

    
    
    // Get the candidte sites

    // For testing only. Actual implementation to be done
    vector<int> sites(10);
    sites[0] = 4;
    sites[1] = 100;
    sites[2] = 200;
    sites[3] = 994;
    sites[4] = 1245;
    sites[5] = 2148;
    sites[6] = 5769;
    sites[7] = 9925;
    sites[8] = 4598;
    sites[9] = 10054;


    // Get the construction costs



    // Get the distance matrix
    vector<vector<long double>> dist = calculate_distance_matrix(graph, sites);



    // Get the traffic levels
    vector<long double> traffic = get_traffic(node_to_id);



    // Call the genetic algorithm
    

}