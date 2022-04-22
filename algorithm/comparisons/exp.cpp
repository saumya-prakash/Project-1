/* 
writes the results to the 'stats' file
writes <size of the input (m=n), time taken by brute_force, time taken by GA>
*/

#include "../brute_force/brute_force.h"
#include "../genetic/genetic.h"


void generate_test_case(int m, int n, vector<long double> &construction_cost, vector<vector<long double>> &distance_cost, vector<long double> &traffic)
{
    construction_cost = vector<long double>(m, 0.00);
    
    for(int i=0; i<m; i++)
        construction_cost[i] = rand()%100 + 1;


    distance_cost = vector<vector<long double>>(n, vector<long double>(m, 0.00));
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            
            if(rand()%5 == 0)
                distance_cost[i][j] = drand48()*1000 + 1000;
            else
                distance_cost[i][j] = drand48()*100 + 1;


    traffic = vector<long double>(n, 0.00);
    for(int i=0; i<n; i++)
        traffic[i] = drand48()*2;

    return;
}



int main()
{    
    srand48(time(NULL));
    
    vector<long double> construction;
    vector<vector<long double>> cost;
    vector<long double> traffic;

    ofstream of("stats");

    int mx[] = {2, 3, 4, 5, 6, 7, 8, 9};
    int ny[] = {2, 3, 4, 5, 6, 7, 8, 9};

    vector<pair<int, int>> aux;

    // m^n -> i^j
    for(int i=2; i<=9; i++)
    {
        for(int j=i; j<=9; j++)
        {
            generate_test_case(i, j, construction, cost, traffic);

            BruteForce bf(i, j, construction, cost, traffic);

            clock_t start = clock();
            bf.solve().first;
            clock_t end = clock();

            double elapsed1 = (double)(end-start)/CLOCKS_PER_SEC;
            
            
            GeneticAlgorithm ga(i, j, construction, cost, traffic);

            start = clock();
            ga.solve();
            end = clock();

            double elapsed2 = (double)(end-start)/CLOCKS_PER_SEC;

            of<<i<<" "<<j<<" "<<elapsed1<<" "<<elapsed2<<endl;
        }
    }


    of.close();

    return 0;
}