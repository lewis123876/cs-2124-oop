// Deejuanae Lewis

#include <iostream>
#include <vector>
#include "polynomial.h"
using namespace std;

// Overloads the output operator to print the polynomial in a readable format
ostream& operator<<(ostream& os, const Polynomial& obj) {
     Polynomial::Node* curr = obj.headPtr;
     int countDegree = obj.degree;

     while (curr) {
          if (curr->coeff == 0 && obj.degree < 1) {
               os << curr->coeff;
               return os;
          }
          if (curr->coeff != 0) {
               if (curr->coeff == -1 && countDegree > 0) {
                    os << "-";
               } else if (curr->coeff != 1 || countDegree == 0) {
                    os << curr->coeff;
               }

               if (countDegree > 0) {
                    os << "x";
                    if (countDegree > 1) os << "^" << countDegree;
               }

               if (curr->next) os << "+";
          }
          countDegree--;
          curr = curr->next;
     }
     return os;
}


// Constructs a default Polynomial object with a constant term of 0 and degree 0
// Parameters: None
// Return Type: None
Polynomial::Polynomial(): headPtr(new Node{}), degree(0){}

// Constructs a Polynomial object from a vector of coefficients
// Parameters: coeffs - coefficients, from highest to lowest degree
// Return Type: None
Polynomial::Polynomial(const vector<int>& coeffs): headPtr(nullptr),
degree(coeffs.size()-1) {
     if (coeffs.size() == 0) {
          return;
     }
     headPtr = new Node{coeffs[0]};
     Node* curr = headPtr;

     for (int i = 1; i < coeffs.size(); i++) {
          Node* newNode = new Node{coeffs[i]};
          curr->next = newNode;
          curr = curr->next;
     }
     removeZeros();
}

//Copy Control

// Constructs a copy of another Polynomial object
// Parameters: rhs - the Polynomial to copy
// Return Type: None
Polynomial::Polynomial(const Polynomial& rhs) {
     if(!rhs.headPtr) {
          headPtr = nullptr;
          degree = 0;
          return;
     }
     degree = rhs.degree;
     headPtr = new Node{rhs.headPtr->coeff};
     Node* curr = headPtr;
     Node* rhsCurr = rhs.headPtr->next;
     while(rhsCurr){
          Node* newNode = new Node{rhsCurr->coeff};
          curr->next = newNode;
          curr = curr->next;
          rhsCurr = rhsCurr->next;
     }
     removeZeros();
}

// Overloads the assignment operator to copy another Polynomial object
// Parameters: rhs - the Polynomial to copy
// Return Type: Polynomial& - reference to the updated Polynomial object
Polynomial& Polynomial::operator=(const Polynomial& rhs) {
     if (this != &rhs) {
          while (headPtr) {
               Node* prev = headPtr;
               headPtr = headPtr->next;
               delete prev;
          }
          headPtr = new Node{};

          degree = rhs.degree;
          headPtr = new Node{rhs.headPtr->coeff};
          Node* curr = headPtr;
          Node* currRhs = rhs.headPtr->next;
          while (currRhs) {
               curr->next = new Node{currRhs->coeff};
               curr = curr->next;
               currRhs = currRhs->next;
          }
     }
     return *this;
}

// Destroys the Polynomial object, releasing allocated memory
// Parameters: None
// Return Type: None
Polynomial::~Polynomial() {
     while (headPtr) {
          Node* prev = headPtr;
          headPtr = headPtr->next;
          delete prev;
     }
     headPtr = nullptr;
}

//operators

// Adds another Polynomial to the current Polynomial
// Parameters: rhs - the Polynomial to add
// Return Type: Polynomial& - reference to the updated Polynomial object
Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
     if (rhs.headPtr != nullptr) {

          // if the rhs polynomial is larger
          // expand the current polynomial to match the rhs
          while (rhs.degree > degree) {
               Node* newHead = new Node {0, headPtr};
               headPtr = newHead;
               degree++;
          }

          // if the current polynomial is larger
          // expand the rhs to match the current polynomial
          Polynomial adjustedRhs = rhs;
          while (degree > adjustedRhs.degree) {
               Node* newHead= new Node{0, adjustedRhs.headPtr};
               adjustedRhs.headPtr=newHead;
               adjustedRhs.degree++;
          }

          //add the coefficients of the two polynomials
          Node* curr = headPtr;
          Node* rhsCurr = adjustedRhs.headPtr;
          while (curr && rhsCurr) {
               curr->coeff += rhsCurr->coeff;
               curr = curr->next;
               rhsCurr = rhsCurr->next;
          }

          //remove any leading zeros
          removeZeros();
     }
     return *this;
}

// Overloads the + operator to add two Polynomial objects
// Parameters: rhs - the first Polynomial, lhs - the second Polynomial
// Return Type: Polynomial - the result of adding the two polynomials
Polynomial operator+(const Polynomial& rhs, const Polynomial& lhs){
     Polynomial result = rhs;
     result += lhs;
     return result;
}

// Compares two Polynomial objects to see if they are equal
// Parameters: rhs - the first Polynomial, lhs - the second Polynomial
// Return Type: bool - true if the polynomials are equal else false
bool operator==(const Polynomial& rhs, const Polynomial& lhs){
     Polynomial::Node* currRhs = rhs.headPtr;
     Polynomial::Node* currLhs = lhs.headPtr;
     if(&currLhs != &currRhs) {
          if(lhs.degree != rhs.degree) return false;
          while (currRhs) {
               if (lhs.headPtr->coeff != rhs.headPtr->coeff) return false;
               currLhs = currLhs->next;
               currRhs = currRhs->next;
          }
     }
     return true;
}
// Compares two Polynomial objects to see if they are NOT equal
// Parameters: rhs - the first Polynomial, lhs - the second Polynomial
// Return Type: bool - true if the polynomials are NOT equal else false
bool operator!=(const Polynomial& rhs, const Polynomial& lhs){
     return !(rhs == lhs);
}

// Evaluates the polynomial for a given value
// Parameters: value - the value to substitute for x
// Return Type: int - the result of the evaluation
int Polynomial::evaluate(int value) const {
     int result = 0;
     Node* curr = headPtr;

     //evaluation based on horner's method
     while (curr) {
          result = result * value + curr->coeff;
          curr = curr->next;
     }

     return result;
}

// Removes leading zero terms from the polynomial
// Parameters: None
// Return Type: Void
void Polynomial::removeZeros() {
     //removes leading zeros and deletes the node
     while (headPtr && headPtr->coeff == 0 && degree > 0) {
          Node* temp = headPtr;
          headPtr = headPtr->next;
          delete temp;
          degree--;
     }
     if(!headPtr) {
          headPtr = new Node{};
          degree = 0;
     }
}

void doNothing(Polynomial temp) {}
