#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>

using namespace std;


int main(int argc, char *argv[])
{
    srand(time(NULL));
    std::ofstream infile;
    infile.open("tile map level1.txt" , std::ios_base::out);
    if(infile.is_open()) cout<<"SUCCESS";
    else cout<<"FAIL";
    int left = 0 , top = 0;
    int matrixRow = 0, matrixColumn = 0;
    bool isobs;

    isobs = false;
    while(matrixRow < 161){
        matrixColumn = 0;
    while(matrixColumn < 241){
        infile << left <<' ' << top << ' ' << isobs << endl;
        left += 5;
        matrixColumn++;
        isobs = (rand()%10)? false : true;
    }
        left = 0;
        top += 5;
        matrixRow++;
    }

    return 0;
}


