//Deejuanae Lewis
/*
  The purpose of this program is to implement a class that handles big unsigned
  integers. For the class a selection of operators are overloaded.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Put your class and all function definitions here.
//A class that is meant to represent big unsigned integers. An object can be
//intialized using an integer or a string and the digits are stored in a vector.
class BigUnsigned {
    friend ostream& operator<<(ostream& os, const BigUnsigned& obj);
    friend bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs);
    friend bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs);

public:
    //Contructors
    BigUnsigned(int value = 0);
    BigUnsigned(const string& s);

    //getters
    size_t getLength() const { return digits.size(); }
    int getDigit(size_t index) const;

    //overloaded operators
    BigUnsigned& operator+=(const BigUnsigned& rhs);
    BigUnsigned& operator++();
    BigUnsigned operator++(int);

    //Conversion operator to bool
    //Return Type: bool - true if the number is not zero else false
    explicit operator bool() const {
        return (getLength() != 0) && !(digits[0] == 0);
    }

private:
    void parseDigits(int value);
    vector<int> digits;
};

//Constructor that initializes BigUnsigned from an integer
//Parameters: string - the integer to initialize from
BigUnsigned::BigUnsigned(int value) {
    if (value == 0) {
        digits.push_back(0);
    }
    else {
        parseDigits(value);
    }
}

//Constructor that initializes BigUnsigned from a string
//Parameters: string - the string to initialize from
BigUnsigned::BigUnsigned(const string& s) {
    //checks if string is empty or the first value is a letter
    if (s.empty() || !(s[0] >= '0' && s[0] <= '9')) {
        digits.push_back(0);
        return;
    }
    //ignores all the leading zeros
    size_t i = 0;
    while (i < s.length() && s[i] == '0') {
        i++;
    }
    //stores all the digits in the vector
    int value = 0;
    while (s[i] >= '0' && s[i] <= '9') {
        value = value * 10 + (s[i] - '0');
        i++;
    }
    parseDigits(value);

    //if nothing was added to digits then add a zero
    if (digits.empty()) {
        digits.push_back(0);
    }
}

//overloaded output operator
ostream& operator<<(ostream& os, const BigUnsigned& obj) {
    for (size_t i = obj.digits.size(); i > 0; i--) {
        os << obj.digits[i - 1];
    }
    return os;
}

//Parses the digits of a given integer value and stores them in a vector
//Parameters: int - the value to be parsed
//Return Type: void
void BigUnsigned::parseDigits(int value) {
    while(value > 0 ) {
        int temp = value % 10;
        digits.push_back(temp);
        value = value / 10;
    }
}

//Overloads the equality operator to compare two BigUnsigned objects
//Parameters:lhs - the left side integer, rhs - the right side integer
//Return Type: true if both BigUnsigned objects are equal else false
bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs){
    if (lhs.getLength() != rhs.getLength()) {
        return false;
    }

    for (size_t i = 0; i < lhs.getLength(); i++) {
        if (lhs.getDigit(i) != rhs.getDigit(i)) {
            return false;
        }
    }
    return true;
}

//Overloads the less-than operator to compare two BigUnsigned objects
//Parameters: lhs - the left side integer, rhs - the right side integer
//Return Type: true if lhs is less than rhs else false
bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    if (lhs.getLength() < rhs.getLength()) {
        return true;
    }

    if (lhs.getLength() == rhs.getLength()) {
        for (size_t i = lhs.getLength(); i > 0; i--) {
            if (lhs.getDigit(i - 1) < rhs.getDigit(i - 1)) {
                return true;
            }
        }
    }
    return false;
}


//Getter for a specific digit
//Parameters: size_t - the index of the digit to get
//Return Type: int - the digit at the specified index
int BigUnsigned::getDigit(size_t index) const {
    if (index >= digits.size()) {
        cerr << ("Index out of bounds");
    }
    return digits[index];
}

//Overloaded += operator to add a rhs to the current object
//Parameters: BigUnsigned - the right-hand side operand
//Return Type: BigUnsigned& - reference to the current object
BigUnsigned& BigUnsigned::operator+=(const BigUnsigned& rhs) {
    for (int i = 0; i < rhs.digits.size(); i++) {
        //both digits in index i from current object and rhs, if rhs has more
        //digits than current object push back new digits to current object
        if (i < digits.size()) {
            digits[i] += rhs.digits[i];
            if (digits[i] > 9) {
                digits[i] -= 10;
                if (i + 1 == digits.size()) {
                    digits.push_back(1);
                } else {
                    digits[i + 1] += 1;
                }
            }
        } else {
            digits.push_back(rhs.digits[i]);
        }
    }
    return *this;
}

//Overloaded pre increment operator
//Parameters: None
//Return Type: BigUnsigned& - a reference to the incremented object
BigUnsigned& BigUnsigned::operator++() {
    *this += 1;
    return *this;
}

//Overloaded post increment operator
//Parameters: int - a dummy
//Return Type: BigUnsigned - the original value before incrementing
BigUnsigned BigUnsigned::operator++(int) {
    BigUnsigned tmp = *this;
    *this += 1;
    return tmp;
}

//prototypes
BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs);

int main() {
    BigUnsigned zero;
    BigUnsigned one(1);

    cout << "zero: " << zero << endl;
    cout << "one: " << one << endl;

    BigUnsigned val = 1;
    cout << "val: " << val << endl;
    cout << "++val: " << ++val << endl;
    cout << "val: " << val << endl;
    cout << "val++: " << val++ << endl;
    cout << "val: " << val << endl;

    cout << "(one + zero): " << (one + zero) << endl;
    cout << "(one + one): " << (one + one) << endl;

    cout << boolalpha;
    cout << "one < one: " << (one < one) << endl;
    cout << "zero < one: " << (zero < one) << endl;

    BigUnsigned a = 123;
    BigUnsigned b = 1234;
    BigUnsigned c = 124;
    BigUnsigned d = 12345;

    cout << "a: " << a << ", b: " << b
            << ", c: " << c << ", d: " << d << endl;
    cout << "a + d: " << (a + d) << endl;
    cout << "d + d: " << (d + d) << endl;
    cout << "a < d: " << (a < d) << endl;
    cout << "d < a: " << (d < a) << endl;
    cout << "zero == zero: " << (zero == zero) << endl
            << "zero == one: " << (zero == one) << endl
            << "a == a: " << (a == a) << endl
            << "a == d: " << (a == d) << endl
            << "d == a: " << (d == a) << endl;

    cout << "(zero == 0): " << (zero == 0) << endl
            << "(one == 0): " << (one == 0) << endl
            << "(1 == one): " << (1 == one) << endl;

    //+=
    cout << "b: " << b << ", c: " << c << endl;
    cout << "(c += b): " << (c += b) << endl;
    cout << "b: " << b << ", c: " << c << endl;


    BigUnsigned x = a;
    cout << "x: " << x << ", a: " << a << endl
            << "x == a: " << (x == a) << endl
            << "a == x: " << (a == x) << endl
            << "a < x: " << (a < x) << endl
            << "a > x: " << (a > x) << endl;

    cout << "x > a: " << (x > a) << endl
            << "x >= a: " << (x >= a) << endl
            << "x <= a: " << (x <= a) << endl
            << "x != a: " << (x != a) << endl;


    BigUnsigned big("987654321");
    BigUnsigned big2("  ");
    BigUnsigned big3("felix");
    BigUnsigned big4("00987654321");

    cout << "big: " << big << endl
            << "big2: " << big2 << endl
            << "big3: " << big3 << endl
            << "big4: " << big4 << endl;

    BigUnsigned big5(98765);
    BigUnsigned big6(2457);
    cout << "big5: " << big5 << ", big6: " << big6 << endl
            << "(big5 + big6): " << (big5 + big6) << endl
            << "(big6 + big5): " << (big6 + big5) << endl;


    //How does this work?
    cout << zero << " is " << (zero ? "true" : "false") << endl;
    cout << one << " is " << (one ? "true" : "false") << endl;
    cout << big4 << " is " << (big4 ? "true" : "false") << endl;
} //main


//Adds two Big Unsigned numbers and returns the result.
//Parameters: lhs - the left side integer, rhs - the right side integer
//Return Type:
// BigUnsigned - the sum of lhs and rhs
BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    BigUnsigned result(0);
    result += lhs;
    result += rhs;
    return result;
}

//Overloads the not-equal operator to compare two BigUnsigned objects
//Parameters: lhs - the left side integer, rhs - the right side integer
//Return Type: true if lhs is not equal to rhs else false
bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    return !(lhs == rhs);
}

//Overloads the less-than-or-equal operator to compare two BigUnsigned objects
//Parameters: lhs - the left side integer, rhs - the right side integer
//Return Type: true if lhs is less than or equal to rhs else false
bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

//Overloads the greater-than operator to compare two BigUnsigned objects
//Parameters: lhs - the left side integer, rhs - the right side integer
//Return Type: true if lhs is greater than rhs else false
bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    return !(lhs <= rhs);
}

//Overloads the greater-than-or-equal operator to compare two BigUnsigned objects
//Parameters: lhs - the left side integer, rhs - the right side integer
//Return Type: true if lhs is greater than or equal to rhs else false
bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    return !(lhs < rhs);
}
