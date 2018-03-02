#include "matrix.h"
#include <sstream>
#include <vector>

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
    std::cout << "Enter " << column + 1 << ". equation: ";

    std::string inputEquation{};
    std::cin >> inputEquation;
    std::stringstream stringStrm{inputEquation};
    for (int i{0}; i < inputEquation.size(); ++i) {
        for (int p{0}; p < GetEquationLength(); ++p) {
            if (inputEquation.at(i) == variableList[p]) {
                std::string temp{};
                std::getline(stringStrm, temp, variableList[p]);
                std::stringstream intPusher{temp};
                int number{};
                intPusher >> number;
                m_matrix[column][p] = Fraction{number};
            }
        }
    }
    // Push the rest into answer:
    std::string temp{};
    stringStrm.ignore(10, '=');
    std::getline(stringStrm, temp, '\0');
    int number{};
    std::stringstream intPusher{temp};
    intPusher >> number;
    m_matrix[column][GetEquationLength()] = Fraction{number};

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

    // PrintAnswer(std::cout);
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

int Matrix::GetColomsAmount() const
{
    return m_column;
}

int Matrix::GetEquationLength() const
{
    return m_equationLength - 1;
}

void Matrix::PrintAnswer(std::ostream &cout)
{
    // Print first part of answer.
    cout << "(";
    for (int i{0}; i < GetEquationLength(); ++i) {
        cout << variableList[i];
        if (i + 1 != GetEquationLength()) {
            cout << ",";
        } else {
            cout << ") = (";
        }
    }


}

