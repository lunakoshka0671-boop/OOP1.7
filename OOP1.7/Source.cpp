
#include <iostream>
#include "DigitString.h"
#include "Fraction.h"

using namespace std;

int main()
{
    cout << "===== DigitString =====" << endl;

    // Різні способи створення об'єктів
    DigitString a;
    DigitString b("125");
    DigitString c("-25");

    // Ініціалізація
    a.Init("100");

    // Методи доступу
    cout << "a = " << a.toString() << endl;
    cout << "b = " << b.GetDigits() << endl;

    // Методи введення та виведення
    DigitString d;
    d.Read();
    d.Display();

    // Арифметичні оператори
    cout << "a + b = " << (a + b).toString() << endl;
    cout << "a - b = " << (a - b).toString() << endl;
    cout << "a * b = " << (a * b).toString() << endl;
    cout << "a / b = " << (a / b).toString() << endl;
    cout << "a % b = " << (a % b).toString() << endl;

    // Унарні оператори
    cout << "+c = " << (+c).toString() << endl;
    cout << "-b = " << (-b).toString() << endl;

    // Інкремент і декремент
    DigitString e("5");
    cout << "e = " << e.toString() << endl;
    cout << "e++ = " << (e++).toString() << endl;
    cout << "After e++: " << e.toString() << endl;
    cout << "++e = " << (++e).toString() << endl;
    cout << "e-- = " << (e--).toString() << endl;
    cout << "--e = " << (--e).toString() << endl;

    // Оператори порівняння
    cout << boolalpha;
    cout << "a == b: " << (a == b) << endl;
    cout << "a != b: " << (a != b) << endl;
    cout << "a > b: " << (a > b) << endl;
    cout << "a < b: " << (a < b) << endl;
    cout << "a >= b: " << (a >= b) << endl;
    cout << "a <= b: " << (a <= b) << endl;

    // Масив об'єктів
    DigitString arr[3] = {
        DigitString("10"),
        DigitString("20"),
        DigitString("30")
    };

    cout << "\nMassive DigitString:" << endl;
    for (int i = 0; i < 3; i++)
        arr[i].Display();


    cout << "\n===== Fraction =====" << endl;

    // Різні способи створення об'єктів
    Fraction f1;
    Fraction f2("12", 50);
    Fraction f3("2", 25, true);

    f1.Init("3", 75, false);

    cout << "f1 = " << f1.toString() << endl;
    cout << "f2 = " << f2.toString() << endl;
    cout << "f3 = " << f3.toString() << endl;

    // Методи доступу
    cout << "Integer part f2: "
        << f2.GetIntegerPart().toString() << endl;

    cout << "Fractional part f2: "
        << f2.GetFractionalPart() << endl;

    cout << "Negative: "
        << f3.GetNegative() << endl;

    // Методи введення та виведення
    Fraction f4;
    f4.Read();
    f4.Display();

    // Арифметичні оператори
    cout << "f1 + f2 = " << (f1 + f2).toString() << endl;
    cout << "f1 - f2 = " << (f1 - f2).toString() << endl;
    cout << "f1 * f2 = " << (f1 * f2).toString() << endl;

    // Оператори порівняння
    cout << "f1 == f2: " << (f1 == f2) << endl;
    cout << "f1 != f2: " << (f1 != f2) << endl;
    cout << "f1 > f2: " << (f1 > f2) << endl;
    cout << "f1 < f2: " << (f1 < f2) << endl;
    cout << "f1 >= f2: " << (f1 >= f2) << endl;
    cout << "f1 <= f2: " << (f1 <= f2) << endl;

    // Масив об'єктів
    Fraction fractions[3] = {
        Fraction("1", 25),
        Fraction("2", 50),
        Fraction("3", 75)
    };

    cout << "\nMassive Fraction:" << endl;
    for (int i = 0; i < 3; i++)
        fractions[i].Display();

    return 0;
}

