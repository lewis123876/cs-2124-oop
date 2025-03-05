//Deejuanae Lewis

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    //Q1
    std::cout << "Hello, World!" << endl;

    //Q2
    cout << "Hello, World!" << endl;

    //Q3
    int x;
    int y = 17;
    int z = 2000000017;
    double pie = 3.14159;
    cout << "x: " << x << endl;

    //Q4
    cout << "X size: " << sizeof(x) << "\nY size: "
    << sizeof(y) << "\nZ size: " << sizeof(z)
    << "\nPie size: " << sizeof(pie) << endl ;

    //Q5
    //x = "felix";

    //Q6
    if ( y >= 10 && y <= 20) {
        cout << "Y is between 10 and 20 inclusive" << endl;
    }

    //Q7
    for (int i = 10; i <= 20; i++) {
        cout << i << " ";
    }
    cout << endl;
    int start = 10;
    while (start <= 20) {
        cout << start << " ";
        start++;
    }
    cout << endl;
    start = 10;
    do {
        cout << start << " ";
        start++;
    }
    while(start<=20);
    cout << endl;

    //Q8
    ifstream ifs;
    string name;
     do {
         cout << "Enter a file name: ";
         cin >> name;
         ifs.open(name);
     }
    while(!ifs);
    cout << "File opened" << endl;

    //Q9
    string word;
    while (ifs >> word) {
        cout << word << endl;
    }
    ifs.close();

    //Q10
    ifstream integers;
    integers.open("integers.txt");
    if(!integers) {
        cerr << "File does not exist." << endl;
        exit(1);
    }
    else {
        int currVal;
        int sum = 0;
        while (integers >> currVal) {
            sum += currVal;
        }
        cout << "Sum: " << sum << endl;
    }

    //Q11
    ifstream mixed;
    mixed.open("mixed.txt");

    if(!mixed) {
        cerr << "File does not exist." << endl;
        exit(1);
    }
    else {
        int currVal2;
        int sum = 0;
        while (integers >> currVal2) {
            sum += currVal2;
        }
        cout << "Sum: " << sum << endl;
    }


    //Vector
    //12
    vector<int> v = {2, 4, 6, 8, 10};

    //13
    for (size_t t = 0; t < v.size(); t++) {
        cout << v[t] << " ";
    }
    cout << endl;

    for (int i : v) {
        cout << i << " ";
    }
    cout << endl;

    for (size_t t = v.size(); t > 0; t--) {
        cout << v[t - 1]<< " ";
    }
    cout << endl;

    //14
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19 };
    for (int i : primes) {
        cout << i << " ";
    }

















}
