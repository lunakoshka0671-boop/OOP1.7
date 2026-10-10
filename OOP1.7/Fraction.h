
#pragma once
#include "DigitString.h"

class Fraction
{
private:
    DigitString integerPart;
    unsigned short fractionalPart;
    bool negative;

public:
    // Конструктори
    Fraction();
    Fraction(string integer, unsigned short fraction);
    Fraction(string integer, unsigned short fraction, bool sign);

    // Методи доступу
    DigitString GetIntegerPart() const;
    unsigned short GetFractionalPart() const;
    bool GetNegative() const;

    bool SetIntegerPart(DigitString value);
    bool SetFractionalPart(unsigned short value);
    bool SetNegative(bool value);

    // Обов'язкові методи
    bool Init(string integer, unsigned short fraction, bool sign);
    void Read();
    void Display() const;
    string toString() const;

    // Арифметичні оператори
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;

    // Оператори порівняння
    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;
};

