//Deejuanae Lewis
/*
  rec07_begin.cpp
  CS2124
  Implement the class Rational, so that the following program works.
 */

#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);

// Put your Rational class here.
class Rational {
    friend istream& operator>>(istream& is, Rational& obj);
    friend ostream& operator<<(ostream& os, const Rational& obj);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);

public:
    Rational(int numerator = 0, int denominator = 1): numerator(numerator),
    denominator(denominator) {
        normalize();
    }

    void normalize();
    Rational& operator+=(const Rational& rhs);
    Rational& operator++();
    Rational operator++(int i);
    explicit operator bool() const {
        return numerator != 0;
    }

private:
    int numerator;
    int denominator;
};

//friends
istream& operator>>(istream& is, Rational& obj) {
    char slash;
    is >> obj.numerator >> slash >> obj.denominator;
    obj.normalize();
    return is;
}

ostream& operator<<(ostream& os, const Rational& obj) {
    os << obj.numerator << '/' << obj.denominator;
    return os;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    if((lhs.numerator == rhs.numerator) && (lhs.denominator == rhs.denominator)) {
        return true;
    }
    return false;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    if(lhs.numerator * rhs.denominator < rhs.numerator * lhs.denominator) {
        return true;
    }
    return false;
}

//Member functions
void Rational::normalize() {
    int gcd = greatestCommonDivisor(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;

    if((numerator < 0 && denominator < 0) || denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
}

Rational& Rational::operator+=(const Rational& rhs) {
    numerator = numerator * rhs.denominator + rhs.numerator * denominator;
    denominator = denominator * rhs.denominator;
    normalize();
    return *this;
}

Rational& Rational::operator++() {
    *this += 1;
    return *this;
}

Rational Rational::operator++(int i) {
    Rational temp(*this);
    *this += 1;
    return temp;
}

// Any functions that are not members and not friends should have
// prototypes here and their definitions after main.
Rational operator+(const Rational& lhs, const Rational& rhs);
Rational& operator--(Rational& obj);
Rational operator--(Rational& obj, int i);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);

int main()
{
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    
    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing? Why shouldn't it compile?
    //cout << "a-- -- = " << (a-- --) << endl;
   // cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : "
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}

int greatestCommonDivisor(int x, int y)
{
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

// Any functions that are not members and not friends should have
// their definitions here...

Rational operator+(const Rational& lhs, const Rational& rhs){
    Rational newRational;
    newRational += lhs;
    newRational += rhs;
    return newRational;
}

Rational& operator--(Rational& obj){
    obj += -1;
    return obj;
}

Rational operator--(Rational& obj, int i) {
    Rational temp(obj);
    obj += -1;
    return temp;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

bool operator>(const Rational& lhs, const Rational& rhs) {
 return !(lhs<=rhs);
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return ((lhs < rhs) || (lhs == rhs));
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return (!(lhs < rhs));
}
