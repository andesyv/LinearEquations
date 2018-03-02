#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "fraction.h"

class Matrix
{
private:
    Fraction **m_matrix{nullptr};

    const char variableList[4]{'x', 'y', 'z', 'w'};

    const int m_column{0};
    const int m_equationLength{0};

    void PrintAnswer(std::ostream &cout);

public:
    // Constructor
    Matrix(int numberOfDifferentUnknowns = 1, int column = 1);

    void FillEquation(int column);

    // Destructor
    ~Matrix();

    Fraction GetMatrix(int column, int row) const;

    void Solve();

    void PrintMatrix();

    // Multiplies the whole equation with a number c.
    void MultiplyByC(Fraction c, int column);

    void DivideByC(Fraction c, int column);

    // Swaps the placement of two equations in the matrix.
    void SwapEquations(int firstColumn, int secondColumn);

    // Adds an equation by a c amount to the resultEquation.
    void AddByEquation(int resultEquation, Fraction c, int addEquation);

    int GetColomsAmount() const;
    int GetEquationLength() const;
    void ExtractionIntoEquation(std::stringstream &stringStrm, int column, int row, char delimChar);
};

#endif // MATRIX_H
