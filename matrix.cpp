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

void Matrix::ExtractionIntoEquation(std::stringstream &stringStrm, int column, int row, char delimChar)
{
    std::string temp{};
    std::getline(stringStrm, temp, delimChar);
    std::stringstream intPusher{temp};
    int number{};
    intPusher >> number;
    m_matrix[column][row] = Fraction{number};
}

void Matrix::FillEquation(int column)
{
    std::cout << "Enter " << column + 1 << ". equation: ";
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(24000, '\n');
    }
    // std::cin.ignore(24000, '\n');

    std::string inputEquation{};
    std::getline(std::cin, inputEquation, '\n');
    std::stringstream stringStrm{inputEquation};
    for (int i{0}; i < static_cast<int>(inputEquation.size()); ++i) {
        for (int p{0}; p < GetEquationLength(); ++p) {
            if (inputEquation.at(i) == variableList[p]) {
                ExtractionIntoEquation(stringStrm, column, p, variableList[p]);
                if (GetMatrix(column, p) == 0) {
                    m_matrix[column][p] = Fraction{1};
                }
            }
        }
    }
    stringStrm.ignore(24000, '=');

    // Push the rest into answer:
    ExtractionIntoEquation(stringStrm, column, GetEquationLength(), '\0');

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

        // Make 0 not be in the first column.
        for (int y{columnIndex + 1}; y < m_column; ++y) {
            if (GetMatrix(columnIndex, row) == 0) {
                SwapEquations(columnIndex, y);
                PrintMatrix();
            } else {
                break;
            }
        }

        // If it's still 0, skip to the next row on the same Index.
        if (GetMatrix(columnIndex, row) == 0) {
            continue;
        }

        // Make the first number be 1;
        DivideByC(GetMatrix(columnIndex, row), columnIndex);
        PrintMatrix();

        // For every other column, make them 0.
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
    //TODO: Finish this function.

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

