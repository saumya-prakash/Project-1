#include <bits/stdc++.h>

using namespace std;


class BruteForce
{
private:
    int m, n;   // number of candidate sites, number of clients
    vector<int> construction;
    vector<vector<int>> cost;

    vector<int> allotment;

public:
    BruteForce(int a, int b): m(a), n(b), construction(vector<int>(m, 0)), cost(vector<vector<int>>(n, vector<int>(m, 0))), allotment(vector<int>(n, -1))
    {
        cout<<"Enter the cost of construction array: ";

        for(int i=0; i<m; i++)
            cin>>construction[i];

        cout<<"Enter the transportation-cost matrix: ";

        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                cin>>cost[i][j];

        return;
    }


    int solve()
    {
        // can assign any station to a given client
        // generate all such assignments and check

        allotment = vector<int>(n, -1);

        int res = INT_MAX;

        generate_check(0, res);

        return res;
    }

private:
    void generate_check(int cur, int &res)
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

            res = min(res, tmp);

            return;
        }

        for(int i=0; i<m; i++)
        {
            allotment[cur] = i;
            generate_check(cur+1, res);
        }

        return;
    }
};



int main()
{
    // Candidate sites are numbered from 0 to m-s
    int m = 0;
    cout<<"Enter number of candidate locations: ";
    cin>>m;

    // Clients are numbered from 0 to n-1
    int n = 0;
    cout<<"Enter number of clients: ";
    cin>>n;


    BruteForce bf = BruteForce(m, n);

    // get the optimal value using brute-force technique
    cout<<"Calculating..."<<endl;
    int res = bf.solve();

    cout<<"Optimal value = "<<res<<endl;


    return 0;
}
