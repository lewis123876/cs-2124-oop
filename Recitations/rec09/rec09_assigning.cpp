//Deejuanae Lewis
#include <iostream>
using namespace std;

class Base {
public:
    void baseMethod() {
        cout << "Base method: " << endl;
    }
private:
};

class Derived : public Base {
public:
    void derivedMethod() {
        cout << "Derived method: " << endl;
    }
private:
};

int main() {
    Base baseInstance;
    Derived derivedInstance;

    Base* basePtr = nullptr;
    Derived* derivedPtr = nullptr;

    baseInstance = derivedInstance;

    // derivedInstance = baseInstance;

    basePtr = derivedPtr;

    // derivedPtr = basePtr;

    basePtr = &baseInstance;
    basePtr = &derivedInstance;

    // derivedPtr = &baseInstance;
    derivedPtr = &derivedInstance;

}
