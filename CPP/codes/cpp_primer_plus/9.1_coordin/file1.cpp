// file1.cpp -- exampple of a three-file program
#include <iostream>
#include "coordin.h"  // structure templates, function prototypes
using namespace std;


int main()
{
    rect rplace;
    polar pplace;

    cout << "Enter the x and y values: ";
    while (cin >> rplace.x >> rplace.y) {
        pplace = rect_to_polar(rplace);
        show_polar(pplace);
        cout << "Next two numbers (q to quit): ";
    }
    cout << "Bye! \n";
    return 0;
}

// g++ -I ./include -o test ./src/*.cpp file1.cpp