#include "brute_force.h"


int main()
{
    // Candidate sites are numbered from 0 to m-s
    int m = 0;
    cout<<"Enter number of candidate locations: ";
    cin>>m;

    // Clients are numbered from 0 to n-1
    int n = 0;
    cout<<"Enter number of clients: ";
    cin>>n;

    vector<int> construction(m, 0);
    cout<<"Enter the cost of construction array: ";

    for(int i=0; i<m; i++)
        cin>>construction[i];


    vector<vector<int>> cost(n, vector<int>(m, 0));
    cout<<"Enter the transportation-cost matrix: ";

    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin>>cost[i][j];


    BruteForce bf = BruteForce(m, n, construction, cost);

    // get the optimal value using brute-force technique
    cout<<"Calculating..."<<endl;

    pair<int, int> res = bf.solve();
    cout<<"Optimal value = "<<res.first<<endl;
    cout<<"Worst value = "<<res.second<<endl;

    return 0;
}