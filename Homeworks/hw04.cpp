//Deejuanae lewis
/*
  Association: Noble - Warrior
  The purpose of this program is to simulate battles between nobles, where each
  can hire warriors. The combined strength of all the warriors determines
  the outcome of the battle.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Your Noble and Warrior classes should go here.
// ...

//Warrior class represents a warrior with a name, strength, and hired status
class Warrior {
    friend ostream& operator << (ostream& os, const Warrior& obj);
public:
    Warrior(const string& name, int strength): name(name), strength(strength),
    hired(false) {}

    //getters
    const string& getName() const {return name;}
    double getStrength() const {return strength;}
    bool isHired() const {return hired;}

    //setters
    void setHired(bool newStatus) {hired = newStatus;}
    void setStrength(double newStrength) {strength = newStrength;}

private:
    string name;
    double strength;
    bool hired;

};


//overloaded output operator to print warrior
ostream& operator << (ostream& os, const Warrior& obj) {
    os << obj.name << ": " << obj.strength;
    return os;
}


//Noble class represents a noble with a name and a warriors. The noble can
//choose to hire, fire, and battle warriors.
class Noble {
    friend ostream& operator << (ostream& os, const Noble& obj);
public:
    Noble(const string& name) : name(name), alive(true){}

    //getters
    const string& getName() const {return name;}
    double getArmyStrength() const;
    bool isAlive() const {return alive;}

    //setters
    void setAlive(bool newStatus) {alive = newStatus;}
    void setStrengthToZero();
    void setStrengthByRatio(double ratio);

    //prototypes
    bool hire(Warrior& warrior);
    bool fire(Warrior& warrior);
    void battle(Noble& enemy);

private:
    string name;
    vector<Warrior*> warriorPtrs;
    bool alive;

};

//Calculates and returns the total strength of the noble's army
//Parameters: None
//Return Type: a double that represents the total strength of the army
double Noble::getArmyStrength() const {
    double total = 0;
    for (Warrior* warrior : warriorPtrs) {
        total += warrior->getStrength();
    }
    return total;
}

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

//Hires a warrior into the noble's army if the warrior is available and alive
//and if the noble is alive
//Parameters: Warrior& warrior - the warrior to hire
//Return Type: bool - true if hire was successful else false
bool Noble::hire(Warrior& warrior) {
    if(!this-> isAlive()) {
        cout << this-> getName() << "is Dead";
        return false;
    }
    if(warrior.isHired() || warrior.getStrength() == 0) {
        cout << this->getName() << " failed to hire " << warrior.getName()
        << endl;
        return false;
    }
    Warrior* warriorPtr = &warrior;
    warriorPtrs.push_back(warriorPtr);
    warrior.setHired(true);
    return true;
}

//removes a warrior from the noble's army unless the noble is dead or the
//warrior does not belong to this noble
//Parameters: Warrior& warrior - the warrior to fire
//Return Type: a bool - true if fire was complete else false
bool Noble::fire(Warrior& warrior) {
    if(!this-> isAlive()) {
        cout << this-> getName() << "is Dead. He can't fire a warrior.";
        return false;
    }
    for (size_t i = 0; i < warriorPtrs.size(); ++i) {
        if (warriorPtrs[i] == &warrior){
            for (size_t j = i; j < warriorPtrs.size() - 1; ++j) {
                warriorPtrs[j] = warriorPtrs[j + 1];
            }
            warriorPtrs.pop_back();
            cout << warrior.getName() << " you don't work for me any more! --"
            << this->getName() << endl;
            warrior.setHired(false);
            return true;
        }
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
            cout << enemy.getName() << " defeats" << this->getName() << endl;
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

//overloaded output operator to print noble and their army
ostream& operator << (ostream& os, const Noble& obj) {
    os << obj.getName() << " has an army of " << obj.warriorPtrs.size();
    for (Warrior* warrior: obj.warriorPtrs) {
        os <<"\n\t"<< *warrior ;
    }
    return os;
}


int main()
{
    //code for testing the Noble and Warrior Classes
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);

    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";

    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

}
