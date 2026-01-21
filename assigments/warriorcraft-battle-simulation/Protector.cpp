#include "Protector.h"
using namespace std;

namespace WarriorCraft {

//overloaded output operator to Protector
ostream &operator<<(ostream &os, const Protector &obj) {
    os << obj.name << " has strength " << obj.strength;
    return os;
}

// Constructor that initializes a Protector with a name, strength, hired status,
// and no lord.
Protector::Protector(const string &name, double strength): name(name),
    strength(strength), hired(false), lord(nullptr) {
}

// Returns the name of the protector.
// Parameters: None
// Return Type: const string& - the name of the protector
const string &Protector::getName() const {
    return name;
}

// Returns the strength of the protector.
// Parameters: None
// Return Type: double - the strength of the protector
double Protector::getStrength() const {
    return strength;
}

// Sets the strength of the protector to a new value.
// Parameters: change (double) - the new strength value for the protector
// Return Type: Void
void Protector::setStrength(double change) {
    strength = change;
}

// Returns whether the protector is currently hired or not.
// Parameters: None
// Return Type: bool - true if the protector is hired, false otherwise
bool Protector::isHired() const {
    return hired;
}

// Sets the hiring status of the protector.
// Parameters: newStatus (bool) - the new hired status of the protector
// Return Type: Void
void Protector::setHired(const bool newStatus) {
    hired = newStatus;
}

// Sets the protector's lord to a new lord object.
// Parameters: newLord - a pointer to the new lord the protector will serve
// Return Type: Void
void Protector::setLord(Lord *newLord) {
    lord = newLord;
}

//Makes a protector runaway changing his employer none and hire status to false
//Parameters: None
//Return Type: Void
void Protector::runaway() {
    if (lord) {
        cout << name << " flees in terror, abandoning his lord, " <<
                lord->getName() << endl;
        lord->removeProtector(*this);
        setLord(nullptr);
    } else {
        cout << this->name << " is not employed by anyone!" << endl;
    }
}

// Constructor that initializes a Wizard with a name and strength,
// calling the base class (Protector) constructor
Wizard::Wizard(const string &name, double strength): Protector(name, strength) {
}

//Prints out the attack of a wizard
//Parameters: None
//Return Type: void
void Wizard::attack() const {
    cout << "POOF!" << endl;
}

// Constructor that initializes a Warrior with a name and strength, calling the
// base class (Protector) constructor
Warrior::Warrior(const string &name,
                 double strength): Protector(name, strength) {
}

// Constructor that initializes an Archer with a name and strength, calling the
// base class (Protector) constructor
Archer::Archer(const string &name, double strength): Warrior(name, strength) {
}

//Prints out the attack of a Archer
//Parameters: None
//Return Type: void
void Archer::attack() const {
    cout << "TWANG!  " << getName() <<
            " says: Take that in the name of my lord, "
            << lord->getName() << endl;
}

// Constructor that initializes a Swordsman with a name and strength,
// calling the base class (Protector) constructor.
Swordsman::Swordsman(const string &name, double strength): Warrior(
    name, strength) {
}

//Prints out the attack of a Swordsman
//Parameters: None
//Return Type: void
void Swordsman::attack() const {
    cout << "CLANG!  " << getName() <<
            " says: Take that in the name of my lord, "
            << lord->getName() << endl;
}

}

