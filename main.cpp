#include <iostream>
#include <typeinfo>
#include "fraction.h"
#include "matrix.h"

using namespace std;

int main()
{
    Matrix matrix{3, 3};
    matrix.Solve();

    Fraction fraction{-4, -2};
    std::cout << 3 + Fraction{3} << "\n";

    return 0;
}
