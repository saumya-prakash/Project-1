#include "brute_force.h"


pair<long double, long double> BruteForce::solve()
{
    // can assign any station to a given client
    // generate all such assignments and check

    allotment = vector<int>(n, -1);

    long double best = numeric_limits<long double>::max();
    long double worst = numeric_limits<long double>::lowest();
    generate_check(0, best, worst);

    return pair<long double, long double>(best, worst);
}


void BruteForce::generate_check(int cur, long double &best, long double &worst)
{
    if(cur == n)    // all clients assigned to some station
    {
        // calculate the total cost of this assignment
        vector<int> status(m, 0);

        long double tmp = 0;
        for(int i=0; i<allotment.size(); i++)
        {
            int st_id = allotment[i];
            status[st_id] = 1;

            tmp += cost[i][st_id]/traffic[i];
        }

        for(int i=0; i<status.size(); i++)
        {
            if(status[i] == 1)
                tmp += construction[i];

        }

        values.push_back(tmp);

        best = min(best, tmp);
        worst = max(worst, tmp);

        return;
    }

    for(int i=0; i<m; i++)
    {
        allotment[cur] = i;
        generate_check(cur+1, best, worst);
    }

    return;
}


void BruteForce::save_space()
{
    sort(values.begin(), values.end());
    
    ofstream fi("space.txt", ostream::out);

    for(auto a: values)
        fi<<a<<'\n';

    fi.close();
    return;
}


