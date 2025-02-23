//Deejuanae Lewis
#include "Warrior.h"
#include "Noble.h"
#include <iostream>

namespace WarriorCraft {

    Warrior::Warrior(const std::string& name, double strength)
        : name(name), strength(strength), hired(false), noble(nullptr) {}

    const std::string& Warrior::getName() const { return name; }
    double Warrior::getStrength() const { return strength; }
    bool Warrior::isHired() const { return hired; }

    void Warrior::setHired(bool newStatus) { hired = newStatus; }
    void Warrior::setStrength(double newStrength) { strength = newStrength; }
    void Warrior::setNoble(Noble* newNoble) { noble = newNoble; }

    void Warrior::runaway() {
        if (noble) {
            std::cout << name << " flees in terror, abandoning his lord, " << noble->getName() << std::endl;
            noble->removeWarrior(*this);
            setNoble(nullptr);
            setHired(false);
        } else {
            std::cout << name << " is not employed by anyone!" << std::endl;
        }
    }

    std::ostream& operator<<(std::ostream& os, const Warrior& obj) {
        os << obj.name << ": " << obj.strength;
        return os;
    }

} // namespace WarriorCraft
