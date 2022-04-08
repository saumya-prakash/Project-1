#include "genetic.h"


// TODO: Implement CULLING MAYBE?? -> then maybe use linked list to store population and value?

void GeneticAlgorithm::solve()
{
    // Create the initial chromosomes

    // population = vector<vector<int>>();
    // value = vector<int>();

    while(population.size() < INITIAL_POPULATION_SIZE)
    {
        vector<int> tmp = random_chromosome();

        long double a = fitness(tmp);
        total += a;
        population.push_back(tmp);
        value.push_back(a);

    }

    // Run for 'iter' iterations
    
    int iter = 1;
    // O(N*[N + mlog(m) + n])
    while(iter <= NUMBER_OF_GENERATIONS)
    {
        // cout<<"Iteration: "<<iter<<"..."<<endl;

        // Can do culling here
        
        cull();

        // // Select 2 chromosomes
        pair<vector<int>, vector<int>> individuals = select();

        // 2-point crossover
        pair<vector<int>, vector<int>> children = crossover(individuals.first, individuals.second);

        // Validate, and mutate if something wrong
        validate(children.first);
        validate(children.second);


        // Add to the population
        long double a = fitness(children.first);
        total += a;
        population.push_back(children.first);
        value.push_back(a);

        a = fitness(children.second);
        total += a;
        population.push_back(children.second);
        value.push_back(a);

        iter++;  
    }

    return;
}



// create a fitness() function tht will assign proper weights to the individuals
long double GeneticAlgorithm::fitness(const vector<int> &chromosome)
{
    long double a = objective_function(chromosome);

    int n = population.size();

    mean = (static_cast<long double>(n)/(n+1))*mean + a/static_cast<long double>(n+1);

    return mean/a;
}


// Calculates the objective function on the given chromosome 
// m*log(m) + m*log(m) + n
// O(m*log(m) + n) 
long double GeneticAlgorithm::objective_function(const vector<int> &chromosome)
{
    long double res = 0;  // to store the result

    vector<int> aux;
    for(int i=0; i<m; i++)
        aux.push_back(chromosome[i]);
    sort(aux.begin(), aux.end());


    for(int i=0; i<m; i++)
    {
        if(chromosome[i] >= 0)
        {
            // cost of constructing the ith station
            res += construction[i];

            // Find the next largest number in the first half of the chromosome
            
            int key = chromosome[i];
            // int a = INT_MAX;

            // // LINEAR approach
            // for(int j=0; j<m; j++)
            // {
            //     if(chromosome[j] > key && chromosome[j] < a)
            //         a = chromosome[j];
            // }

            // if(a == INT_MAX)
            //     a = n;

            // LOGARITHMIC approach            
            int a = locate(key, aux);

            for(int j=key; j<a; j++)
                // assign client-j to the station-i
                res += weight[j][i]/traffic[j];
            
            // cout<<a<<endl;
            // if(a == -1)
            //     cout<<"Next largest number found as "<<a<<" for "<<key<<endl;
        }
    }

    return res;
}




// Creates and returns a random chromosome
// O(m+n)
vector<int> GeneticAlgorithm::random_chromosome()
{
    vector<int> chromosome(m+n, -1);

    // Create the charging station part

    // put a compulsory 0
    chromosome[0] = 0;

    // store other IDs
    // IDs in the range of 0 to n-1
    // We can select upto m-1 value from this pool.
    // Each value should be selected eactly once. 0 has already been selected.
    int a = 1;
    for(int i=1; i<n && a<m; i++)
    {
        if(rand()%2 == 0)
            chromosome[a] = -1;

        else
            chromosome[a] = i;

        a++;
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



// Select 2 individuals from the popultion using the roulette-wheel method
pair<vector<int>, vector<int>> GeneticAlgorithm::select()
{
    // Select 2 chromosomes
    
    int ind1 = -1, ind2 = -1;

    // use roulette wheel selection

    // First individual
    long double target = drand48()*total;
    long double sum = 0;
    
    for(int i=0; i<population.size(); i++)
    {
        sum += value[i];
        if(sum >= target)
        {
            ind1 = i;
            break;
        }
    }


    // Second individual
    target = drand48()*(total-value[ind1]);
    sum = 0;

    for(int i=0; i<population.size(); i++)
    {
        if(i != ind1)
            sum += value[i];

        if(sum >= target)
        {
            ind2 = i;
            break;
        }
    }
    
    return {population[ind1], population[ind2]};
}


// Does crossover between 2 chromosomes and returns 2 children
// O(m+n) time
pair<vector<int>, vector<int>> GeneticAlgorithm::crossover(vector<int> &chr1, vector<int> &chr2)
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

    pair<vector<int>, vector<int>> children;
    children.first = child_1;
    children.second = child_2;

    return children;
}



// This function permutates the given array range
// linear time complexity
void GeneticAlgorithm::permutate(int begin, int end, vector<int> &arr)
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





// Does validation of the chromosome
// O(m+n) time
void GeneticAlgorithm::validate(vector<int> &chromosome)
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
            chromosome[i] = -1;         // make this entry of cur -1 [Any other strategy may be thought about]
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


// O(log m)
int GeneticAlgorithm::locate(int key, const vector<int> &arr) const
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





// This function prints the chromosome
// O(m+n)
void GeneticAlgorithm::print_chromosome(const vector<int> &chromosome) const
{
    for(int i=0; i<m; i++)
        cout<<chromosome[i]<<" ";

    cout<<"| ";
    
    for(int i=m; i<chromosome.size(); i++)
        cout<<chromosome[i]<<" ";
    
    cout<<endl;

    return;
}


vector<int> GeneticAlgorithm::best_chromosome() const
{
    int ind = 0;
    long double a = value[0];

    for(int i=0; i<value.size(); i++)
    {
        if(a < value[i])
        {
            a = value[i];
            ind = i;
        }
    }

    return population[ind];
}

long double GeneticAlgorithm::best_objective_value()
{
    int ind = 0;
    long double a = value[0];

    for(int i=0; i<value.size(); i++)
    {
        if(a < value[i])
        {
            a = value[i];
            ind = i;
        }
    }

    return objective_function(population[ind]);
}




void GeneticAlgorithm::cull()
{
    int n = population.size();

    // Remove some of the chromosomes
    int target = int(n-(CULL_PERCENT*n));

    search(0, n-1, target);

    // cout<<n<<" "<<target<<endl;

    // total and mean should be adjusted accordingly !!!!
    for(auto it=value.begin()+target; it != value.end(); ++it)
        total -= *it;
    
    for(auto it=population.begin()+target; it != population.end(); ++it)
    {
        long double a = objective_function(*it);

        mean = (static_cast<long double>(n)/(n-1))*mean - a/static_cast<long double>(n-1);
        n--;
    }

    population.erase(population.begin()+target, population.end());    
    value.erase(value.begin()+target, value.end());
    
    // may need to permutate population and value together

    return;
}


void GeneticAlgorithm::search(int i, int j, int target)
{
    if(i >= j)
        return;

    int k = partition(i, j);

    if(target == k)
        return;
    
    if(target > k)
        search(k+1, j, target);
    
    else
        search(i, k-1, target);

}


int GeneticAlgorithm::partition(int i, int j)
{
    // Choose the last element as the pivot

    int k = 0;
    int l = 0;

    while(l < j)
    {
        if(value[l] >= value[j])
        {
            swap(value[l], value[k]);
            swap(population[l], population[k]);

            k++;
        }

        l++;
    }

    swap(value[l], value[k]);
    swap(population[l], population[k]);
    
    return k;
}