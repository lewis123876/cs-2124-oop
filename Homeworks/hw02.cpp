//Deejuanae Lewis
//Model of a game of medieval times
//warriors fight sometimes to the death


#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


struct Warrior {
    string name;
    int strength;
};


void openFile(ifstream& file);
void addWarrior(vector<Warrior>& warriors, const string& name, int strength);
void battle(vector<Warrior>& warriors, const string& name1, const string& name2);
void status(const vector<Warrior>& warriors);


int main() {
    //open file
    ifstream file;
    openFile(file);

    vector<Warrior> warriors;
    string command;

    //reading each line of the file and performing the command
    while(file >> command) {
        if(command == "Warrior") {
            string name;
            int strength;
            file >> name >> strength;
            addWarrior(warriors, name, strength);
        }
        else if(command == "Battle") {
            string name1;
            string name2;
            file >> name1 >> name2;
            battle(warriors, name1, name2);
        }
        else if(command == "Status") {
            status(warriors);
        }
    }
    file.close();
}

//opens a file and checks if it's open
//takes in a file
//does not return a value
void openFile(ifstream& file) {
    file.open("warriors.txt");
    if(!file) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
}


//creates a warrior and adds them to the roster
//takes in the vector of warriors, warrior name, and warrior strength
//does not return a value
void addWarrior(vector<Warrior>& warriors, const string& name, int strength){
    //checking if new warrior already exists in vector
    for (const Warrior& warrior : warriors) {
        if (warrior.name == name) {
            cerr << "Error: Duplicate Warrior Name." << endl;
            return;
        }
    }
    //adding warrior to vector
    warriors.push_back(Warrior(name, strength));
}


//finds the index of a warrior in the vector
//takes in the vector of warriors and the name of a warrior
//returns an integer for the index
size_t findIndex(const vector<Warrior>& warriors, const string& name) {
    for (size_t i = 0; i < warriors.size(); i++) {
        if (warriors[i].name == name) {
            return i;
        }
    }
    return warriors.size();
}

//causes a battle between two warriors
//takes in the vector of warriors and the names of both fighters
//does not return a value
void battle(vector<Warrior>& warriors, const string& name1, const string& name2){
    size_t index1 = findIndex(warriors, name1);
    size_t index2 = findIndex(warriors, name2);

    //check if warriors were found. If not display an error
    if (index1 == warriors.size() || index2 == warriors.size()) {
        cerr << "Error: One or both of the warriors do not exist." << endl;
        return;
    }

    //initializing reference to warriors
    Warrior& warrior1 = warriors[index1];
    Warrior& warrior2 = warriors[index2];

    cout << name1 << " battles " << name2 << endl;

    //check warriors' strengths then determine the battle
    if( warrior1.strength == 0 && warrior2.strength == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if(warrior1.strength == 0) {
        cout << "He's dead, " << warrior2.name << endl;
    }
    else if (warrior2.strength == 0) {
        cout << "He's dead, " << warrior1.name << endl;
    }
    else if(warrior1.strength > warrior2.strength) {
        warrior1.strength -= warrior2.strength;
        warrior2.strength = 0;
        cout << warrior1.name <<  " defeats " << warrior2.name << endl;
    }
    else if(warrior2.strength > warrior1.strength) {
        warrior2.strength -= warrior1.strength;
        warrior1.strength = 0;
        cout << warrior2.name <<  " defeats " << warrior1.name << endl;
    }
    else {
        warrior1.strength = 0;
        warrior2.strength = 0;
        cout << "Mutual Annihilation: " << warrior1.name << " and " << warrior2.name;
        cout << " die at each other's hands" << endl;
        }
}


//lists all warriors and their strengths
//takes in the vector of warriors
//does not return a value
void status(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;

    //output each warriors name and strength
    for (const Warrior& warrior: warriors) {
        cout << "Warrior: " << warrior.name << ", strength: " << warrior.strength << endl;
    }
}
