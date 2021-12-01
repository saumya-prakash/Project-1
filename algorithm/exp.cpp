#include "./brute_force/brute_force.h"
#include "./genetic/genetic.h"

void generate_test_case(int m, int n, vector<int> &construction_cost, vector<vector<int>> &distance_cost)
{
    construction_cost = vector<int>(m, 0);
    
    for(int i=0; i<m; i++)
        construction_cost[i] = 1; //rand()%100 + 1;


    distance_cost = vector<vector<int>>(n, vector<int>(m, 0));
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            
            if(rand()%5 == 0)
                distance_cost[i][j] = rand()%100 + 250;
            
            else
                distance_cost[i][j] = rand()%100 + 1;

    return;
}



int main()
{    
    vector<int> construction;
    vector<vector<int>> cost;

    ofstream of("stats");

    // m^n -> i^j
    for(int i=2; i<=10; i++)
    {
        for(int j=2; j<=8; j++)
        {
            generate_test_case(i, j, construction, cost);

            BruteForce bf(i, j, construction, cost);

            clock_t start = clock();
            int res = bf.solve().first;
            clock_t end = clock();

            double elapsed1 = (double)(end-start)/CLOCKS_PER_SEC;
            
            vector<vector<int>> population;
            vector<int> value;
            start = clock();
            geneticAlgorithm(i, j, construction, cost, population, value);
            end = clock();

            double elapsed2 = (double)(end-start)/CLOCKS_PER_SEC;

            of<<i<<" "<<j<<" "<<elapsed1<<" "<<elapsed2<<endl;
        }
    }


    of.close();

    return 0;
}