/*The purpose of the program is to simulate battles between nobles , where they
  can hire and fire warriors. The combined strength of all warriors determines
  the outcome of the battle. Some key differences with this assignment and the
  last is the usage of cyclic association and separate compilation.
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//forward declaration of Noble class
class Noble;

//Warrior class represents a warrior with a name, strength, and hired status
class Warrior {
    friend ostream& operator << (ostream& os, const Warrior& obj);
public:
    Warrior(const string& name, double strength);

    void runaway();

    //getters
    const string& getName() const;
    double getStrength() const;
    bool isHired() const;

    //setters
    void setHired(bool newStatus);
    void setStrength(double newStrength);
    void setNoble(Noble* newNoble);

private:
    string name;
    double strength;
    bool hired;
    Noble* noble;
};

//Noble class represents a noble with a name and a warriors. The noble can
//choose to hire, fire, and battle warriors.
class Noble {
    friend ostream& operator << (ostream& os, const Noble& obj);
public:
    Noble(const string& name);

    bool hire(Warrior& warrior);
    bool fire(Warrior& warrior);
    void battle(Noble& enemy);
    bool removeWarrior(Warrior& warrior);

    //getters
    const string& getName() const;
    double getArmyStrength() const;
    bool isAlive() const;

    //setters
    void setAlive(bool newStatus);
    void setStrengthToZero();
    void setStrengthByRatio(double ratio);

private:
    string name;
    vector<Warrior*> warriorPtrs;
    bool alive;
};


int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
     << lance << endl
     << jim << endl
     << linus << endl
     << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
     << lance << endl
     << jim << endl
     << linus << endl
     << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
     << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
     << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}



//Warrior Definitions

//overloaded output operator to warrior
ostream& operator<<(ostream& os, const Warrior& obj) {
    os << obj.name << ": " << obj.strength;
    return os;
}

//Warrior Constructor
Warrior::Warrior(const string& name, double strength)
       : name(name), strength(strength), hired(false), noble(nullptr) {}

//Makes a warrior runaway changing his employer none and hire status to false
//Parameters: None
//Return Type: Void
void Warrior::runaway() {
    if(noble) {
        cout << this->name << " flees in terror, abandoning his lord, " <<
            this->noble->getName() << endl;
        noble->removeWarrior(*this);
        setNoble(nullptr);
        setHired(false);
    }
    else {
        cout << this->name << " is not employed by anyone!" << endl;
    }
}

//Getters
const string& Warrior::getName() const { return name; }
double Warrior::getStrength() const { return strength; }
bool Warrior::isHired() const { return hired; }

//Setters
void Warrior::setHired(bool newStatus) { hired = newStatus; }
void Warrior::setStrength(double newStrength) { strength = newStrength; }
void Warrior::setNoble(Noble* newNoble) { noble = newNoble; }


//Noble Definitions

//overloaded output operator to print noble and their army
ostream& operator << (ostream& os, const Noble& obj) {
    os << obj.getName() << " has an army of " << obj.warriorPtrs.size();
    for (const Warrior* const warrior: obj.warriorPtrs) {
        os <<"\n\t"<< *warrior ;
    }
    return os;
}

//Noble Constructor
Noble::Noble(const std::string& name) : name(name), alive(true) {}

//Hires a warrior into the noble's army if the warrior is available and alive
//and if the noble is alive
//Parameters: Warrior& warrior - the warrior to hire
//Return Type: bool - true if hire was successful else false
bool Noble::hire(Warrior& warrior) {
    if(!this-> isAlive()) {
        cout << this-> getName() << " is Dead";
        return false;
    }
    if(warrior.isHired() || warrior.getStrength() == 0) {
        cout << this->getName() << " failed to hire " << warrior.getName()
        << endl;
        return false;
    }
    warriorPtrs.push_back(&warrior);
    warrior.setHired(true);
    warrior.setNoble(this);
    return true;
}

//removes a warrior from the noble's army unless the noble is dead or the
//warrior does not belong to this noble
//Parameters: Warrior& warrior - the warrior to fire
//Return Type: a bool - true if fire was complete else false
bool Noble::fire(Warrior& warrior) {
    if(!this-> isAlive()) {
        cout << this-> getName() << " is Dead. He can't fire a warrior.";
        return false;
    }

    if(removeWarrior(warrior)) {
        cout << warrior.getName() << ", you don't work for me anymore! --"
            << this->getName() << endl;
        return true;
    }

    cout <<this->getName() << " failed to fire " << warrior.getName() << endl;
    return false;

}

//simulates battle between two nobles by comparing army strengths
//Parameters: Noble& enemy - the enemy noble
//Return Type: void
void Noble::battle(Noble& enemy) {
    cout << this-> getName() << " battles " << enemy.getName() << endl;

    //compares the two nobles strengths and determines the outcome of the battle
    if(!this-> isAlive() && !enemy.isAlive()) {
        cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
    }
    else if(!this-> isAlive()) {
        cout << "He's dead, " << enemy.getName() << endl;
    }
    else if(!enemy.isAlive()) {
        cout << "He's dead, " << this-> getName() << endl;
    }
    else {
        double myStrength = this-> getArmyStrength();
        double enemyStrength = enemy.getArmyStrength();

        if (myStrength > enemyStrength) {
            double ratio = enemyStrength/myStrength;
            this->setStrengthByRatio(ratio);
            enemy.setStrengthToZero();
            enemy.setAlive(false);
            cout << this-> getName() << " defeats " << enemy.getName() << endl;
        }
        else if(enemyStrength > myStrength) {
            double ratio = myStrength/enemyStrength;
            enemy.setStrengthByRatio(ratio);
            this->setStrengthToZero();
            this->setAlive(false);
            cout << enemy.getName() << " defeats " << this->getName() << endl;
        }
        else {

            this->setStrengthToZero();
            this->setAlive(false);
            enemy.setStrengthToZero();
            enemy.setAlive(false);
            cout << "Mutual Annihilation: " << this-> getName() << " and "
            << enemy.getName() << " die at each other's hands" << endl;
        }
    }

}

//Removes warrior from the nobles warrior list
//Parameter: Warrior& warrior - the warrior that needs to be removed
//Return Type: a bool that tells whether the warrior has been removed
bool Noble::removeWarrior(Warrior& warrior) {
    for (size_t i = 0; i < warriorPtrs.size(); ++i) {
        if (warriorPtrs[i] == &warrior){
            for (size_t j = i; j < warriorPtrs.size() - 1; ++j) {
                warriorPtrs[j] = warriorPtrs[j + 1];
            }
            warriorPtrs.pop_back();
            warrior.setHired(false);
            return true;
        }
    }
    return false;
}


//getters
const string& Noble::getName() const { return name; }

//Calculates and returns the total strength of the noble's army
//Parameters: None
//Return Type: a double that represents the total strength of the army
double Noble::getArmyStrength() const {
    double total = 0;
    for (const Warrior* warrior : warriorPtrs) {
        total += warrior->getStrength();
    }
    return total;
}

bool Noble::isAlive() const { return alive;}


//setters
void Noble::setAlive(bool alive) { this->alive = alive;}

//Sets the strength of all warriors in the noble's army to zero
//Parameters: None
//Return Type: void
void Noble::setStrengthToZero() {
    for(Warrior* warrior: warriorPtrs) {
        warrior->setStrength(0);
    }
}

//Adjusts the strength of all warriors by a ratio
//Parameters: a double - the ratio or two armies
//Return Type: void
void Noble::setStrengthByRatio(double ratio) {
    for(Warrior* warrior: warriorPtrs) {
        warrior->setStrength(warrior->getStrength() * (1-ratio));
    }
}



