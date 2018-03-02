#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <limits>

// Forward declarations
class Fraction;

Fraction operator* (int value, const Fraction &frac);
Fraction operator/ (int value, const Fraction &frac);
Fraction operator+ (int value, const Fraction &frac);
Fraction operator- (int value, const Fraction &frac);


class Fraction
{
private:
    int m_numerator{0};
    int m_denominator{1};

    int gcd(int a, int b) {
        return (b == 0) ? (a > 0 ? a : -a) : gcd(b, a % b);
    }

    void reduce();
    void evenNegatives();
public:
    Fraction (int numerator = 0, int denominator = 1);

    float ToFloat();
    explicit operator float() const {
        return static_cast<float>(m_numerator) / static_cast<float>(m_denominator);
    }

    Fraction operator* (const Fraction &frac);
    Fraction operator/ (const Fraction &frac);
    Fraction operator+ (const Fraction &frac);
    Fraction operator- (const Fraction &frac);
    Fraction &operator*= (const Fraction &frac);
    Fraction &operator/= (const Fraction &frac);
    Fraction &operator+= (const Fraction &frac);
    Fraction &operator-= (const Fraction &frac);

    bool operator== (int value);
    bool operator!= (int value);
    Fraction operator- ();

    void print();

    // friend std::ostream& operator<< (std::ostream &stream, const Fraction &frac);

    friend std::ostream& operator<< (std::ostream &stream, const Fraction &frac) {
        if (frac.m_denominator == 0) {
            stream << std::numeric_limits<float>::quiet_NaN();
        } else if (frac.m_numerator == 0) {
            stream << 0;
        } else if (frac.m_denominator == 1) {
            stream << frac.m_numerator;
        } else {
            stream << "(" << frac.m_numerator << "/" << frac.m_denominator << ")";
        }
        return stream;
    }
};

#endif // FRACTION_H
