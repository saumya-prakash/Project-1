#include "genetic.h"


int main()
{
    // seed the random number generator
    srand(time(NULL));

    // Candidate sites are numbered from 0 to m-1
    int m = 0;
    cout<<"Enter number of candidate locations: ";
    cin>>m;
    
    // Clients are numbered from 0 to n-1
    int n = 0;
    cout<<"Enter number of clients: ";
    cin>>n;


    cout<<"Enter the cost function: ";
    vector<int> construction(m, 0);
    // construction cost for reach candidate site
    for(int i=0; i<m; i++)
        cin>>construction[i];


    cout<<"Enter the cost matrix: ";
    vector<vector<int>> weight(n, vector<int>(m, 0));
    // weight matrix (n x m) (number of clients x number of candidate sites)
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin>>weight[i][j];


    cout<<endl<<endl;
    
    vector<vector<int>> population;
    vector<int> value;

    geneticAlgorithm(m, n, construction, weight, population, value);

    // Print the final result
    int ind = -1;
    int a = INT_MAX;

    for(int i=0; i<value.size(); i++)
    {
        if(value[i] < a)
        {
            a = value[i];
            ind = i;
        }
    }


    cout<<"Minimized value = "<<value[ind]<<endl;
    // print_chromosome(population[ind], m, n);
    cout<<endl;
    cout<<"Stations to be built: ";
    for(int i=0; i<m; i++)
        if(population[ind][i] >= 0)
            cout<<"station-"<<i<<" ";
    
    cout<<endl;

    return 0;
}

