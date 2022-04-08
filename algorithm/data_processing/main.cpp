#include <iostream>
#include <fstream>
#include "utils.h"

using std::string;
using std::cin;
using std::cout;
using std::ifstream;
using std::istream;
using std::getline;

int main()
{
    // Get the components one by one and run the algorithm on them

    ifstream fi("./data/components.txt", istream::in);

    string line;
    
    while(getline(fi, line))
    {
        process(line);


        // Just one component experiment
        break;
    }



    fi.close();

    return 0;
}