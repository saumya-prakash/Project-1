#include "utils.h"
#include "graph.h"
#include "../genetic/genetic.h"

void process(const string &line)
{
    unordered_map<int, int> node_to_id, id_to_node;

    istringstream iss(line);

    int n = 0;
    int a = 0;
    while(iss>>a)
    {
        node_to_id[a] = n;
        id_to_node[n] = a;
        ++n;
    }


    n = node_to_id.size();  // total number of nodes

    // Now create the graph corresponding to this component.
    vector<vector<pair<int, long double>>> graph = get_graph(node_to_id);

    // get a connected component now
    // The partition is creating disconnected graphs. Now what to do?????
    // Option one - take the largest connected component. It is very likely that the disconnected
    // components lie on the outer periphery and don't contribute much. 
    vector<int> final_nodes = normalize(graph);
    
    // Find the actual node_IDs
    for(int i=0; i<final_nodes.size(); i++)
    {
        int a = final_nodes[i];
        final_nodes[i] = id_to_node[a];
    }

    node_to_id.clear();
    id_to_node.clear();

    n = 0;
    for(auto a: final_nodes)
    {
        node_to_id[a] = n;
        id_to_node[n] = a;
        n++;
    }

    // n = total number of nodes in this normalized sub-graph/component
    graph = get_graph(node_to_id);
    if(n == 4)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<graph[i].size(); j++)
                cout<<graph[i][j].first<<" "<<graph[i][j].second<<" ";
            cout<<endl;
        }
    }


    // Get the candidte sites

    // For testing only. Actual implementation to be done
    int m = 5;
    vector<int> sites(m);
    sites[m-5] = 2;
    sites[m-4] = 100;
    sites[m-3] = 200;
    sites[m-2] = 994;
    sites[m-1] = 1245;
    // sites[5] = 2148;
    // sites[6] = 5769;
    // sites[7] = 9925;
    // sites[8] = 4598;
    // sites[9] = 10054;


    // Get the construction costs
    // Keep the construction costs same for now
    vector<long double> construction_cost(m, 1.00);


    // Get the distance matrix
    cout<<"Computing distance matrix..."<<endl;
    vector<vector<long double>> dist = calculate_distance_matrix(graph, sites);

    // cout<<dist.size()<<" "<<dist[0].size()<<'\n';

    // cout<<dist[0][0]<<" "<<dist[0][100]<<'\n';

    // // Get the traffic levels
    vector<long double> traffic = get_traffic(node_to_id);


    // Call the genetic algorithm
    cout<<"n = "<<n<<'\n';
    cout<<"m = "<<m<<'\n';        

    GeneticAlgorithm ga(m, n, construction_cost, dist, traffic);
    ga.solve();

    cout<<fixed;
    cout<<ga.best_objective_value()<<'\n';
}