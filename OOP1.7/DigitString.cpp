
#include "DigitString.h"
#include <iostream>
#include <stdexcept>

using namespace std;

namespace
{
    // Перевірка правильності запису числа
    bool IsValid(const string& s)
    {
        if (s.empty())
            return false;

        size_t start = (s[0] == '-') ? 1 : 0;

        if (start == s.size())
            return false;

        for (size_t i = start; i < s.size(); i++)
        {
            if (s[i] < '0' || s[i] > '9')
                return false;
        }

        return true;
    }

    // Видалення зайвих нулів на початку
    string Normalize(string s)
    {
        bool negative = (s[0] == '-');
        size_t start = negative ? 1 : 0;

        while (start + 1 < s.size() && s[start] == '0')
            start++;

        string result = s.substr(start);

        if (result == "0")
            return "0";

        return negative ? "-" + result : result;
    }

    bool IsNegative(const string& s)
    {
        return !s.empty() && s[0] == '-';
    }

    string AbsString(const string& s)
    {
        return IsNegative(s) ? s.substr(1) : s;
    }

    // Порівняння модулів невід'ємних чисел
    int CompareAbs(const string& a, const string& b)
    {
        if (a.size() > b.size()) return 1;
        if (a.size() < b.size()) return -1;

        if (a > b) return 1;
        if (a < b) return -1;

        return 0;
    }

    // Додавання невід'ємних чисел
    string AddAbs(const string& a, const string& b)
    {
        string result;
        int i = (int)a.size() - 1;
        int j = (int)b.size() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry)
        {
            int sum = carry;

            if (i >= 0) sum += a[i--] - '0';
            if (j >= 0) sum += b[j--] - '0';

            result.push_back(char('0' + sum % 10));
            carry = sum / 10;
        }

        reverse(result.begin(), result.end());
        return result;
    }

    // Віднімання модулів, коли a >= b
    string SubAbs(const string& a, const string& b)
    {
        string result;
        int i = (int)a.size() - 1;
        int j = (int)b.size() - 1;
        int borrow = 0;

        while (i >= 0)
        {
            int digit = a[i--] - '0' - borrow;
            int sub = (j >= 0) ? b[j--] - '0' : 0;

            if (digit < sub)
            {
                digit += 10;
                borrow = 1;
            }
            else
                borrow = 0;

            result.push_back(char('0' + digit - sub));
        }

        reverse(result.begin(), result.end());
        return Normalize(result);
    }

    // Множення невід'ємних чисел
    string MulAbs(const string& a, const string& b)
    {
        if (a == "0" || b == "0")
            return "0";

        string result(a.size() + b.size(), '0');

        for (int i = (int)a.size() - 1; i >= 0; i--)
        {
            for (int j = (int)b.size() - 1; j >= 0; j--)
            {
                int product = (a[i] - '0') * (b[j] - '0');
                int sum = product + (result[i + j + 1] - '0');

                result[i + j + 1] = char('0' + sum % 10);
                result[i + j] += sum / 10;
            }
        }

        return Normalize(result);
    }

    // Ділення невід'ємних чисел
    string DivAbs(const string& a, const string& b)
    {
        if (b == "0")
            throw domain_error("Division by zero");

        string quotient;
        string remainder = "0";

        for (char digit : a)
        {
            if (remainder == "0")
                remainder = string(1, digit);
            else
                remainder += digit;

            remainder = Normalize(remainder);

            int q = 0;

            while (CompareAbs(remainder, b) >= 0)
            {
                remainder = SubAbs(remainder, b);
                q++;
            }

            quotient.push_back(char('0' + q));
        }

        return Normalize(quotient);
    }

    // Додавання зі знаками
    string AddSigned(const string& a, const string& b)
    {
        bool na = IsNegative(a);
        bool nb = IsNegative(b);

        string aa = AbsString(a);
        string bb = AbsString(b);

        if (na == nb)
        {
            string result = AddAbs(aa, bb);
            return na && result != "0" ? "-" + result : result;
        }

        int cmp = CompareAbs(aa, bb);

        if (cmp == 0)
            return "0";

        string result;
        bool negative;

        if (cmp > 0)
        {
            result = SubAbs(aa, bb);
            negative = na;
        }
        else
        {
            result = SubAbs(bb, aa);
            negative = nb;
        }

        return negative && result != "0" ? "-" + result : result;
    }

    // Порівняння цілих чисел зі знаками
    int CompareSigned(const string& a, const string& b)
    {
        bool na = IsNegative(a);
        bool nb = IsNegative(b);

        if (na && !nb) return -1;
        if (!na && nb) return 1;

        int cmp = CompareAbs(AbsString(a), AbsString(b));

        return na ? -cmp : cmp;
    }
}

