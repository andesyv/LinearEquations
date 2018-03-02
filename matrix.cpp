#include "matrix.h"

Matrix::Matrix(int numberOfDifferentUnknowns, int column) : m_column{column}, m_equationLength{numberOfDifferentUnknowns + 1} {
    m_matrix = new Fraction*[m_column];
    for (int i{0}; i < m_column; ++i) {
        m_matrix[i] = new Fraction[m_equationLength];
    }
    std::cout << "colums is: " << m_column << "\nlength of equation is: " << m_equationLength << "\n";
}

void Matrix::FillWithNumbers() {
    for (int y{0}; y < m_column; ++y) {
        for (int x{0}; x < m_equationLength; ++x) {
            m_matrix[y][x] = static_cast<Fraction>(Increaser());
        }
    }
}

void Matrix::FillEquation(int column)
{
    std::cout << "Enter equation: ";
    const std::string names[4]{"x: ", "y: ", "z: ", "Answer: "};
    for (int row{0}; row < m_equationLength; ++row) {
        std::cout << "\n" << names[row];
        int in{};
        std::cin >> in;
        m_matrix[column][row] = Fraction{in};
    }
    std::cout << "\n";
}

Matrix::~Matrix() {
    for (int i{0}; i < m_column; ++i) {
        delete[] m_matrix[i];
    }
    delete[] m_matrix;
}

Fraction Matrix::GetMatrix(int column, int row) const {
    if (column >= 0 && column < m_column && row >= 0 && row < m_equationLength) {
        return m_matrix[column][row];
    } else {
        return Fraction{};
    }
}

void Matrix::Solve() {
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

    PrintAnswer();
}

void Matrix::PrintMatrix() {
    for (int y{0}; y < m_column; ++y) {
        std::cout << "(";
        for (int x{0}; x < m_equationLength; ++x) {
            std::cout << m_matrix[y][x];
            (x + 1 != m_equationLength) ? std::cout << ", " : std::cout << ")";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Matrix::MultiplyByC(Fraction c, int column) {
    if (c != 0) {
        for (int i{0}; i < m_equationLength; ++i) {
            m_matrix[column][i] *= c;
        }
    }
}

void Matrix::DivideByC(Fraction c, int column) {
    if (c != 0) {
        for (int i{0}; i < m_equationLength; ++i) {
            m_matrix[column][i] /= c;
        }
    }
}

void Matrix::SwapEquations(int firstColumn, int secondColumn) {
    Fraction *temp = m_matrix[firstColumn];
    m_matrix[firstColumn] = m_matrix[secondColumn];
    m_matrix[secondColumn] = temp;
    temp = nullptr;
}

void Matrix::AddByEquation(int resultEquation, Fraction c, int addEquation) {
    for (int i{0}; i < m_equationLength; ++i) {
        m_matrix[resultEquation][i] += c * GetMatrix(addEquation, i);
    }
}

int Matrix::NumberOfColoms() const
{
    return m_column;
}

int Matrix::LengthOfEquation() const
{
    return m_equationLength - 1;
}

void Matrix::PrintAnswer()
{

}

