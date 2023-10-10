// compile with external.cpp
#include <iostream>
extern double warming; // use warming from anther file

// function prototypes
void update(double dt);
void local();

using std::cout;
void update(double dt)
{
    extern double warming; // optional redeclaration
    warming += dt;
    cout << "Updateing global warming to " << warming << " degrees. \n";
}

void local()
{
    double warming = 0.8; // new variable hides external one
    cout << "Local warming = " << warming << " degrees. \n";
    // Access global varibale with the scope resolution operator
    cout << "But global warming = " << ::warming << " degrees. \n";
}