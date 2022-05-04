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
    if(n <= 100)    // MAYBE TOO SMALL COMPONENT????
    {
        // for(int i=0; i<n; i++)
        // {
        //     for(int j=0; j<graph[i].size(); j++)
        //         cout<<graph[i][j].first<<" "<<graph[i][j].second<<" ";
        //     cout<<endl;
        // }

        return;
    }


    // Get the traffic levels
    cout<<"[-] Reading demands.csv..."<<endl;
    vector<long double> traffic = get_traffic(node_to_id);
    cout<<"[+] Done"<<endl;

    // Get the candidate sites
    cout<<"[-] Proposing candidate sites"<<endl;
    vector<int> sites = get_sites(graph, traffic);
    int m = sites.size();
    cout<<"[+] Done"<<endl;

    cout<<"Total number of nodes = "<<n<<endl;
    cout<<"Number of candidate sites = "<<m<<endl;

    // Get the construction costs
    // Keep the construction costs same for now
    vector<long double> construction_cost(m, 1000.00);



    // Get the distance matrix
    cout<<"[-] Computing the distance matrix..."<<endl;
    vector<vector<long double>> dist = calculate_distance_matrix(graph, sites);
    cout<<"[+] Done"<<endl;


    // cout<<dist.size()<<" "<<dist[0].size()<<'\n';

    // cout<<dist[0][0]<<" "<<dist[0][100]<<'\n';


    // Call the genetic algorithm
    GeneticAlgorithm ga(m, n, construction_cost, dist, traffic);
    
    cout<<"Running the genetic algorithm..."<<endl;
    ga.solve();
    cout<<"[+] Done"<<endl;

    cout<<fixed;
    cout<<"Best objective value = "<<ga.best_objective_value()<<'\n';


    vector<int> chrm = ga.best_chromosome();
    cout<<"Stations to be built: ";
    for(int i=0; i<m; i++)
        if(chrm[i] >= 0)
            cout<<"station-"<<i<<" ";

    cout<<"\n\n";

    vector<int> station_nodes;

    for(int i=0; i<m; i++)
        if(chrm[i] >=0 )
        {
            // cout<<"Actual node in the graph = "<<sites[i]<<'\n';
            station_nodes.push_back(sites[i]);

            // cout<<"Actual node in the map = "<<id_to_node[sites[i]]<<'\n';
            // Now find the corresponding lat-long pair
        }
    

    // sites = vector<int>(station_nodes);
    // m = sites.size();


    // GeneticAlgorithm fa(m, n, construction_cost, dist, traffic);
    
    // fa.solve();

    // cout<<fixed;
    // cout<<"Best objective value = "<<fa.best_objective_value()<<'\n';

    cout<<"[-] Storing the results..."<<endl;
    store_results(sites, station_nodes, id_to_node);
    cout<<"[+] Done"<<endl;

    return;
}