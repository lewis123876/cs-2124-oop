/*The purpose of the program is to simulate battles between nobles , where they
  can hire and fire warriors. The combined strength of all warriors determines
  the outcome of the battle. Some key differences with this assignment and the
  last is the usage of the heap, dynamic memory management, and new errors.
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bits/fs_fwd.h>

using namespace std;

//Warrior class represents a warrior with a name, strength, and hired status
class Warrior {
    friend ostream& operator << (ostream& os, const Warrior& obj);
public:
    Warrior(const string& name, double strength): name(name),
    strength(strength), hired(false) {}

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
        cout << this-> getName() << " is Dead";
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
        cout << this-> getName() << " is Dead. He can't fire a warrior.";
        return false;
    }
    for (size_t i = 0; i < warriorPtrs.size(); ++i) {
        if (warriorPtrs[i] == &warrior){
            for (size_t j = i; j < warriorPtrs.size() - 1; ++j) {
                warriorPtrs[j] = warriorPtrs[j + 1];
            }
            warriorPtrs.pop_back();
            cout << warrior.getName() << ", you don't work for me any more! --"
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

//overloaded output operator to print noble and their army
ostream& operator << (ostream& os, const Noble& obj) {
    os << obj.getName() << " has an army of " << obj.warriorPtrs.size();
    for (Warrior* const warrior: obj.warriorPtrs) {
        os <<"\n\t"<< *warrior ;
    }
    return os;
}

//Prototypes
void openFile(ifstream& ifs);
Noble* findNoble(const vector<Noble*>& nobles, const string& name);
Warrior* findWarrior(const vector<Warrior*>& warriors, const string& name);
void status(const vector<Warrior*>& warriorPtrs, const vector<Noble*>& noblePtrs);
void clear(vector<Warrior*>& warriorPtrs, vector<Noble*>& noblePtrs);


int main() {
    //open the nobleWarriors file for reading
    ifstream ifs;
    openFile(ifs);
    string command;
    string name;
    string name2;
    double strength;

    //vectors to store pointers of nobles and warriors
    vector<Noble*> noblePtrs;
    vector<Warrior*> warriorPtrs;


    //Loop through each command and execute the corresponding action
    while(ifs >> command) {
        //If the command is "Noble", add a noble if they don't already exist
        if (command == "Noble") {
            ifs >> name;
            Noble* noble = findNoble(noblePtrs, name);
            if (noble) {
                cout << "Noble " << name << " already exists." << endl;
                continue;
            }
            Noble* newNoble = new Noble(name);
            noblePtrs.push_back(newNoble);
        }
        //If the command is "Warrior", add a warrior if they don't already exist
        else if (command == "Warrior") {
            ifs >> name >> strength;
            Warrior* warrior = findWarrior(warriorPtrs, name);
            if (warrior) {
                cout << "Warrior " << name << " already exists." << endl;
                continue;
            }
            Warrior* newWarrior = new Warrior(name, strength);
            warriorPtrs.push_back(newWarrior);
        }
        //If the command is "Hire", try to hire a warrior for a noble
        else if(command == "Hire") {
            ifs >> name >> name2;
            Noble* noble = findNoble(noblePtrs, name);
            Warrior* warrior = findWarrior(warriorPtrs, name2);
            if(!noble) {
                cout << "Attempting to hire using unknown noble: " << name
                << endl;
            }
            else if(!warrior) {
                cout << "Attempting to hire using unknown warrior: " << name2
                << endl;
            }
            else {
                noble->hire(*warrior);
            }
        }
        //If the command is "Fire", fire a warrior from a noble's army
        else if(command == "Fire") {
            ifs >> name >> name2;
            Noble* noble = findNoble(noblePtrs, name);
            Warrior* warrior = findWarrior(warriorPtrs, name2);
            if(!noble) {
                cout << "Attempting to fire using unknown noble: " << name
                << endl;
            }
            else if(!warrior) {
                cout << "Attempting to fire using unknown warrior: " << name2
                << endl;
            }
            else {
                noble->fire(*warrior);
            }
        }
        //If the command is "Battle", start a battle between two nobles
        else if(command == "Battle") {
            ifs >> name >> name2;
            Noble* noble = findNoble(noblePtrs, name);
            Noble* noble2 = findNoble(noblePtrs, name2);

            if(!noble) {
                cout << "Attempting to battle using unknown noble: " << name
                << endl;
            }
            else if(!noble2) {
                cout << "Attempting to battle using unknown noble: " << name2
                << endl;
            }
            else {
                noble->battle(*noble2);

            }
        }
        //If the command is "Status", display all nobles and warriors
        else if(command == "Status") {
            status(warriorPtrs, noblePtrs);
        }
        //If the command is "Clear", remove nobles and warriors from memory
        else if(command == "Clear") {
            clear(warriorPtrs, noblePtrs);
        }

    }
    ifs.close();

}

//Opens the file for reading commands and exits if there's an error.
//Parameters: ifstream& ifs - the stream
//Return Type: void
void openFile(ifstream& ifs) {
    ifs.open("nobleWarriors.txt");
    if(!ifs) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
}

//finds a noble based name from a vector of pointers
//Parameters: vector<Noble*> - all the nobles, string& name - name of noble
//Return Type: a pointer to a Noble else a nullptr
Noble* findNoble(const vector<Noble*>& nobles, const string& name) {
    for (Noble* const noble: nobles) {
        if (noble->getName() == name) {
            return noble;
        }
    }
    return nullptr;
}

//finds a warrior from a vector of pointers to based on name
//Parameters: vector<Noble*> - all the nobles, string& name - name of warrior
//Return Type: a pointer to a Warrior else a nullptr
Warrior* findWarrior(const vector<Warrior*>& warriors, const string& name) {
    for (Warrior* const warrior: warriors) {
        if (warrior->getName() == name) {
            return warrior;
        }
    }
    return nullptr;
}

//Prints out nobles and their armies. Also prints unemployed warriors
//Parameters: vector<Noble*> - all the nobles vector<Warrior*> - all the warriors
//Return Type: void
void status(const vector<Warrior*>& warriorPtrs, const vector<Noble*>& noblePtrs){
    cout << "Status\n======\nNobles:" << endl;
    if(noblePtrs.size() == 0) {
        cout << "NONE" << endl;
    }
    for (Noble* const noble: noblePtrs) {
        cout << *noble << endl;
    }
    bool isAllHired = true;
    cout << "\nUnemployed Warriors:" << endl;
    for (Warrior* const warrior: warriorPtrs) {
        if(!warrior->isHired()) {
            cout << "\t"<< *warrior << endl;
            isAllHired = false;
        }
    }
    if (isAllHired) {cout << "NONE" << endl;}
}

//Clears all the warrior and noble objects from memory
//Parameters: vector<Noble*> - all the nobles vector<Warrior*> - all the warriors
//Return Type: void
void clear(vector<Warrior*>& warriorPtrs, vector<Noble*>& noblePtrs) {
    for (Warrior* const warrior: warriorPtrs) {
        delete warrior;
    }
    warriorPtrs.clear();

    for (Noble* const noble: noblePtrs) {
        delete noble;
    }
    noblePtrs.clear();
}

