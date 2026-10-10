
#include "Fraction.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace
{
    // Перетворення Fraction на ціле число сотих
    DigitString ToScaled(const Fraction& value)
    {
        DigitString hundred("100");
        DigitString result =
            value.GetIntegerPart() * hundred +
            DigitString(to_string(value.GetFractionalPart()));

        if (value.GetNegative() && result != DigitString("0"))
            result = -result;

        return result;
    }

    // Перетворення цілих сотих на Fraction
    Fraction FromScaled(DigitString value)
    {
        bool negative = value < DigitString("0");

        if (negative)
            value = -value;

        DigitString integer = value / DigitString("100");
        DigitString fraction = value % DigitString("100");

        unsigned short fractionalPart =
            static_cast<unsigned short>(stoi(fraction.toString()));

        Fraction result;
        result.Init(integer.toString(), fractionalPart, negative);
        return result;
    }
}

// Конструктори
Fraction::Fraction()
    : integerPart("0"), fractionalPart(0), negative(false)
{
}

Fraction::Fraction(string integer, unsigned short fraction)
    : integerPart("0"), fractionalPart(0), negative(false)
{
    Init(integer, fraction, false);
}

Fraction::Fraction(string integer, unsigned short fraction, bool sign)
    : integerPart("0"), fractionalPart(0), negative(false)
{
    Init(integer, fraction, sign);
}

// Методи доступу
DigitString Fraction::GetIntegerPart() const
{
    return integerPart;
}

unsigned short Fraction::GetFractionalPart() const
{
    return fractionalPart;
}

bool Fraction::GetNegative() const
{
    return negative;
}

bool Fraction::SetIntegerPart(DigitString value)
{
    if (value < DigitString("0"))
    {
        integerPart = DigitString("0");
        return false;
    }

    integerPart = value;
    return true;
}

bool Fraction::SetFractionalPart(unsigned short value)
{
    if (value > 99)
    {
        fractionalPart = 0;
        return false;
    }

    fractionalPart = value;
    return true;
}

bool Fraction::SetNegative(bool value)
{
    negative = value;

    if (integerPart == DigitString("0") &&
        fractionalPart == 0)
        negative = false;

    return true;
}

// Ініціалізація
bool Fraction::Init(string integer, unsigned short fraction, bool sign)
{
    return SetIntegerPart(integer)
        && SetFractionalPart(fraction)
        && SetNegative(sign);
}

// Введення з клавіатури
void Fraction::Read()
{
    string integer;
    unsigned int fraction;
    char separator;
    bool sign;

    do
    {
        cout << "Input a number (example: -12.45): ";
        cin >> integer;

        size_t pos = integer.find('.');

        if (pos == string::npos)
        {
            cout << "Use a decimal point, for example 12.45.\n";
            continue;
        }

        string fractionalString = integer.substr(pos + 1);
        string integerString = integer.substr(0, pos);

        if (fractionalString.empty() ||
            fractionalString.size() > 2)
        {
            cout << "Use one or two decimal digits.\n";
            continue;
        }

        if (fractionalString.size() == 1)
            fractionalString += "0";

        try
        {
            fraction = static_cast<unsigned int>(
                stoi(fractionalString));
        }
        catch (...)
        {
            cout << "Invalid fractional part.\n";
            continue;
        }

        sign = !integerString.empty() &&
            integerString[0] == '-';

        if (sign)
            integerString = integerString.substr(1);

        DigitString temp;

        if (!temp.Init(integerString))
        {
            cout << "Invalid integer part.\n";
            continue;
        }

        if (Init(integerString,
            static_cast<unsigned short>(fraction), sign))
            return;

        cout << "Invalid value. Try again.\n";

    } while (true);
}

// Виведення
void Fraction::Display() const
{
    cout << toString();
}

// Перетворення до рядка
string Fraction::toString() const
{
    stringstream sout;

    if (negative)
        sout << '-';

    sout << integerPart.toString()
        << '.'
        << setw(2) << setfill('0')
        << fractionalPart;

    return sout.str();
}

// Додавання
Fraction Fraction::operator+(const Fraction& other) const
{
    return FromScaled(ToScaled(*this) + ToScaled(other));
}

// Віднімання
Fraction Fraction::operator-(const Fraction& other) const
{
    return FromScaled(ToScaled(*this) - ToScaled(other));
}

// Множення з точністю до сотих
Fraction Fraction::operator*(const Fraction& other) const
{
    DigitString product = ToScaled(*this) * ToScaled(other);
    DigitString result = product / DigitString("100");

    return FromScaled(result);
}

// Порівняння
bool Fraction::operator==(const Fraction& other) const
{
    return ToScaled(*this) == ToScaled(other);
}

bool Fraction::operator!=(const Fraction& other) const
{
    return !(*this == other);
}

bool Fraction::operator<(const Fraction& other) const
{
    return ToScaled(*this) < ToScaled(other);
}

bool Fraction::operator>(const Fraction& other) const
{
    return other < *this;
}

bool Fraction::operator<=(const Fraction& other) const
{
    return !(*this > other);
}

bool Fraction::operator>=(const Fraction& other) const
{
    return !(*this < other);
}
