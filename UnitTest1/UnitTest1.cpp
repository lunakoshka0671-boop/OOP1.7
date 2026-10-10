
#include "pch.h"
#include "CppUnitTest.h"
#include "../OOP1.7/DigitString.cpp"
#include "../OOP1.7/Fraction.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Variant25Tests
{
    TEST_CLASS(Variant25Test)
    {
    public:

        // Тести DigitString

        TEST_METHOD(TestDigitStringInit)
        {
            DigitString a;

            Assert::IsTrue(a.Init("12345"));
            Assert::AreEqual(string("12345"), a.toString());

            Assert::IsFalse(a.Init("12a"));
            Assert::AreEqual(string("0"), a.toString());
        }

        TEST_METHOD(TestDigitStringArithmetic)
        {
            DigitString a("25");
            DigitString b("10");

            Assert::AreEqual(string("35"), (a + b).toString());
            Assert::AreEqual(string("15"), (a - b).toString());
            Assert::AreEqual(string("250"), (a * b).toString());
            Assert::AreEqual(string("2"), (a / b).toString());
            Assert::AreEqual(string("5"), (a % b).toString());
        }

        TEST_METHOD(TestDigitStringComparison)
        {
            DigitString a("100");
            DigitString b("20");

            Assert::IsTrue(a > b);
            Assert::IsTrue(b < a);
            Assert::IsTrue(a != b);
            Assert::IsTrue(a == DigitString("100"));
        }

        // Тести Fraction

        TEST_METHOD(TestFractionInitAndFormat)
        {
            Fraction a("12", 5);

            Assert::AreEqual(string("12.05"), a.toString());

            Fraction b;
            Assert::IsTrue(b.Init("3", 50, false));
            Assert::AreEqual(string("3.50"), b.toString());
        }

        TEST_METHOD(TestFractionAddition)
        {
            Fraction a("1", 75);
            Fraction b("0", 50);

            Assert::AreEqual(string("2.25"), (a + b).toString());
        }

        TEST_METHOD(TestFractionSubtraction)
        {
            Fraction a("1", 25);
            Fraction b("2", 50);

            Assert::AreEqual(string("-1.25"), (a - b).toString());
        }

        TEST_METHOD(TestFractionMultiplication)
        {
            Fraction a("2", 50);
            Fraction b("2", 00);

            Assert::AreEqual(string("5.00"), (a * b).toString());
        }

        TEST_METHOD(TestFractionComparison)
        {
            Fraction a("3", 50);
            Fraction b("2", 75);

            Assert::IsTrue(a > b);
            Assert::IsTrue(b < a);
            Assert::IsTrue(a != b);
            Assert::IsTrue(a == Fraction("3", 50));
        }
    };
}
