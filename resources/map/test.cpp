#include <iostream>
#include <fstream>
using namespace std;


int main (int argc, char const* argv[])
{
    ifstream infile;
    infile.open("level1.txt" , ios_base::in);
    string hello;
    int left = 0 , top = 0;
    bool isp,isobs;
    
    
    while(true)
    {   
        infile>>hello;   
        infile>>left;
        infile>>top;
        infile>>isobs;
        infile>>isp;
        
        if(infile.eof())
            break;
        
        cout<<hello<<"," << left<<","<<top<<","<<isobs<<","<<isp<<endl;
        
    }
    return 0;
}

