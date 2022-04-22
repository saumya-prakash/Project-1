/*
writes the results to the 'comps' file
writes <best, worst, GA's answer>
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
    ofstream of("comps", ofstream::app);

    vector<pair<int, int>> aux;

    // m^n -> i^j
    for(int i=0; i<1000; i++)
    {
        int m = rand()%7 + 2;
        int n = rand()%7 + 2;

        vector<long double> construction;
        vector<vector<long double>> cost;
        vector<long double> traffic;

        generate_test_case(m, n, construction, cost, traffic);

        BruteForce bf(m, n, construction, cost, traffic);
        pair<long double, long double> tmp = bf.solve();

        GeneticAlgorithm ga(m, n, construction, cost, traffic);
        ga.solve();

        long double a = ga.best_objective_value();

        // if(tmp.first > a)
        // {
        //     of<<tmp.first<<" "<<tmp.second<<" "<<a<<endl;

        //     for(int i=0; i<construction.size(); i++)
        //         of<<construction[i]<<" ";
        //     of<<endl;

        //     for(int i=0; i<cost.size(); i++)
        //     {
        //         for(int j=0; j<cost[i].size(); j++)
        //             of<<cost[i][j]<<" ";

        //         of<<endl;
        //     }

        //     break;
        // }
        
        if(tmp.first <= a)
            of<<tmp.first<<" "<<tmp.second<<" "<<a<<endl;
    }


    of.close();

    return 0;
}