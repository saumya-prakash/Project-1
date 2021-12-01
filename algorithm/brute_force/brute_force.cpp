#include "brute_force.h"


pair<int, int> BruteForce::solve()
{
    // can assign any station to a given client
    // generate all such assignments and check

    allotment = vector<int>(n, -1);

    int best = INT_MAX;
    int worst = INT_MIN;
    generate_check(0, best, worst);

    return pair<int, int>(best, worst);
}


void BruteForce::generate_check(int cur, int &best, int &worst)
{
    if(cur == n)    // all clients assigned to some station
    {
        // calculate the total cost of this assignment
        vector<int> status(m, 0);

        int tmp = 0;
        for(int i=0; i<allotment.size(); i++)
        {
            int st_id = allotment[i];
            status[st_id] = 1;

            tmp += cost[i][st_id];
        }

        for(int i=0; i<status.size(); i++)
        {
            if(status[i] == 1)
                tmp += construction[i];

        }

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





