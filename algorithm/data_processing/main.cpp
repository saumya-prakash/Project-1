#include <iostream>
#include <fstream>
#include "utils.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::istream;
using std::getline;
using std::ofstream;


int main()
{
    // Clear the output file
    ofstream of("./data/stations_location", ofstream::out);
    of.close();

    // Get the components one by one and run the algorithm on them

    cout<<"[-] Opening components.txt file..."<<endl;
    ifstream fi("./data/components.txt", istream::in);
    cout<<"[+] Done"<<endl;

    cout<<endl;

    string line;
    int cnt = 1;

    while(getline(fi, line))
    {
        // cout<<"Component-"<<cnt<<": "<<endl;
        cnt++;

        process(line);

        cout<<endl<<endl;

        // // Just one component experiment
        // break;
    }



    fi.close();

    return 0;
}