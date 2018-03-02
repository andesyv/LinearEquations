#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "fraction.h"

class Matrix
{
private:
    Fraction **m_matrix{nullptr};

    const int m_column{0};
    const int m_equationLength{0};

    int Increaser() {
        static int increase{5};
        return ++increase;
    }

public:
    // Constructor
    Matrix(int numberOfDifferentUnknowns, int column);

    void FillWithNumbers();

    // Destructor
    ~Matrix();

    Fraction GetMatrix(int column, int row) const;

    void Solve() {
        FillWithNumbers();
        PrintMatrix();

        int columnIndex{0};
        for (int row{0}; row < m_equationLength - 1; ++row) {
            // First column
            // Make 0 not be in the first column.
            for (int y{columnIndex + 1}; y < m_column; ++y) {
                if (GetMatrix(columnIndex, row) == 0) {
                    SwapEquations(columnIndex, y);
                    PrintMatrix();
                } else {
                    break;
                }
            }
            PrintMatrix();
            // If it's still 1, skip to the next row on the same Index.
            if (GetMatrix(columnIndex, row) == 0) {
                continue;
            }

            // Make the first number be 1;
            DivideByC(GetMatrix(columnIndex, row), columnIndex);
            PrintMatrix();

            // For every other row, remove x's.
            for (int y{0}; y < m_column; ++y) {
                if (columnIndex == y) {
                    continue;
                } else {
                    AddByEquation(y, -GetMatrix(y, row), columnIndex);
                    PrintMatrix();
                }
            }
            ++columnIndex;
        }
    }

    void PrintMatrix();

    // Multiplies the whole equation with a number c.
    void MultiplyByC(Fraction c, int column);

    void DivideByC(Fraction c, int column);

    // Swaps the placement of two equations in the matrix.
    void SwapEquations(int firstColumn, int secondColumn);

    // Adds an equation by a c amount to the resultEquation.
    void AddByEquation(int resultEquation, Fraction c, int addEquation);
};

#endif // MATRIX_H
