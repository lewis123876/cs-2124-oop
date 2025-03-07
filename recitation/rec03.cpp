//Name: Deejuanae Lewis
//The purpose of the program is to manage a bank account
//Using structs and classes

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


// Task 1
// Define an Account struct
struct Account {
     string name;
     int accountNumber;
};


// Task 2
// Define an Account class (use a different name than in Task 1)
class AccountClass {
public:
     AccountClass(const string& name, int accountNumber) :
     name(name), accountNumber(accountNumber) {}

     //inspectors (getters)
     const string& getName() const;
     int getAccountNumber() const;
     friend ostream& operator<<(ostream& os, const AccountClass& obj);

private:
     string name;
     int accountNumber;

};

ostream& operator << (ostream& os, const AccountClass& obj) {
     //os << obj.getName() << "\t" << obj.getAccountNumber();
     os << obj.name << "\t" << obj.accountNumber;
     return os;
}

const string& AccountClass::getName() const {
     return name;
}

int AccountClass::getAccountNumber() const {
     return accountNumber;
}

// Task 3
// Define another Account class (use a different name than in Task
// 1&2) and a Transaction class. The Transaction class is to be
// defined outside of the Account class, i.e. it is not "nested".
class Transaction {
public:
     Transaction(const string& type, int value):
     type(type), value(value){}
     friend ostream& operator << (ostream& os, const Transaction& obj);

private:
     string type;
     int value;

};
ostream& operator << (ostream& os, const Transaction& obj) {
     os << obj.type << " " << obj.value;
     return os;
}

class NewAccountClass {
public:
     NewAccountClass(const string& name, int accountNumber) :
          name(name), accountNumber(accountNumber) {
          balance = 0;
     }

     //inspectors (getters)
     const string& getName() const;
     int getAccountNumber() const;
     void deposit(int amount);
     void withdrawal(int amount);
     friend ostream& operator<<(ostream& os, const NewAccountClass& obj);


private:
     string name;
     int accountNumber;
     vector<Transaction> transactions;
     int balance;


};

const string& NewAccountClass::getName() const {
     return name;
}

int NewAccountClass::getAccountNumber() const {
     return accountNumber;
}

void NewAccountClass::deposit(int amount) {
     string type = "deposit";
     transactions.emplace_back(type, amount);
     balance += amount;
}
void NewAccountClass::withdrawal(int amount) {
     if (amount > balance) {
          cout << "Account# " << accountNumber << " has only " << balance
          << ". Insufficient for withdrawal of " << amount << endl;
          return;
     }
     string type = "withdrawal";
     transactions.emplace_back(type, amount);
     balance -= amount;
}

ostream& operator << (ostream& os, const NewAccountClass& obj) {
     os << obj.name << " " << obj.accountNumber << ": " << endl;
     for (const Transaction& transaction : obj.transactions) {
          os << "\t" << transaction << endl;
     }
     return os;
}


// Task 4
// Define yet another Account class, this time with a nested public
// Transaction class. Again use a different name for the Account class
// than in the previous Tasks. Note that it is NOT necessary to rename
// the Transaction class, since it is nested.
class NestedAccountClass {
     friend ostream& operator<<(ostream& os, const NestedAccountClass& obj);
public:
     class Transaction {
     public:
          Transaction(const string& type, int value)
              : type(type), value(value) {}

          friend ostream& operator<<(ostream& os, const Transaction& trans) {
               os << trans.type << ": " << trans.value;
               return os;
          }

     private:
          string type;
          int value;
     };

     NestedAccountClass(const string& name, int accountNumber)
         : name(name), accountNumber(accountNumber), balance(0) {}

     // Inspectors (getters)
     const string& getName() const;
     int getAccountNumber() const;
     void deposit(int amount);
     void withdrawal(int amount);

private:
     string name;
     int accountNumber;
     vector<Transaction> transactions;
     int balance;
};

int NestedAccountClass::getAccountNumber() const {
     return accountNumber;
}

void NestedAccountClass::deposit(int amount) {
     string type = "deposit";
     transactions.emplace_back(type, amount);
     balance += amount;
}

void NestedAccountClass::withdrawal(int amount) {
     if (amount > balance) {
          cout << "Account# " << accountNumber << " has only " << balance
          << ". Insufficient for withdrawal of " << amount << endl;
          return;
     }
     string type = "withdrawal";
     transactions.emplace_back(type, amount);
     balance -= amount;
}

ostream& operator << (ostream& os, const NestedAccountClass& obj) {
     os << obj.name << " " << obj.accountNumber << ": " << endl;
     for (const NestedAccountClass::Transaction& transaction : obj.transactions) {
          os << "\t" << transaction << endl;
     }
     return os;
}


// Task 5
// Same as Task 4, but make the Transaction nested class private.
// Yes, the Account class needs a new name but, again, the Transaction
// class does not.

