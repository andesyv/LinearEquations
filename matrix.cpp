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

