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


bool connected_graph(const vector<vector<pair<int, long double>>> &graph)
{
    int n = graph.size();

    vector<int> status(n, 0);

    for(int i=0; i<n; i++)
    {
        if(status[i] != 0)
            continue;

        int cnt = 1;

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

        cout<<cnt<<endl;
    }


    return true;
}

vector<vector<long double>> calculate_distance_matrix(const vector<vector<pair<int, long double>>> &graph, const vector<int> &sites)
{
    int n = graph.size();
    int m = sites.size();

    vector<vector<long double>> dist(n, vector<long double>(m, -1.00));


    // The partition is creating disconnected graphs. Now what to do?????
    // Option one - take the largest connected component. It is very likely that the disconnected
    // components lie on the outer periphery and don;t contribute much. 

    cout<<connected_graph(graph)<<endl;
    return dist;

    for(int i=0; i<m; i++)
    {
        int s = sites[i];

        vector<long double> tmp = dijkstra(s, graph);

        for(int j=0; j<n; j++)
            dist[j][i] = tmp[j];
    }

    return dist;
}


