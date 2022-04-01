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
    
    GeneticAlgorithm ga(m, n, construction, weight);
    // ga.solve();

    // // Print the final result

    // cout<<"Objective value = "<<ga.best_objective_value()<<endl;
    // ga.print_chromosome(ga.best_chromosome());
    // cout<<endl;

    // vector<int> arr = ga.best_chromosome();

    // cout<<"Stations to be built: ";
    // for(int i=0; i<m; i++)
    //     if(arr[i] >= 0)
    //         cout<<"station-"<<i<<" ";

    // cout<<endl;

    vector<int> aux(11, -1);

    aux[1] = 0;
    aux[5] = 0;

    aux[6] = 2;
    aux[7] = 4;
    aux[8] = 3;
    aux[9] = 1;
    aux[10] = 0;

    // cout<<endl<<ga.objective_function(aux)<<endl;
    ga.print_chromosome(aux);
    ga.validate(aux);
    ga.print_chromosome(aux);


    return 0;
}

/*******
-1 0 -1 -1 -1 0 | 2 4 3 1 0 
-1 -1 -1 -1 -1 0 | 2 4 3 1 0    -> what to do in this case - only one 0 and nothing else!?
********/