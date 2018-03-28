#include <iostream>
#include <typeinfo>
#include <cassert>
#include "fraction.h"
#include "matrix.h"

using namespace std;

int main()
{
    std::cout << "How many linear equations are there?\n";
    int numEquations{0};
    std::cin >> numEquations;
    assert(numEquations > 0);
    std::cout << "How many different variables are there? (maximum 4: x, y, z, w )\n";
    int numVariables{0};
    std::cin >> numVariables;
    assert(numVariables > 0 && numVariables <= 4);

    std::cin.ignore(24000, '\n');

    Matrix matrix{numVariables, numEquations};

    // Fill the equations:
    for (int column{0}; column < matrix.GetColomsAmount(); ++column) {
        matrix.FillEquation(column);
    }

    // Solve the equation.
    matrix.SolveTraditional();

    return 0;
}

int oldMain() {
    Fraction a{66};
    Fraction b{7, 3};
    Fraction c{49};
    std::cout << a - (b * c) << "\n";

    return 0;
}