int main() {

     // Task 1: account as struct
     //      1a
     ifstream file("accounts.txt");
     if(!file) {
          cerr << "File failed to open" << endl;
          exit(1);
     }

     vector<Account> accounts;
     string name;
     int accountNumber;

     while(file >> name >> accountNumber) {
          Account tempAccount;
          tempAccount.name = name;
          tempAccount.accountNumber = accountNumber;
          accounts.push_back(tempAccount);
     }

     file.close();

     cout << "Task1a:\n"
         << "Filling vector of struct objects, define a local struct instance\n"
         << "and set fields explicitly:\n";

     for(const Account& account: accounts) {
          cout << account.name << "\t" << account.accountNumber << endl;
     }


    //      1b
     accounts.clear();
     file.open("accounts.txt");
     if (!file) {
          cerr << "File failed to open";
          exit(1);
     }

     while(file >> name >> accountNumber) {
          Account newAccount{name, accountNumber};
          accounts.push_back(newAccount);
     }

     file.close();

     cout << "Task1b:\n"
          << "Filling vector of struct objects, using {} initialization:\n";
     for(const Account& account: accounts) {
          cout << account.name << "\t" << account.accountNumber << endl;
     }

    //==================================
    // Task 2: account as class

     //      2a
     file.open("accounts.txt");
     if (!file) {
          cerr << "File failed to open";
          exit(1);
     }

     vector<AccountClass> accountClasses;

     while(file >> name >> accountNumber) {
          AccountClass newAccountClass(name, accountNumber);
          accountClasses.push_back(newAccountClass);

     }
     file.close();

     cout << "==============\n";
     cout << "\nTask2a:"
          << "\nFilling vector of class objects, using local class object:\n";
     for(const AccountClass& accountClass: accountClasses) {
          cout << accountClass.getName() << "\t" << accountClass.getAccountNumber() << endl;
     }

     cout << "\nTask2b:\n";
     cout << "output using output operator with getters\n";
     for(const AccountClass& accountClass: accountClasses) {
          cout << accountClass << endl;
     }

    cout << "\nTask2c:\n"
         << "output using output operator as friend without getters\n";
     for(const AccountClass& accountClass: accountClasses) {
          cout << accountClass << endl;
     }

    cout << "\nTask2d:\n"
         << "Filling vector of class objects, using temporary class object:\n";
     accountClasses.clear();
     file.open("accounts.txt");
     if (!file) {
          cerr << "File failed to open";
          exit(1);
     }

     while(file >> name >> accountNumber) {
          accountClasses.push_back(AccountClass(name, accountNumber));
     }

     file.close();

     for(const AccountClass& accountClass: accountClasses) {
          cout << accountClass << endl;
     }

    cout << "\nTask2e:\n"
         << "Filling vector of class objects, using emplace_back:\n";
     accountClasses.clear();
     file.open("accounts.txt");
     if (!file) {
          cerr << "File failed to open";
          exit(1);
     }

     while(file >> name >> accountNumber) {
          accountClasses.emplace_back(name, accountNumber);
     }

     file.close();

     for(const AccountClass& accountClass: accountClasses) {
          cout << accountClass << endl;
     }

    cout << "==============\n"
         << "\nTask 3:\nAccounts and Transaction:\n";
     file.open("transactions.txt");
     if (!file) {
          cerr << "File failed to open";
          exit(1);
     }
     string command;
     vector<NewAccountClass> newAccounts;
     string accountName;
     int accountNumber2;
     int value;

     while(file >> command) {
          if (command == "Account") {
               file >> accountName >> accountNumber2;
               newAccounts.emplace_back(accountName, accountNumber2);
          }
          else{
               file >> accountNumber2 >> value;
               for (NewAccountClass& account: newAccounts) {
                    if (account.getAccountNumber() == accountNumber2) {
                         if(command == "Deposit") {
                              account.deposit(value);
                         }
                         if (command == "Withdraw") {
                              account.withdrawal(value);
                         }
                    }
                    break;
               }
          }
     }
     file.close();

     for (const NewAccountClass& newAccount: newAccounts) {
          cout << newAccount << endl;
     }

    cout << "==============\n"
         << "\nTask 4:\nTransaction nested in public section of Account:\n";
     file.open("transactions.txt");
     if (!file) {
          cerr << "File failed to open";
          exit(1);
     }

     vector<NestedAccountClass> nestedAccounts;

     while(file >> command) {
          if (command == "Account") {
               file >> accountName >> accountNumber2;
               nestedAccounts.emplace_back(accountName, accountNumber2);
          }
          else{
               file >> accountNumber2 >> value;
               for (NestedAccountClass& account: nestedAccounts) {
                    if (account.getAccountNumber() == accountNumber2) {
                         if(command == "Deposit") {
                              account.deposit(value);
                         }
                         if (command == "Withdraw") {
                              account.withdrawal(value);
                         }
                         break;
                    }
               }
          }
     }
     file.close();

     for (const NestedAccountClass& nestedAccount: nestedAccounts) {
          cout << nestedAccount << endl;
     }

    cout << "==============\n"
         << "\nTask 5:\nTransaction nested in private section of Account:\n";

}
