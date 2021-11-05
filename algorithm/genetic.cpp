#include "utils.h"


int main()
{
    srand(time(NULL));

    int m = 0;
    cout<<"Enter number of candidate locations: ";
    cin>>m;

    // Candidate sites are numbered from 0 to m-1

    cout<<"Enter the cost function: ";
    vector<int> construction(m, 0);
    
    for(int i=0; i<m; i++)
        cin>>construction[i];

    int n = 0;
    cout<<"Enter number of clients: ";
    cin>>n;

    // Clients are numbered from 0 to n-1

    cout<<"Enter the cost matrix: ";
    vector<vector<int>> weight(n, vector<int>(m, 0));
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin>>weight[i][j];


    cout<<endl<<endl;

    // Define the initial chromosomes
    

    vector<vector<int>> population;
    vector<int> value;

    int total = 0;

    int ini_num = 10;
    for(int i=0; i<ini_num; i++)
    {
        vector<int> tmp = random_chromosome(m, n);
        population.push_back(tmp);

        int a = objective_function(tmp, m, n, construction, weight);
        total += a;
        value.push_back(a);
    }

    // Run for 1000 iterations
    int iter = 1000;
    while(iter > 0)
    {
        // Select 2 chromosomes

        vector<int> chr1, chr2;

        int cnt = 2;
        for(int i=0; i<population.size() && cnt>0; i++)
        {
            int cur = value[i];

            double prob = 1 - (double)value[i] / total;

            if(drand48() <= prob)
            {
                chr2 = chr1;
                chr1 = population[i];

                cnt--;
            }
        }

        if(cnt > 0)
        {
            continue;
        }


        // 2-point Crossover
        pair<vector<int>, vector<int>> children = crossover(chr1, chr2, m, n);


        // Validate
        validate(children.first, m, n);
        validate(children.second, m, n);


        // Add to the population

        population.push_back(children.first);
        int a = objective_function(children.first, m, n, construction, weight);
        total += a;
        value.push_back(a);

        population.push_back(children.second);
        a = objective_function(children.second, m, n, construction, weight);
        total += a;
        value.push_back(a);


        iter--;
    }


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

