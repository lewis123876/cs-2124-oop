//Name: Deejuanae Lewis
//The purpose of the program is to insert hydrocarbs and all their names

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

struct Molecule{
  vector<string> names;
  int carbon;
  int hydrogen;
};

void openFile(ifstream& file);
size_t findMolecule(const vector<Molecule>& molecules, int carbon, int hydrogen);
void insertMolecule(vector<Molecule>& molecules, ifstream& file );
void sortVector(vector<Molecule>& molecule);
void printMolecule(const Molecule& molecule);
void display(const vector<Molecule>& molecules);


int main(){
  ifstream file;
  openFile(file);

  vector<Molecule> molecules;
  insertMolecule(molecules, file);
  file.close();

  cout << "Unsorted: " << endl;
  display(molecules);
  cout << endl;

  sortVector(molecules);
  cout << "Sorted: " << endl;
  display(molecules);
  cout << endl;
}

void openFile(ifstream& file) {
  string name;
  do {
    cout << "Enter a file name:" << endl;
    cin >> name;
    file.open(name);
  }
  while(!file);
  cout << "File opened" << endl;
}

size_t findMolecule(const vector<Molecule>& molecules, int carbon, int hydrogen) {
  for (size_t i = 0; i < molecules.size(); i++) {
    if (molecules[i].carbon == carbon && molecules[i].hydrogen == hydrogen) {
      return i;
    }
  }
  return molecules.size();
}

void insertMolecule(vector<Molecule>& molecules, ifstream& file ){
  string name;
  int carbon, hydrogen;
  char temp;

  while (file >> name >> temp >> carbon >> temp >> hydrogen){
    size_t index = findMolecule(molecules, carbon, hydrogen);
    if (index != molecules.size()) {
      molecules[index].names.push_back(name);
    }
    else {
      vector<string> names = {name};
      Molecule newMolecule = {names, carbon, hydrogen};
      molecules.push_back(newMolecule);
    }
  }
}

void sortVector(vector<Molecule>& molecule) {
  for (size_t i = 0; i < molecule.size(); i++) {
    for (size_t j = 0; j < molecule.size()-i-1; j++) {
      if(molecule[j].carbon > molecule[j+1].carbon) {
        swap(molecule[j], molecule[j+1]);
      }

      if(molecule[j].carbon == molecule[j+1].carbon) {
        if(molecule[j].hydrogen > molecule[j+1].hydrogen) {
          swap(molecule[j], molecule[j+1]);
        }
      }
    }
  }
}

void printMolecule(const Molecule& molecule) {
  cout << "C" << molecule.carbon << "H" << molecule.hydrogen << " ";
  for (const string& name: molecule.names) {
    cout << name << " ";
  }
}

void display(const vector<Molecule>& molecules){
  for(const Molecule& molecule : molecules){
    cout << "C" << molecule.carbon << "H" << molecule.hydrogen << " ";
    for (const string& name : molecule.names) {
      cout << name << " ";
    }
    cout << endl;
  }
}








