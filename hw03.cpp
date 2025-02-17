//Deejuanae Lewis
//The purpose is to create warriors and their weapons
//then simulate battles between warriors

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Warrior models a warrior with a name and a weapon
//includes getter functions for all fields and a setter for strength
//nested inside the warrior is the weapon class
//Weapon models a weapon with a name and a strength
//includes getters for name and strength and a setter for strength
class Warrior {
    friend ostream& operator << (ostream& os, const Warrior& obj);
public:
    Warrior(const string& name, const string& weaponName, int strength) :
    name(name), weapon{weaponName, strength}{}

    //inspectors (getters) for accessing private member variables
    const string& getName() const;
    const string& getWeaponName() const;
    int getWeaponStrength() const;
    void changeStrength(int difference);

private:
    class Weapon {
    public:
        Weapon(const string& name, int strength) :
        name(name), strength(strength){}

        int getStrength() const {return strength;}
        const string& getName() const {return name;}
        void setStrength(int newStrength) {strength = newStrength;}

        friend ostream& operator<<(ostream& os, const Weapon& obj) {
            os << "weapon: " << obj.name << ", " << obj.strength;
            return os;
        }

    private:
        string name;
        int strength;
    };

    string name;
    Weapon weapon;
};

ostream& operator <<(ostream& os, const Warrior& obj) {
    os << "Warrior: " << obj.name << ", " << obj.weapon;
    return os;
}

const string& Warrior::getName() const {
    return name;
}

const string& Warrior::getWeaponName() const {
    return weapon.getName();
}

int Warrior::getWeaponStrength() const {
    return weapon.getStrength();
}

//a method used to change the weapon strength
void Warrior::changeStrength(int difference) {
    int newStrength = weapon.getStrength() - difference;
    if (newStrength < 0) {
        newStrength = 0;
    }
    weapon.setStrength(newStrength);
}

//Function prototypes
void openFile(ifstream& ifs);
void addWarrior(vector<Warrior>& warriors, const string& name,
                const string& weaponName, int strength);
size_t findIndex(const vector<Warrior>& warriors, const string& name);
void battle(vector<Warrior>& warriors, const string& name1, const string& name2);
void status(const vector<Warrior>& warriors);

int main() {
    ifstream ifs;
    openFile(ifs);

    //initializing vector to store warriors and variables to read file
    vector<Warrior> warriors;
    string command;
    string name;
    string name2;
    string weaponName;
    int strength;

    //reading each line of the file and performing the command
    while(ifs >> command) {
        if (command == "Warrior") {
            ifs >> name >> weaponName >> strength;
            addWarrior(warriors, name, weaponName, strength);
        }
        else if (command == "Battle") {
            ifs >> name >> name2;
            battle(warriors, name, name2);
        }
        else if (command == "Status") {
            status(warriors);
        }
    }
    ifs.close();
}


//Function to open a file and checks if it's open
//Parameters include a reference to the file stream
//Does not return a value
void openFile(ifstream& ifs) {
    ifs.open("warriors.txt");
    if (!ifs) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
}


//Function to create a warrior and add them to the roster
//Parameters include a vector of warriors, warrior name, weapon name, and
//weapon strength
//Does not return a value
void addWarrior(vector<Warrior>& warriors, const string& name,
const string& weaponName, int strength) {
    //check for duplicate warrior names
    for (const Warrior& warrior: warriors) {
        if(warrior.getName() == name) {
            cerr << "Error: Duplicate Warrior Name." << endl;
            return;
        }
    }
    warriors.emplace_back(name, weaponName, strength);
}


//Function to find the index of a warrior by name
//Parameters include takes in the vector of warriors and the name of a warrior
//Returns size_t, the index of the warrior or the vector size if not found
size_t findIndex(const vector<Warrior>& warriors, const string& name) {
    for(size_t i = 0; i < warriors.size(); i++) {
        if(warriors[i].getName() == name) {
            return i;
        }
    }
    return warriors.size();
}


//Function that simulates a battle between two warriors
//Parameters include a vector of warriors and the names of both fighters
//Does not return a value
void battle(vector<Warrior>& warriors, const string& name1, const string& name2) {
    size_t index1 = findIndex(warriors, name1);
    size_t index2 = findIndex(warriors, name2);

    // Check if warriors were found
    if (index1 == warriors.size() || index2 == warriors.size()) {
        cerr << "Error: One or both of the warriors do not exist." << endl;
        return;
    }

    // Initializing reference to warriors and their weapon strength
    Warrior& warrior1 = warriors[index1];
    Warrior& warrior2 = warriors[index2];
    int strength1 = warrior1.getWeaponStrength();
    int strength2 = warrior2.getWeaponStrength();
    cout << name1 << " battles " << name2 << endl;

    // Determine the battle outcome
    if (strength1 == 0 && strength2 == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    } else if (strength1 == 0) {
        cout << "He's dead, " << warrior2.getName() << endl;
    } else if (strength2 == 0) {
        cout << "He's dead, " << warrior1.getName() << endl;
    } else if (strength1 > strength2) {
        warrior2.changeStrength(strength1);
        warrior1.changeStrength(strength2);
        cout << warrior1.getName() << " defeats " << warrior2.getName() << endl;
    } else if (strength2 > strength1) {
        warrior1.changeStrength(strength2);
        warrior2.changeStrength(strength1);
        cout << warrior2.getName() << " defeats " << warrior1.getName() << endl;
    } else {
        warrior1.changeStrength(strength1);
        warrior2.changeStrength(strength2);
        cout << "Mutual Annihilation: " << warrior1.getName() << " and "
             << warrior2.getName() << " die at each other's hands" << endl;
    }
}


//Function that outputs all warriors and their weapons
//Parameters include the vector of warriors
//Does not return a value
void status(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;

    //printing each warrior object
    for (const Warrior& warrior: warriors) {
        cout << warrior << endl;
    }
}