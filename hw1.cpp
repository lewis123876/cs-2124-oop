//Name: Deejuanae Lewis
//The purpose of the program is to decrypt text encrypted by caesar cypher
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//declares functions that are to be defined later
char decryptChar(char& character , int distance);
void decryptLine(string& line, int distance);


int main() {
    //open file for reading and check if it is open
    ifstream code("encrypted.txt");
    if(!code) {
        cerr << "failed to open encrypted";
        exit(1);
    }

    //declares variables for rotation distance and lines of the text
    vector<string> lines;
    string line;
    int distance;

    //reads and stores rotation distance and the text
    code >> distance;
    while(getline(code, line)) {
        lines.push_back(line);
    }

    //decrypts each line of the text stored in vector
    for (size_t i = 0; i < lines.size(); i++) {
        decryptLine(lines[i], distance);
    }

    //prints decrypted lines in reverse order
    for (size_t t = lines.size(); t > 0; t--) {
        cout << lines[t - 1] << endl;
    }
}

//decrypts a single character and returns the new value
char decryptChar(char& character , int distance) {
    //checking if the character is uppercase A through Z
    if (character > 64 && character < 91) {
        //shifts characters by distance using modulus 26, in case there is wrap-around
        character -= (distance % 26);
        //adjusts character if it is below capital A
        if (character < 65) {
            character = 91 - (65 - character);
        }
    }
    return character;
}

//Decrypts an entire line by using decryptchar for each character
void decryptLine(string& line, int distance) {
    for(char& c : line ) {
        c = decryptChar(c, distance);
    }
}
