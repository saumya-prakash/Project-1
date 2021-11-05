#include "utils.h"


int main()
{
    int m = 0;
    cout<<"Enter number of candidate locations: ";
    cin>>m;

    // Candidate sites are numbered from 1 to m

    cout<<"Enter the cost function: ";
    vector<int> construction(m+1, 0);
    
    for(int i=1; i<=m; i++)
        cin>>construction[i];

    int n = 0;
    cout<<"Enter number of clients: ";
    cin>>n;

    // Clients are numbered from 1 to n

    cout<<"Enter the cost matrix: ";
    vector<vector<int>> weight(n+1, vector<int>(m+1, 0));
    
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            cin>>weight[i][j];


    // Define the initial chromosomes
    int k = 10;

    


    return 0;
}