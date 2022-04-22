// #include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

int main()
{
    srand48(time(NULL));

    int m = 0;     // number of candidate sites
    int n = 0;    // number of nodes

    cout<<"Enter number of candidate sites: ";
    cin>>m;

    cout<<"Enter number of nodes: ";
    cin>>n;

    vector<long double> construction_cost(m, 0.00);
    for(int i=0; i<m; i++)
        construction_cost[i] = drand48()*100 + 1;


    vector<vector<long double>> distance_cost(n, vector<long double>(m, 0.00));
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
        {
            if(rand()%5 == 0)
                distance_cost[i][j] = drand48()*1000 + 1000;
            else
                distance_cost[i][j] = drand48()*100 + 1;
        }


    vector<long double> traffic(n, 0.00);
    for(int i=0; i<n; i++)
        traffic[i] = drand48()*2;

    // write to a file

    string filename = to_string(n) + "_" + to_string(m);

    ofstream fi;
    fi.open(filename, ofstream::out);

    fi<<m<<" "<<n<<endl;

    for(int i=0; i<m; i++)
        fi<<construction_cost[i]<<" ";
    fi<<endl;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
            fi<<distance_cost[i][j]<<" ";
        fi<<endl;
    }

    for(int i=0; i<n; i++)
        fi<<traffic[i]<<" ";
    fi<<endl;

    fi.close();
    return 0;
}