#include "fraction.h"

Fraction::Fraction(int numerator, int denominator) : m_numerator{numerator}, m_denominator{denominator}
{
    reduce();
}

Fraction::Fraction(Fraction numerator, Fraction denominator)
{
    Fraction result{numerator / denominator};
    m_numerator = result.m_numerator;
    m_denominator = result.m_denominator;

    reduce();
}

void Fraction::reduce() {
    int division{gcd(m_numerator, m_denominator)};
    m_numerator /= division;
    m_denominator /= division;

    evenNegatives();
}

void Fraction::evenNegatives()
{
    if (m_denominator < 0) {
        m_numerator *= -1;
        m_denominator *= -1;
    }
}

float Fraction::ToFloat() {
    return static_cast<float>(m_numerator) / static_cast<float>(m_denominator);
}

Fraction Fraction::operator* (const Fraction &frac) {
    Fraction newFrac{m_numerator * frac.m_numerator, m_denominator * frac.m_denominator};
    newFrac.reduce();
    return newFrac;
}

Fraction Fraction::operator/ (const Fraction &frac) {
    Fraction newFrac{m_numerator * frac.m_denominator, m_denominator * frac.m_numerator};
    newFrac.reduce();
    return newFrac;
}
Fraction Fraction::operator+(const Fraction &frac)
{
    Fraction newFrac{m_numerator * frac.m_denominator + frac.m_numerator * m_denominator, m_denominator * frac.m_denominator};
    newFrac.reduce();
    return newFrac;
}

Fraction Fraction::operator-(const Fraction &frac)
{
    Fraction newFrac{m_numerator * frac.m_denominator - frac.m_numerator * m_denominator, m_denominator * frac.m_denominator};
    newFrac.reduce();
    return newFrac;
}

Fraction &Fraction::operator*=(const Fraction &frac)
{
    *this = *this * frac;
    return *this;
}

Fraction &Fraction::operator/=(const Fraction &frac)
{
    *this = *this / frac;
    return *this;
}

Fraction &Fraction::operator+=(const Fraction &frac)
{
    *this = *this + frac;
    return *this;
}

Fraction &Fraction::operator-=(const Fraction &frac)
{
    *this = *this - frac;
    return *this;
}

bool Fraction::operator==(int value)
{
    if (m_numerator == 0 || m_denominator == 1) {
        return m_numerator == value;
    } else {
        return false;
    }
}

bool Fraction::operator!=(int value)
{
    return !(*this == value);
}

Fraction Fraction::operator-()
{
    return Fraction{-m_numerator, m_denominator};
}

Fraction operator* (int value, const Fraction &frac) {
    std::cout << "int * Fraction called!\n";
    return Fraction{value} * frac;
}

Fraction operator/ (int value, const Fraction &frac) {
    return Fraction{value} / frac;
}

Fraction operator+ (int value, const Fraction &frac) {
    return Fraction{value} + frac;
}

Fraction operator- (int value, const Fraction &frac) {
    return Fraction{value} - frac;
}

void Fraction::print() {
    if (m_denominator == 0) {
        std::cout << std::numeric_limits<float>::infinity() << "\n";
    } else {
        std::cout << "(" << m_numerator << "/" << m_denominator << ")\n";
    }
}
