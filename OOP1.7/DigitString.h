
#pragma once
#include <string>

using namespace std;

class DigitString
{
private:
    string digits;

public:

    DigitString();
    DigitString(string value);

    // Методи доступу
    string GetDigits() const;
    bool SetDigits(string value);

    // Обов'язкові методи
    bool Init(string value);
    void Read();
    void Display() const;
    string toString() const;

    // Арифметичні оператори
    DigitString operator+ (const DigitString& other) const;
    DigitString operator- (const DigitString& other) const;
    DigitString operator* (const DigitString& other) const;
    DigitString operator/ (const DigitString& other) const;
    DigitString operator% (const DigitString& other) const;

    DigitString& operator++();
    DigitString operator++(int);

    DigitString& operator--();
    DigitString operator--(int);

    // Унарні оператори
    DigitString operator+ () const;
    DigitString operator- () const;

    // Оператори порівняння
    bool operator== (const DigitString& other) const;
    bool operator!= (const DigitString& other) const;
    bool operator< (const DigitString& other) const;
    bool operator> (const DigitString& other) const;
    bool operator<= (const DigitString& other) const;
    bool operator>= (const DigitString& other) const;
};
