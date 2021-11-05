#include "utils.h"

vector<int> random_chromosome(int m, int n)
{
    vector<int> chromosome(m+n, 0);

    // Create the charging station part

    // put a compulsory 0
    chromosome[0] = 0;

    // store other IDs
    int a = 1;
    for(int i=1; i<n && a<m; i++)
    {
        if(rand()%2 == 0)
        {
            chromosome[a] = -1;
            a++;
        }

        else
        {
            chromosome[a] = i;
            a++;
        }
    }

    permutate(0, m, chromosome);

    // Create the client ID part

    // assign the IDs
    for(int i=m; i<chromosome.size(); i++)
    {
        chromosome[i] = i-m;
    }

    // permutate
    permutate(m, chromosome.size(), chromosome);


    return chromosome;
}



void permutate(int begin, int end, vector<int> &arr)
{
    // permutate the elements in the range [begin, end)

    for(int i=end-1; i>=begin; i--)
    {
        int n = i-begin+1;

        int ind = rand()%n + begin;

        swap(arr[ind], arr[i]);
    }

    return;
}

void print_chromosome(vector<int> &chromosome, int m, int n)
{
    for(int i=0; i<m; i++)
        cout<<chromosome[i]<<" ";

    cout<<"| ";
    
    for(int i=m; i<chromosome.size(); i++)
        cout<<chromosome[i]<<" ";
    
    cout<<endl;

    return;
}






int objective_function(vector<int> &chromosome, int m, int n, vector<int> &construction, vector<vector<int>> &weight)
{
    int total = 0;

    for(int i=0; i<m; i++)
    {
        if(chromosome[i] >= 0)
        {
            total += construction[i];

            int key = chromosome[i];
            int a = INT_MAX;
            for(int j=0; j<m; j++)
            {
                if(chromosome[j] > key && chromosome[j] < a)
                    a = chromosome[j];
            }

            if(a == INT_MAX)
                a = n;
            
            for(int j=key; j<a; j++)
            {
                // Assign client-j to the station-i
                total += weight[j][i];
            }
        }
    }

    return total;
}

pair<vector<int>, vector<int>> crossover(vector<int> &chr1, vector<int> &chr2, int m, int n)
{
    vector<int> child_1(m+n, -1);
    vector<int> child_2(m+n, -1);

    // first crossover point
    int p1 = rand()%(m-1);

    for(int i=0; i<=p1; i++)
    {
        child_1[i] = chr1[i];
        child_2[i] = chr2[i];
    }

    for(int i=p1+1; i<m; i++)
    {
        child_1[i] = chr2[i];
        child_2[i] = chr1[i];
    }

    // second crossover point
    int p2 = rand()%(n-1);

    for(int i=m; i<=m+p2; i++)
    {
        child_1[i] = chr1[i];
        child_2[i] = chr2[i];
    }

    for(int i=m+p2+1; i<m+n; i++)
    {
        child_1[i] = chr2[i];
        child_2[i] = chr1[i];
    }

    pair<vector<int>, vector<int>> res;
    res.first = child_1;
    res.second = child_2;

    return res;
}



void validate(vector<int> &chromosome, int m, int n)
{
    // Check the station part

    // 0 a must and no repetition

    vector<int> aux(n, 0);

    for(int i=0; i<m; i++)
    {
        int cur = chromosome[i];

        if(cur >= 0)
            aux[cur]++;
    }

    // remove duplicates
    for(int i=0; i<m; i++)
    {
        int cur = chromosome[i];

        if(cur >= 0 && aux[cur] > 1)
        {
            chromosome[i] = -1;
            aux[cur]--;
        }
    }

    // if 0 is not present, insert it randomly at some location
    if(aux[0] == 0)
    {
        int cnt = 0;
        for(int i=0; i<m; i++)
            if(chromosome[i] == -1)
                cnt++;


        cnt = rand()%cnt + 1;
        for(int i=0; i<m; i++)
        {
            if(chromosome[i] == -1)
            {
                cnt--;
                if(cnt == 0)
                {
                    chromosome[i] = 0;
                    break;
                }
            }
        }
    }


    // Check the ID part
    aux = vector<int>(n, 0);

    for(int i=m; i<chromosome.size(); i++)
    {
        aux[chromosome[i]]++;
    }

    int a = 0;

    for(int i=m; i<chromosome.size(); i++)
    {
        int cur = chromosome[i];

        if(aux[cur] > 1)
        {
            // correct this
            aux[cur]--;

            while(a<n && aux[a] != 0)
                a++;
            
            chromosome[i] = a;
            aux[a] = 1;
        }
    }

    return;
}