// Конструктори
DigitString::DigitString()
{
    digits = "0";
}

DigitString::DigitString(string value)
{
    digits = "0";
    SetDigits(value);
}

// Методи доступу
string DigitString::GetDigits() const
{
    return digits;
}

bool DigitString::SetDigits(string value)
{
    if (!IsValid(value))
    {
        digits = "0";
        return false;
    }

    digits = Normalize(value);
    return true;
}

// Ініціалізація
bool DigitString::Init(string value)
{
    return SetDigits(value);
}

// Введення
void DigitString::Read()
{
    string value;

    do
    {
        cout << "Input an integer: ";
        cin >> value;
    } while (!Init(value));
}

// Виведення
void DigitString::Display() const
{
    cout << toString();
}

// Перетворення до рядка
string DigitString::toString() const
{
    return digits;
}

// Додавання
DigitString DigitString::operator+(const DigitString& other) const
{
    return DigitString(AddSigned(digits, other.digits));
}

// Віднімання
DigitString DigitString::operator-(const DigitString& other) const
{
    string b = other.digits;

    if (b != "0")
        b = IsNegative(b) ? AbsString(b) : "-" + b;

    return DigitString(AddSigned(digits, b));
}

// Множення
DigitString DigitString::operator*(const DigitString& other) const
{
    string result = MulAbs(
        AbsString(digits), AbsString(other.digits));

    if (IsNegative(digits) != IsNegative(other.digits)
        && result != "0")
        result = "-" + result;

    return DigitString(result);
}

// Ділення націло
DigitString DigitString::operator/(const DigitString& other) const
{
    string result = DivAbs(
        AbsString(digits), AbsString(other.digits));

    if (IsNegative(digits) != IsNegative(other.digits)
        && result != "0")
        result = "-" + result;

    return DigitString(result);
}

// Остача від ділення
DigitString DigitString::operator%(const DigitString& other) const
{
    string a = AbsString(digits);
    string b = AbsString(other.digits);

    string quotient = DivAbs(a, b);
    string product = MulAbs(quotient, b);
    string result = SubAbs(a, product);

    if (IsNegative(digits) && result != "0")
        result = "-" + result;

    return DigitString(result);
}

// Унарний плюс
DigitString DigitString::operator+() const
{
    return *this;
}

// Унарний мінус
DigitString DigitString::operator-() const
{
    if (digits == "0")
        return DigitString("0");

    return DigitString(IsNegative(digits)
        ? AbsString(digits) : "-" + digits);
}

// Порівняння
bool DigitString::operator==(const DigitString& other) const
{
    return digits == other.digits;
}

bool DigitString::operator!=(const DigitString& other) const
{
    return !(*this == other);
}

bool DigitString::operator<(const DigitString& other) const
{
    return CompareSigned(digits, other.digits) < 0;
}

bool DigitString::operator>(const DigitString& other) const
{
    return other < *this;
}

bool DigitString::operator<=(const DigitString& other) const
{
    return !(*this > other);
}

bool DigitString::operator>=(const DigitString& other) const
{
    return !(*this < other);
}

DigitString& DigitString::operator++()
{
    *this = *this + DigitString("1");
    return *this;
}

DigitString DigitString::operator++(int)
{
    DigitString temp = *this;
    ++(*this);
    return temp;
}

DigitString& DigitString::operator--()
{
    *this = *this - DigitString("1");
    return *this;
}

DigitString DigitString::operator--(int)
{
    DigitString temp = *this;
    --(*this);
    return temp;
}