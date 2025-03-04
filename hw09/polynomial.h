// Deejuanae Lewis

#include<iostream>
#include<vector>

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

class Polynomial {
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& obj);
    friend bool operator==(const Polynomial& rhs, const Polynomial& lhs);
public:
    Polynomial();
    Polynomial(const std::vector<int>& coeffs);

    //Copy Control
    Polynomial(const Polynomial& rhs);
    Polynomial& operator=(const Polynomial& rhs);
    ~Polynomial();

    //operator
    Polynomial& operator+=(const Polynomial& rhs);

    //methods
    int evaluate(int value) const;

private:
    struct Node {
        int coeff = 0;
        Node* next = nullptr;
    };

    void removeZeros();

    int degree;
    Node* headPtr;
};

Polynomial operator+(const Polynomial& rhs, const Polynomial& lhs);
bool operator!=(const Polynomial& rhs, const Polynomial& lhs);
void doNothing(Polynomial temp);

#endif //POLYNOMIAL_H
