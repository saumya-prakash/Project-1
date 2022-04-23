#include "graph.h"

vector<vector<pair<int, long double>>> get_graph(const unordered_map<int, int> &node_to_id)
{
    int n = node_to_id.size();  // total number of nodes

    vector<vector<pair<int, long double>>> graph(n);

    ifstream fi("./data/edges.csv", istream::in);

    string line;
    
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


bool connected_graph(const vector<vector<pair<int, long double>>> &graph)
{
    int n = graph.size();

    int flag = 0;

    vector<int> status(n, 0);

    for(int i=0; i<n; i++)
    {
        if(status[i] != 0)
            continue;

        int cnt = 1;
        flag++;

        queue<int> qu;
        qu.push(i);
        status[i] = 1;

        while(!qu.empty())
        {
            int cur = qu.front();
            qu.pop();

            for(int j=0; j<graph[cur].size(); j++)
            {
                int b = graph[cur][j].first;

                if(status[b] == 0)
                {
                    ++cnt;
                    status[b] = 1;
                    qu.push(b);
                }
            }

            status[cur] = 2;
        }
        cout<<"\t"<<cnt<<endl;
    }


    if(flag > 1)
        return false;

    return true;
}



vector<int> normalize(vector<vector<pair<int, long double>>> &graph)
{
    int n = graph.size();
    
    int cnt = 0;
    int start = -1;

    vector<int> status(n, 0);

    for(int i=0; i<n; i++)
    {
        if(status[i] != 0)
            continue;
    
        queue<int> qu;
        int cur_cnt = 0;

        qu.push(i);
        status[i] = 1;    

        while(!qu.empty())
        {
            int a = qu.front();
            cur_cnt++;
            qu.pop();

            for(int i=0; i<graph[a].size(); i++)
            {
                int b = graph[a][i].first;

                if(status[b] == 0)
                {
                    qu.push(b);
                    status[b] = 1;
                }
            }

            status[a] = 2;
        }

        // cout<<cnt<<endl;
        if(cur_cnt > cnt)
        {
            cnt = cur_cnt;
            start = i;
        }

    }

    // cout<<start<<" "<<cnt<<endl;

    vector<int> nodes;

    status = vector<int>(n, 0);

    queue<int> qu;

    qu.push(start);
    status[start] = 1;

    while(!qu.empty())
    {
        int a = qu.front();
        nodes.push_back(a);
        qu.pop();

        for(int i=0; i<graph[a].size(); i++)
        {
            int b = graph[a][i].first;

            if(status[b] == 0)
            {
                qu.push(b);
                status[b] = 1;
            }
        }

        status[a] = 2;
    }

    return nodes;
}


vector<long double> get_traffic(const unordered_map<int, int> &node_to_id)
{
    int n = node_to_id.size();  // total number of nodes

    vector<long double> traffic(n, 0.00);

    ifstream fi("./data/demands.csv", istream::in);

    string line;

    getline(fi, line);  // consume the header line

    while(getline(fi, line))
    {
        istringstream iss(line);
        int u = -1;
        long double l = 0.00;
        iss>>u>>l;

        if(node_to_id.find(u) == node_to_id.end())
            continue;
        
        int a = node_to_id.find(u)->second;
        traffic[a] = l;
    }

    fi.close();
    return traffic;
}



vector<long double> dijkstra(int s, const vector<vector<pair<int, long double>>> &graph)
{
    int n = graph.size();

    vector<long double> res(n, -1.00);
    vector<int> status(n, 0);

    priority_queue<pair<long double, int>, vector<pair<long double, int>>, greater<pair<long double, int>>> pq;

    pq.push({0.00, s});

    int cnt = 0;

    while(cnt < n)
    {
        pair<long double, int> hold = pq.top();
        pq.pop();

        long double d = hold.first;
        int a = hold.second;

        if(status[a] != 0)
            continue;

        cnt++;
        status[a] = 1;

        // cerr<<cnt<<endl;


        for(int i=0; i<graph[a].size(); i++)
        {
            int b = graph[a][i].first;
            long double wt = graph[a][i].second;

            if(status[b] != 0)
                continue;

            if(res[b] == -1.00 || res[b] > d+wt)
            {
                res[b] = d + wt;
                pq.push({d+wt, b});
            }
        }
    }


    return res;
}


vector<vector<long double>> calculate_distance_matrix(const vector<vector<pair<int, long double>>> &graph, const vector<int> &sites)
{
    int n = graph.size();
    int m = sites.size();
    
    vector<vector<long double>> dist(n, vector<long double>(m, -1.00));

    // cout<<connected_graph(graph)<<endl;
    // return dist;
    
    for(int i=0; i<m; i++)
    {
        int s = sites[i];

        vector<long double> tmp = dijkstra(s, graph);

        for(int j=0; j<n; j++)
            dist[j][i] = tmp[j];
    }

    return dist;
}



void store_results(const vector<int> &sites, const vector<int> &station_nodes, const unordered_map<int, int> &id_to_node)
{    
    ofstream of("./data/stations_location", ofstream::out);

    for(int i=0; i<sites.size(); i++)
        of<<id_to_node.find(sites[i])->second<<" ";
    
    of<<'\n';

    for(int i=0; i<station_nodes.size(); i++)
        of<<id_to_node.find(station_nodes[i])->second<<" ";

    of<<'\n';

    of.close();
}