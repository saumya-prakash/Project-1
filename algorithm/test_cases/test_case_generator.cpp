#include <bits/stdc++.h>

using namespace std;

int main()
{
    srand(time(NULL));

    int m = 50;     // number of candidate sites
    int n = 10000;    // number of nodes

    vector<int> construction_cost(m, 0);
    for(int i=0; i<m; i++)
        construction_cost[i] = 1; //rand()%100 + 1;


    vector<vector<int>> distance_cost(n, vector<int>(m, 0));
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
        {
            if(rand()%5 == 0)
                distance_cost[i][j] = rand()%1000 + 1000;
            else
                distance_cost[i][j] = rand()%100 + 1;
        }


    // write to a file

    string filename = to_string(n) + "_" + to_string(m);

    ofstream fi;
    fi.open(filename, ofstream::out);

    fi<<m<<" "<<n<<endl;
    for(int i=0; i<m; i++)
        fi<<construction_cost[i]<<" ";
    
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
            fi<<distance_cost[i][j]<<" ";
        fi<<endl;
    }

    fi.close();
    return 0;
}