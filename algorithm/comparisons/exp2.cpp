/*
writes the results to the 'comps' file
writes <best, worst, GA's answer>
*/

#include "../brute_force/brute_force.h"
#include "../genetic/genetic.h"


void generate_test_case(int m, int n, vector<int> &construction_cost, vector<vector<int>> &distance_cost)
{
    construction_cost = vector<int>(m, 0);
    
    for(int i=0; i<m; i++)
        construction_cost[i] = rand()%100 + 1;


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
    ofstream of("comps", ofstream::app);

    vector<pair<int, int>> aux;

    // m^n -> i^j
    for(int i=0; i<1000; i++)
    {
        int m = rand()%7 + 2;
        int n = rand()%7 + 2;

        vector<int> construction;
        vector<vector<int>> cost;

        generate_test_case(m, n, construction, cost);

        BruteForce bf(m, n, construction, cost);
        pair<int, int> tmp = bf.solve();

        GeneticAlgorithm ga(m, n, construction, cost);
        ga.solve();

        int a = INT_MAX;
        for(auto x: ga.value)
            a = min(a, x);

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