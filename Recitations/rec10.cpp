/*
  Deejuanae Lewis
  rec10_start.cpp
  Starting code 23S
 */

#include <iostream>
#include <vector>
using namespace std;

//
// Musician class as provided to the students. Requires an Instrument class.
//

class Instrument {
    friend ostream& operator<<(ostream& os, const Instrument& obj);
public:
    virtual void makeSound() const = 0;
    virtual void play() const = 0;
    virtual void print(ostream& os) const = 0;
private:
};

ostream& operator<<(ostream& os, const Instrument& obj) {
    obj.print(os);
    return os;
}

void Instrument::makeSound() const {
    cout << "To make sound... ";
}

class Brass : public Instrument {
public:
    Brass(unsigned size) : size(size){}
    void makeSound() const {
        Instrument::makeSound();
        cout << " blow on mouthpiece of size " << size << endl ;
    }
    unsigned getSize() const {return size;}

private:
    unsigned size;
};

class Trombone : public Brass {
public:
    Trombone(unsigned size) : Brass(size) {}
    void play() const {
        cout << "Blat";
    }
    void print(ostream& os) const {
        os << "Trombone: " << getSize();
    }
private:
};

class Trumpet: public Brass {
public:
    Trumpet(unsigned size) : Brass(size) {}
    void play() const {
        cout << "Toot";
    }
    void print(ostream& os) const {
        os << "Trumpet: " << getSize();
    }
private:
};

class String: public Instrument {
public:
    String(unsigned pitch): pitch(pitch) {}
    void makeSound() const {
        Instrument::makeSound();
        cout << " bow a string with pitch " << pitch << endl ;
    }
    unsigned getPitch() const {return pitch;}
private:
    unsigned pitch;
};

class Violin: public String {
public:
    Violin(unsigned pitch): String(pitch) {}
    void play() const {
        cout << "Screech";
    }
    void print(ostream& os) const {
        os << "Violin: " << getPitch();
    }
private:
};

class Cello: public String {
public:
    Cello(unsigned pitch): String(pitch) {}
    void play() const {
        cout << "Squawk";
    }
    void print(ostream& os) const {
        os << "Cello: " << getPitch();
    }
private:
};


class Percussion: public Instrument {
public:
    Percussion(){};
    void makeSound() const{
        Instrument::makeSound();
        cout << " hit me!" << endl ;
    }
private:
};

class Drum: public Percussion {
public:
    Drum(){};
    void play() const {
        cout << "Boom";
    }
    void print(ostream& os) const {
        os<< "Drum";
    }
private:
};

class Cymbal: public Percussion {
public:
    Cymbal(){}
    void play() const {
        cout << "Crash";
    }
    void print(ostream& os) const {
        os<< "Cymbal";
    }
private:
};

class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << name << " has no instr\n";
    }

    // play: play the instrument

    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};

class MILL {
    friend ostream& operator<<(ostream& os, const MILL& obj);

    public:
    void receiveInstr(Instrument& instr) {
        instr.makeSound();
        for(size_t i = 0; i < instrumentPtrs.size(); i++){
            if (instrumentPtrs[i] == nullptr){
                instrumentPtrs[i] = &instr;
                return;
            }
        }
        instrumentPtrs.push_back(&instr);
    }

    Instrument* loanOut() {
        for(size_t i = 0; i < instrumentPtrs.size(); i++){
            if (instrumentPtrs[i] != nullptr) {
                Instrument* result = instrumentPtrs[i];
                instrumentPtrs[i] = nullptr;
                return result;
            }
        }
        return nullptr;
    }

    void dailyTestPlay(){
        for (Instrument* instr: instrumentPtrs){
            if (instr != nullptr){
                instr->makeSound();
            }
        }
    }

private:
    vector<Instrument*> instrumentPtrs;
};

ostream& operator<<(ostream& os, const MILL& obj) {
    os << "The MILL has the following instruments: ";
    bool allLoaned = true;
    for(const Instrument* instr: obj.instrumentPtrs) {
        if (instr != nullptr) {
            allLoaned = false;
        }
    }
    if (obj.instrumentPtrs.size() == 0 || allLoaned) {
        os << "None" << endl;
    }
    else {
        for(const Instrument* instr : obj.instrumentPtrs) {
            if (instr != nullptr) {
                os << *instr << endl;
            }
        }
    }
    return os;
}

class Orch {
public:
    void addPlayer(Musician& musician) {
        musicians.push_back(&musician);
    }
    void play() const {
        for(size_t i = 0; i < musicians.size(); i++){
            musicians[i] -> play();
        }
        cout << endl;
    }
private:
    vector<Musician*> musicians;
};



int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instrumentPtrs ---------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;

    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instrumentPtrs:\n" << mill << "\n\n";

    cout << "Put the instrumentPtrs into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instrumentPtrs:\n" << mill << "\n\n";

    cout << "Daily test ----------------------------------------------------\n"
	 << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

    cout << "Define some Musicians------------------------------------------\n";
    Musician harpo("Harpo");
    Musician groucho("Groucho");

    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	 // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

    groucho.testPlay();
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();
    harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instrumentPtrs:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL at the end of Part One:\n";
    cout << mill << endl;

    //
    // PART TWO
    //
    cout << "\nP A R T  T W O\n";

     Musician bob("Bob");
     Musician sue("Sue");
     Musician mary("Mary");
     Musician ralph("Ralph");
     Musician jody("Judy");
     Musician morgan("Morgan");

     Orch orch;

     // THE SCENARIO

     //Bob joins the orchestra without an instrument.
     orch.addPlayer(bob);

     //The orchestra performs
     cout << "orch performs\n";
     orch.play();

     //Sue gets an instrument from the MIL2 and joins the orchestra.
     sue.acceptInstr(mill.loanOut());
     orch.addPlayer(sue);

     //Ralph gets an instrument from the MIL2.
     ralph.acceptInstr(mill.loanOut());

     //Mary gets an instrument from the MIL2 and joins the orchestra.
     mary.acceptInstr(mill.loanOut());
     orch.addPlayer(mary);

     //Ralph returns his instrument to the MIL2.
     mill.receiveInstr(*ralph.giveBackInstr());

     //Jody gets an instrument from the MIL2 and joins the orchestra.
     jody.acceptInstr(mill.loanOut());
     orch.addPlayer(jody);

     // morgan gets an instrument from the MIL2
     morgan.acceptInstr(mill.loanOut());

     //The orchestra performs.
     cout << "orch performs\n";
     orch.play();

     //Ralph joins the orchestra.
     orch.addPlayer(ralph);

     //The orchestra performs.
     cout << "orch performs\n";
     orch.play();

     // bob gets an instrument from the MIL2
     bob.acceptInstr(mill.loanOut());

     // ralph gets an instrument from the MIL2
     ralph.acceptInstr(mill.loanOut());

     //The orchestra performs.
     cout << "orch performs\n";
     orch.play();

     //Morgan joins the orchestra.
     orch.addPlayer(morgan);

     //The orchestra performs.
     cout << "orch performs\n";
     orch.play();

    cout << endl << mill << endl;

}

