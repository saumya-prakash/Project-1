#include "genetic.h"

// This function creates a random chromosome and returns it
// O(m+n)
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


// This function permutates the given array range
// linear time complexity
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


// This function prints the chromosome
// O(m+n)
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


// O(log m)
int locate(int key, const vector<int> &arr, const int n)
{
    int low = 0;
    int high = arr.size()-1;

    int a = INT_MAX;

    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(arr[mid] == key)
        {
            a = mid;
            break;
        }

        else if(arr[mid] > key)
            high = mid-1;
        
        else
            low = mid+1;
    }

    if(a == arr.size()-1)
        return n;
    
    return arr[a+1];
}



// This function calculates the objective function on the given chromosome 
// m*log(m) + m*log(m) + n
// O(m*log(m) + n) 
int objective_function(vector<int> &chromosome, int m, int n, vector<int> &construction, vector<vector<int>> &weight)
{
    int total = 0;  // to store the value

    vector<int> aux;
    for(int i=0; i<m; i++)
        aux.push_back(chromosome[i]);
    sort(aux.begin(), aux.end());

    // for(int i=0; i<m; i++)
    //     cout<<chromosome[i]<<" ";
    // cout<<endl;

    for(int i=0; i<m; i++)
    {
        if(chromosome[i] >= 0)
        {
            // const of constructing the ith station
            total += construction[i];

            // Find the next largest number in the first half of the chromosome
            
            int key = chromosome[i];
            // int a = INT_MAX;
            // for(int j=0; j<m; j++)
            // {
            //     if(chromosome[j] > key && chromosome[j] < a)
            //         a = chromosome[j];
            // }

            // if(a == INT_MAX)
            //     a = n;
            
            int a = locate(key, aux, n);
            // cout<<key<<"->"<<a<<" "<<b<<endl;
            // assert(a == b);

            for(int j=key; j<a; j++)
            {
                // Assign client-j to the station-i
                total += weight[j][i];
            }
        }
    }

    return total;
}


// This functnio does crossover between 2 chromosomes and returns 2 children
// O(m+n)
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


// This function validates a given chromosome
// O(m+n)
void validate(vector<int> &chromosome, int m, int n)
{
    // Check the station part

    // 0 is a must and no repetition

    vector<int> aux(n, 0);

    for(int i=0; i<m; i++)
    {
        int cur = chromosome[i];

        if(cur >= 0)    // -1s to be ignored
            aux[cur]++;
    }

    // remove duplicates
    for(int i=0; i<m; i++)
    {
        int cur = chromosome[i];

        if(cur >= 0 && aux[cur] > 1)    // cur occurs more than once
        {
            chromosome[i] = -1;         // make this entry of cur -1
            aux[cur]--;                 // decrement the total count of cur
        }
    }

    // if 0 is not present, insert it at some random location
    if(aux[0] == 0)
    {
        int cnt = 0;    // to store the number of -1s
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

    // all numbers from 0 to n-1 should be present, no duplicates allowed

    aux = vector<int>(n, 0);

    for(int i=m; i<chromosome.size(); i++)
    {
        aux[chromosome[i]]++;
    }

    
    int a = 0;
    for(int i=m; i<chromosome.size(); i++)
    {
        int cur = chromosome[i];

        if(aux[cur] > 1)    // cur is repeated -> correct this
        {
            aux[cur]--; // decrement the count of cur

            // Find the first number from 0 to n-1 that is missing
            while(a<n && aux[a] != 0)
                a++;
            
            chromosome[i] = a;  // assign the missing number here
            aux[a] = 1;         // update the count of the missing number
        }
    }

    return;
}



/*************************************************************************************
 * MAIN function ahead
 * ***********************************************************************************/

void geneticAlgorithm(int m, int n, vector<int> &construction, vector<vector<int>> &weight, vector<vector<int>> &population, vector<int> &value)
{
    // Create the initial chromosomes

    population = vector<vector<int>>();
    value = vector<int>();

    int total = 0;  // to store the total fitness value of the population
    int ini_num = 10;
    for(int i=0; i<ini_num; i++)
    {
        vector<int> tmp = random_chromosome(m, n);
        population.push_back(tmp);

        int a = objective_function(tmp, m, n, construction, weight);
        total += a;
        value.push_back(a);
    }


    // Run for 'iter' iterations
    int iter = 10000;
    // O(N*[N + mlog(m) + n])
    while(iter > 0)
    {
        // cout<<iter<<endl;

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


    return;
}


