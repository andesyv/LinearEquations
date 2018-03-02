#include <iostream>
#include <typeinfo>
#include "fraction.h"
#include "matrix.h"

using namespace std;

int main()
{
    std::cout << "How many linear equations are there?\n";
    int numEquations{0};
    std::cin >> numEquations;
    std::cout << "How many different variables are there? (x, y, z, ...)\n";
    int numVariables{0};
    std::cin >> numVariables;

    Matrix matrix{numVariables, numEquations};

    // Fill the equations:
    for (int column{0}; column < matrix.NumberOfColoms(); ++column) {
        matrix.FillEquation(column);
    }

    matrix.Solve();

    return 0;
}
