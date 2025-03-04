// Deejuanae Lewis

#include "Noble.h"
using namespace std;

namespace WarriorCraft {
    // Constructor that initializes a Noble with a name and sets their alive status
    // to true
    Noble::Noble(const string &name): name(name), alive(true) {
    }

    //Returns the name of the noble
    //Parameters: None
    //Return Type: a string that represents the name of the noble
    const string &Noble::getName() const {
        return name;
    }

    //Checks if the fighters are alive
    //Parameters: a Noble - the enemy
    //Return Type: a bool representing whether the fighters can battle
    bool Noble::battleCheck(const Noble &enemy) const {
        if (!this->isAlive() && !enemy.isAlive()) {
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
            return false;
        }
        if (!this->isAlive()) {
            enemy.attack();
            cout << "He's dead " << enemy.getName() << endl;
            return false;
        }
        if (!enemy.isAlive()) {
            this->attack();
            cout << "He's dead " << this->getName() << endl;
            return false;
        }
        this->attack();
        enemy.attack();
        return true;
    }

    //simulates battle between two nobles by comparing army strengths
    //Parameters: Noble& enemy - the enemy noble
    //Return Type: void
    void Noble::battle(Noble &enemy) {
        cout << this->getName() << " battles " << enemy.getName() << endl;

        if (battleCheck(enemy)) {
            double myStrength = this->getStrength();
            double enemyStrength = enemy.getStrength();

            if (myStrength > enemyStrength) {
                this->reduceStrength(enemyStrength);
                enemy.reduceStrength(enemyStrength);
                enemy.setAlive(false);
                cout << this->getName() << " defeats " << enemy.getName() << endl;
            } else if (enemyStrength > myStrength) {
                enemy.reduceStrength(myStrength);
                this->reduceStrength(myStrength);
                this->setAlive(false);
                cout << enemy.getName() << " defeats " << this->getName() << endl;
            } else {
                this->reduceStrength(myStrength);
                this->setAlive(false);
                enemy.reduceStrength(enemyStrength);
                enemy.setAlive(false);
                cout << "Mutual Annihilation: " << this->getName() << " and "
                        << enemy.getName() << " die at each other's hands" << endl;
            }
        }
    }

    // Returns the alive status of the Noble
    // Parameters: None
    // Return Type: a bool
    bool Noble::isAlive() const {
        return alive;
    }

    // Sets the alive status of the Noble to the specified new status
    // Parameters: newStatus (bool) - true for alive, false for dead
    // Return Type: Void
    void Noble::setAlive(bool newStatus) {
        alive = newStatus;
    }

    // overloaded output operator to Lord
    ostream &operator<<(ostream &os, const Lord &obj) {
        os << obj.getName() << " has an army of size: " << obj.protectorPtrs.size();
        for (const Protector *protector: obj.protectorPtrs) {
            os << "\n\t" << *protector;
        }
        return os;
    }

    // Constructor that initializes a Lord with a name, calling the base class
    // Noble constructor
    // Parameters: name (string) - the name of the Lord
    // Return Type: Void
    Lord::Lord(const string &name): Noble(name) {
    }

    // Calculates and returns the total strength of the noble's army
    // Parameters: None
    // Return Type: a double that represents the total strength of the army
    double Lord::getStrength() const {
        double total = 0;
        for (const Protector *protector: protectorPtrs) {
            total += protector->getStrength();
        }
        return total;
    }

    // Reduces the strength of all their Protectors a lord has
    // Parameters: change (double) - the amount the Lord's strength is reduced
    // Return Type: Void
    void Lord::reduceStrength(double change) {
        double ratio = 1 - (change / getStrength());
        for (Protector *protector: protectorPtrs) {
            protector->setStrength(protector->getStrength() * ratio);
        }
    }

    // Hires a protector into the lord's army if the protector is available and alive
    // and if the noble is alive
    // Parameters: Warrior& warrior - the warrior to hire
    // Return Type: bool - true if hire was successful else false
    bool Lord::hires(Protector &protector) {
        if (!this->isAlive() || protector.isHired() || protector.getStrength() ==
            0) {
            cout << this->getName() << " failed to hire " << protector.getName()
                << endl;
            return false;
            }
        protectorPtrs.push_back(&protector);
        protector.setHired(true);
        protector.setLord(this);
        return true;
    }

    // Removes a warrior from the noble's army unless the noble is dead or the
    // warrior does not belong to this noble
    // Parameters: Warrior& warrior - the warrior to fire
    // Return Type: a bool - true if fire was complete else false
    bool Lord::fires(Protector &protector) {
        if (this->isAlive()) {
            if (removeProtector(protector)) {
                cout << protector.getName() <<
                        ", you don't work for me anymore ! -- "
                        << this->getName() << "." << endl;
                return true;
            }
        }
        cout << this->getName() << " failed to fire " << protector.getName() <<
                endl;
        return false;
    }

    // Removes protector from the nobles list
    // Parameter: Protector& protector - the protector that needs to be removed
    // Return Type: a bool that tells whether the protector has been removed
    bool Lord::removeProtector(Protector &protector) {
        for (size_t i = 0; i < protectorPtrs.size(); ++i) {
            if (protectorPtrs[i] != &protector) {
                continue;
            }
            for (size_t j = i; j < protectorPtrs.size() - 1; ++j) {
                protectorPtrs[j] = protectorPtrs[j + 1];
            }
            protectorPtrs.pop_back();
            protector.setHired(false);
            return true;
        }
        return false;
    }

    // Makes the Lord command all their Protectors to attack by calling their
    // respective attack methods
    // Parameters: None
    // Return Type: Void
    void Lord::attack() const {
        for (const Protector *protector: protectorPtrs) {
            protector->attack();
        }
    }

    //overloaded output operator to PersonWithStrengthToFight
    ostream &operator<<(ostream &os, const PersonWithStrengthToFight &obj) {
        os << obj.getName() << " has strength: " << obj.strength << endl;
        return os;
    }

    // Constructor that initializes a PersonWithStrengthToFight with a name and
    // strength, calling the base class (Noble) constructor.
    PersonWithStrengthToFight::PersonWithStrengthToFight(const string &name,
        double strength): Noble(name), strength(strength) {
    }

    // Returns the current strength of the person.
    // Parameters: None
    // Return Type: double - the current strength of the person
    double PersonWithStrengthToFight::getStrength() const {
        return strength;
    }

    // Reduces the person's strength by a specified amount, ensuring the strength
    // doesn't go below 0
    // Parameters: change (double) - the amount to reduce the strength by
    // Return Type: Void
    void PersonWithStrengthToFight::reduceStrength(double change) {
        if (change > strength) {
            strength = 0;
        } else {
            strength -= change;
        }
    }

    // Makes the person attack, outputting a sound "Ugh!".
    // Parameters: None
    // Return Type: Void
    void PersonWithStrengthToFight::attack() const {
        cout << "Ugh!" << endl;
    }
}