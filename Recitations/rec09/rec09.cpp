//Deejuanae Lewis
#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
    //friend ostream& operator<<(ostream& os, const PrintedMaterial& obj) {
    //    os << "Pages: "<< obj.displayNumPages;
    //    return os;
    //}
    
public:
    PrintedMaterial(unsigned numPages):numOfPages(numPages){}
    virtual void displayNumPages() const = 0;
protected: 
private:
    unsigned numOfPages;
};

void PrintedMaterial::displayNumPages() const { 
    cout << numOfPages << endl; 
}

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numPages):PrintedMaterial(numPages){}
    void displayNumPages() const {
        cout << "Magazine: \n";
        PrintedMaterial::displayNumPages();
    }
protected:     
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numPages):PrintedMaterial(numPages){}
    void displayNumPages() const {
        cout << "\nBook: \n";
        PrintedMaterial::displayNumPages();
    }
protected: 
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numPages, unsigned numIndxPgs ):Book(numPages),
	  numOfIndexPages(numIndxPgs){}
    void displayNumPages() const {
        cout << "\nTextBook: \n"
	    cout << "Pages: ";
	    PrintedMaterial::displayNumPages();
	    cout << "Index pages: ";
	    cout << numOfIndexPages << endl; 
    }
    
    void displayNumPages() const {
        PrintedMaterial::displayNumPages();
    }
protected: 
private:
    unsigned numOfIndexPages;
};


class Novel : public Book {
public:
    Novel(unsigned numPages):Book(numPages){}
    
    void displayNumPages() const {
        cout << "\nNovel: \n"
        PrintedMaterial::displayNumPages();
    }
protected: 
private:
};


void displayNumberOfPages(const PrintedMaterial& obj);

int main() {
    TextBook text(5430, 23);
    Novel novel(213);
    Magazine mag(6);

    text.displayNumPages();
    novel.displayNumPages();
    mag.displayNumPages();

    cout << "Display printed material\n" << endl;
    PrintedMaterial pm(2345);
    pm.displayNumPages();
    
    cout<< "\nUsing PrintedMaterial to store textbook object\n";
    PrintedMaterial* pmPtr;
    pmPtr = &text;
    pmPtr->displayNumPages();
    
    //displayNumberOfPages(mag);
    //displayNumberOfPages(novel);
    //displayNumberOfPages(text);

    //PrintedMaterial* pmPtr;
    //pmPtr = &t;
    //pmPtr->displayNumberOfPages();

    
    cout << "\nVector of Printed Material\n";
    vector< PrintedMaterial* > materials;
    materials.push_back(&text);
    materials.push_back(&novel);
    materials.push_back(&mag);
    
    //for(size_t i=0; i < materials.size(); i++) {
	//materials[i]->displayNumPages();
	//cout << "\n";
    //}


    for (const PrintedMaterial* pmPtr : materials) {
	pmPtr->displayNumPages();
	cout << endl;
    }

}

void displayNumberOfPages(const PrintedMaterial& obj) {
    obj.displayNumPages();
}